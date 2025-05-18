% --- Facts ---
parent(ravi, amit).
parent(ravi, sneha).
parent(usha, amit).
parent(usha, sneha).
parent(amit, ritu).
parent(amit, raj).
parent(pooja, ritu).
parent(pooja, raj).

male(ravi).
male(amit).
male(raj).
female(usha).
female(sneha).
female(ritu).
female(pooja).

% --- Rules ---
father(X, Y) :- parent(X, Y), male(X).
mother(X, Y) :- parent(X, Y), female(X).
sibling(X, Y) :- parent(Z, X), parent(Z, Y), X \= Y.
grandparent(X, Y) :- parent(X, Z), parent(Z, Y).

% --- Queries (hardcoded) ---
run :-
    write('--- Family Queries ---'), nl,

    write('Parents of Sneha: '), 
    findall(P, parent(P, sneha), Ps), write(Ps), nl,

    write('Children of Ravi: '), 
    findall(C, parent(ravi, C), Cs), write(Cs), nl,

    write('Siblings of Amit: '), 
    findall(S, sibling(amit, S), Sibs), write(Sibs), nl,

    write('Grandparents of Ritu: '), 
    findall(GP, grandparent(GP, ritu), GPs), write(GPs), nl,

    (mother(pooja, ritu) -> 
        write('Yes, Pooja is the mother of Ritu.'), nl
    ; 
        write('No, Pooja is not the mother of Ritu.'), nl
    ),

    nl, write('--- Additional Basic Queries ---'), nl,

    % Who is the father of Raj?
    (father(F, raj) -> format('Father of Raj is: ~w~n', [F]) ; write('No father found for Raj.'), nl),

    % Who is the mother of Amit?
    (mother(M, amit) -> format('Mother of Amit is: ~w~n', [M]) ; write('No mother found for Amit.'), nl),

    % Is Sneha sibling of Amit?
    (sibling(sneha, amit) -> write('Yes, Sneha is sibling of Amit.'), nl ; write('No, Sneha is not sibling of Amit.'), nl),

    % Is Ravi a grandparent of Ritu?
    (grandparent(ravi, ritu) -> write('Yes, Ravi is a grandparent of Ritu.'), nl ; write('No, Ravi is not a grandparent of Ritu.'), nl).

% --- Run when program starts ---
:- initialization(run).
