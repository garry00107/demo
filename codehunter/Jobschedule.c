#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_JOBS 10
#define MAX_MACHINES 5

// Structure to represent a job
typedef struct {
    int id;
    int duration;
    int machine_constraints[MAX_MACHINES]; // 1 if can run on machine, 0 if not
} Job;

// Simple CSP-based job scheduler
void scheduleJobs(Job jobs[], int num_jobs, int num_machines) {
    int schedule[MAX_MACHINES][100] = {0}; // Schedule for each machine (time slots)
    int machine_time[MAX_MACHINES] = {0};  // Current time on each machine
    
    // Process each job
    for (int j = 0; j < num_jobs; j++) {
        // Find the best machine for this job (earliest available that meets constraints)
        int best_machine = -1;
        int earliest_time = 9999;
        
        for (int m = 0; m < num_machines; m++) {
            // Check if this job can run on this machine
            if (jobs[j].machine_constraints[m] == 1) {
                if (machine_time[m] < earliest_time) {
                    earliest_time = machine_time[m];
                    best_machine = m;
                }
            }
        }
        
        if (best_machine != -1) {
            // Schedule the job on the selected machine
            printf("Job %d scheduled on Machine %d from time %d to %d\n", 
                   jobs[j].id, best_machine, 
                   machine_time[best_machine], 
                   machine_time[best_machine] + jobs[j].duration);
            
            // Update machine time
            machine_time[best_machine] += jobs[j].duration;
        } else {
            printf("Job %d cannot be scheduled on any machine!\n", jobs[j].id);
        }
    }
}

int main() {
    // Sample jobs with their constraints
    Job jobs[MAX_JOBS] = {
        {1, 5, {1, 0, 1, 0, 0}},  // Job 1, duration 5, can run on machines 0 and 2
        {2, 3, {0, 1, 0, 1, 0}},  // Job 2, duration 3, can run on machines 1 and 3
        {3, 7, {1, 1, 0, 0, 1}},  // Job 3, duration 7, can run on machines 0, 1, and 4
        {4, 2, {0, 0, 1, 1, 0}}   // Job 4, duration 2, can run on machines 2 and 3
    };
    
    int num_jobs = 4;
    int num_machines = 5;
    
    printf("Job Scheduling Using CSP Approach:\n");
    scheduleJobs(jobs, num_jobs, num_machines);
    
    return 0;
}