//AO Star

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_CHILDREN 10
#define INF INT_MAX

typedef enum { OR_NODE, AND_NODE } NodeType;

typedef struct Node {
    int id;
    NodeType type;
    int heuristic;
    int solved;
    int cost;
    int num_children;
    struct Node* children[MAX_CHILDREN];
    int weights[MAX_CHILDREN];
    int best_child;  // Index of best child for OR nodes
} Node;

Node* create_node(int id, NodeType type, int heuristic) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->id = id;
    node->type = type;
    node->heuristic = heuristic;
    node->solved = 0;
    node->cost = heuristic;
    node->num_children = 0;
    node->best_child = -1;
    return node;
}

void add_child(Node* parent, Node* child, int weight) {
    if (parent->num_children < MAX_CHILDREN) {
        parent->children[parent->num_children] = child;
        parent->weights[parent->num_children] = weight;
        parent->num_children++;
    }
}

// Update node cost and solved status
void update_node(Node* node) {
    if (node->num_children == 0) {
        node->solved = 1;
        return;
    }

    if (node->type == OR_NODE) {
        int min_cost = INF;
        node->solved = 0;
        
        for (int i = 0; i < node->num_children; i++) {
            int child_cost = node->weights[i] + node->children[i]->cost;
            if (child_cost < min_cost) {
                min_cost = child_cost;
                node->best_child = i;
                node->solved = node->children[i]->solved;
            }
        }
        node->cost = min_cost;
    } 
    else { // AND_NODE
        int total_cost = 0;
        node->solved = 1;
        
        for (int i = 0; i < node->num_children; i++) {
            total_cost += node->weights[i] + node->children[i]->cost;
            if (!node->children[i]->solved) {
                node->solved = 0;
            }
        }
        node->cost = total_cost;
    }
}

int ao_star(Node* root) {
    if (root->num_children == 0) {
        root->solved = 1;
        return root->cost;
    }
    
    int changed;
    do {
        changed = 0;
        
        // Process all unsolved non-leaf nodes in a bottom-up manner
        for (int i = 0; i < root->num_children; i++) {
            if (!root->children[i]->solved) {
                int old_cost = root->children[i]->cost;
                ao_star(root->children[i]);
                if (old_cost != root->children[i]->cost) {
                    changed = 1;
                }
            }
        }
        
        // Update the root node
        int old_cost = root->cost;
        update_node(root);
        if (old_cost != root->cost) {
            changed = 1;
        }
    } while (!root->solved && changed);
    
    return root->cost;
}

void print_solution(Node* node) {
    if (!node) return;
    
    printf("Node %d (Cost: %d, Type: %s, Solved: %s)\n", 
           node->id, node->cost,
           node->type == OR_NODE ? "OR" : "AND", 
           node->solved ? "Yes" : "No");
    
    if (node->type == OR_NODE && node->best_child >= 0) {
        printf("  Best child -> ");
        print_solution(node->children[node->best_child]);
    } 
    else if (node->type == AND_NODE) {
        for (int i = 0; i < node->num_children; i++) {
            print_solution(node->children[i]);
        }
    }
}

int main() {
    // Create the graph nodes
    Node* n1 = create_node(1, OR_NODE, 5);
    Node* n2 = create_node(2, AND_NODE, 3);
    Node* n3 = create_node(3, OR_NODE, 4);
    Node* n4 = create_node(4, OR_NODE, 2);
    Node* n5 = create_node(5, OR_NODE, 6);
    Node* n6 = create_node(6, OR_NODE, 1);

    // Adding children with weights
    add_child(n1, n2, 2);
    add_child(n1, n3, 3);
    add_child(n2, n4, 1);
    add_child(n2, n5, 4);
    add_child(n3, n6, 2);

    // Run AO* algorithm
    int cost = ao_star(n1);

    // Print results
    printf("Minimum cost solution graph has cost: %d\n", cost);
    printf("Solution graph nodes:\n");
    print_solution(n1);

    return 0;
}

// AO* Algorithm Explanation
// This code implements the AO* algorithm, which is a variant of the A* algorithm designed to search through AND-OR graphs. Let me walk you through how it works.
// What are AND-OR Graphs?
// An AND-OR graph represents a problem that can be decomposed into subproblems with two types of nodes:

