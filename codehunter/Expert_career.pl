% Helper predicate: Find intersection of two lists
intersection([], _, []).
intersection([H|T], List2, [H|Result]) :-
    member(H, List2),  % Check if H is in List2
    intersection(T, List2, Result).
intersection([_|T], List2, Result) :-
    intersection(T, List2, Result).

% Helper predicate: Remove duplicates from a list
remove_duplicates([], []).
remove_duplicates([H|T], Result) :-
    member(H, T), !,
    remove_duplicates(T, Result).
remove_duplicates([H|T], [H|Result]) :-
    remove_duplicates(T, Result).

% Knowledge Base
% Career paths based on interests and skills
career(sports, "Professional Athlete or Sports Coach").
career(arts, "Graphic Designer or Fine Artist").
career(technology, "Software Developer or Data Scientist").
career(healthcare, "Doctor or Nurse").
career(business, "Entrepreneur or Business Analyst").
career(law, "Lawyer or Legal Consultant").
career(science, "Research Scientist or Lab Technician").
career(education, "Teacher or Educational Consultant").
career(writing, "Author or Content Writer").
career(music, "Musician or Music Producer").
career(engineering, "Mechanical, Civil, or Software Engineer").
career(higher_studies, "Researcher or Academician pursuing advanced degrees").
career(dance, "Choreographer or Dance Instructor").

% Matching interests to categories
interest_category([sports, fitness], sports).
interest_category([drawing, painting, design], arts).
interest_category([coding, technology, problem_solving], technology).
interest_category([medicine, helping_others, biology], healthcare).
interest_category([management, leadership, finance], business).
interest_category([justice, debating, critical_thinking], law).
interest_category([experiments, curiosity, research], science).
interest_category([teaching, mentoring, learning], education).
interest_category([writing, reading, storytelling], writing).
interest_category([music, singing, composing], music).
interest_category([engineering, machines, innovation], engineering).
interest_category([studies, research, academia, knowledge], higher_studies).
interest_category([dancing,choreography], dance).

% Main Predicate with hardcoded inputs
career_guidance :-
    write('Welcome to the Career Guidance System!'), nl,
    
    % Example 1: Technology interests
    write('Example 1:'), nl,
    write('Please list your interests as a Prolog list, e.g., [coding, painting, fitness]: [coding, technology]'), nl,
    process_interests([coding, technology]),
    
    % Example 2: Arts and Sports interests
    write('Example 2:'), nl,
    write('Please list your interests as a Prolog list, e.g., [coding, painting, fitness]: [painting, drawing, fitness]'), nl,
    process_interests([painting, drawing, fitness]),
    
    % Example 3: Science and Education interests
    write('Example 3:'), nl,
    write('Please list your interests as a Prolog list, e.g., [coding, painting, fitness]: [research, experiments, teaching]'), nl,
    process_interests([research, experiments, teaching]),
    
    % Example 4: No matching interests
    write('Example 4:'), nl,
    write('Please list your interests as a Prolog list, e.g., [coding, painting, fitness]: [flying, teleportation]'), nl,
    process_interests([flying, teleportation]).

% Process the interests and display results
process_interests(Interests) :-
    (   find_careers(Interests, Careers),
        Careers \= []
    ->  write('Based on your interests, potential career paths could be:'), nl,
        print_careers(Careers)
    ;   write('Sorry, we could not determine a suitable career for your interests.'), nl
    ),
    nl.

% Find unique matching careers
find_careers(Interests, UniqueCareersList) :-
    findall(Career, (
        interest_category(InterestList, Category),
        intersection(Interests, InterestList, Matches),
        Matches \= [],  % Ensure there is at least one match
        career(Category, Career)
    ), CareersList),
    remove_duplicates(CareersList, UniqueCareersList).

% Print the list of careers
print_careers([]).
print_careers([Career|Rest]) :-
    format('- ~s~n', [Career]),
    print_careers(Rest).

% Entry point
start :-
    career_guidance.

% Initialization directive
:- initialization(start).