// OR Nodes: Represent alternative ways to solve a problem. To solve an OR node, you only need to solve ONE of its children (whichever has the minimum cost).
// AND Nodes: Represent decomposition of a problem into subproblems. To solve an AND node, you must solve ALL of its children.

// Key Components of the Code
// Data Structures
// ctypedef struct Node {
//     int id;
//     NodeType type;  // OR_NODE or AND_NODE
//     int heuristic;  // Estimated cost to goal
//     int solved;     // Whether this node is solved
//     int cost;       // Total cost of the best solution
//     int num_children;
//     struct Node* children[MAX_CHILDREN];
//     int weights[MAX_CHILDREN];  // Edge costs to children
//     int best_child;  // Index of best child for OR nodes
// } Node;
// Main Functions

// create_node: Creates a new node with initial values
// add_child: Adds a child node with a specified edge weight
// update_node: Updates a node's cost and solved status based on its children
// ao_star: The main algorithm that finds the optimal solution
// print_solution: Displays the solution path

// How the AO* Algorithm Works
// The algorithm repeatedly performs these steps until the root node is solved or no changes occur:

// Expand unsolved nodes: Process all unsolved non-leaf nodes in a bottom-up manner
// Update costs: Recalculate costs for each node based on children
// Check for solution: Determine if the root node is now solved

// Cost Calculation
// For OR nodes:

// Choose the child with minimum (edge_weight + child_cost)
// Node is solved if its best child is solved

// For AND nodes:

// Sum up (edge_weight + child_cost) for all children
// Node is solved only if ALL children are solved

// Detailed Dry Run of the Example
// Let's trace through the execution of the code using the graph constructed in the main() function:
// Graph Structure:
// - n1 (OR, h=5)
//   ├── n2 (AND, h=3) with edge weight 2
//   │    ├── n4 (OR, h=2) with edge weight 1
//   │    └── n5 (OR, h=6) with edge weight 4
//   └── n3 (OR, h=4) with edge weight 3
//        └── n6 (OR, h=1) with edge weight 2
// Initial State
// All nodes have cost = heuristic and solved = 0 (except leaf nodes, which are considered solved).
// NodeTypeHeuristicCostSolvedn1OR550n2AND330n3OR440n4OR220n5OR660n6OR111 (leaf)
// First Iteration

// We start with ao_star(n1)
// Process n1's children: n2 and n3

// Call ao_star(n2)

// Process n2's children: n4 and n5

// Call ao_star(n4) - n4 is a leaf, so no change
// Call ao_star(n5) - n5 is a leaf, so no change


// Update n2: n2 is an AND node, so cost = (1+2) + (4+6) = 13, solved = 0


// Call ao_star(n3)

// Process n3's children: n6

// n6 is a leaf, already solved


// Update n3: n3 is an OR node, so cost = 3+1 = 4, solved = 1, best_child = n6




// Update n1: n1 is an OR node

// From n2: 2+13 = 15
// From n3: 3+4 = 7
// Choose minimum: cost = 7, solved = 1, best_child = n3



// State After First Iteration
// NodeTypeCostSolvedNotesn1OR71Best path is through n3n2AND130n3OR41Best path is through n6n4OR20n5OR60n6OR11Leaf node
// Final Solution
// The algorithm finds that the optimal solution has a cost of 7, going through n1 → n3 → n6.
// Example Output
// Minimum cost solution graph has cost: 7
// Solution graph nodes:
// Node 1 (Cost: 7, Type: OR, Solved: Yes)
//   Best child -> Node 3 (Cost: 4, Type: OR, Solved: Yes)
//   Best child -> Node 6 (Cost: 1, Type: OR, Solved: Yes)
// Key Insights

// Bottom-up Approach: The algorithm works from leaf nodes upward to the root.
// Admissible Heuristic: Like A*, AO* requires an admissible heuristic (one that never overestimates the true cost).
// Optimality: AO* guarantees finding the optimal solution if the heuristic is admissible.
// Efficiency: It avoids exploring all possible paths by using heuristics to guide the search.

// AO* is particularly useful for problem-solving in artificial intelligence where problems can be broken down into subproblems with AND/OR relationships, such as game playing, theorem proving, and planning.
