% Initialize program
:- initialization(main).

% Disease facts: disease name, required symptoms, and cure
disease(flu, [fever, cough, dizziness], 'Rest, hydration, and over-the-counter medications').
disease(dengue, [fever, low_platelet], 'Hospitalization and platelet monitoring').
disease(measles, [fever, rash, cough], 'Vitamin A supplements and rest').
disease(malaria, [fever, chills, headache], 'Antimalarial medications').
disease(covid19, [fever, cough, fatigue], 'Isolation, rest, and hydration').
disease(asthma, [shortness_of_breath, wheezing], 'Inhalers and avoiding allergens').
disease(diabetes, [frequent_urination, extreme_hunger], 'Insulin and dietary changes').
disease(tuberculosis, [persistent_cough, chest_pain], 'Antibiotic treatment for 6 months').
disease(pneumonia, [cough, chest_pain, fatigue], 'Antibiotics and rest').
disease(hepatitis_b, [fatigue, jaundice, nausea], 'Antiviral medications and monitoring').

% Count number of matching symptoms
count_matches([], _, 0).
count_matches([Symptom|Rest], PatientSymptoms, Count) :-
    count_matches(Rest, PatientSymptoms, SubCount),
    (member(Symptom, PatientSymptoms) ->
        Count is SubCount + 1
    ;
        Count is SubCount
    ).

% Get all possible diagnoses with some matching symptoms
possible_diagnoses(PatientSymptoms, Matches) :-
    findall(
        disease(Disease, MatchCount, Cure),
        (
            disease(Disease, Symptoms, Cure),
            count_matches(Symptoms, PatientSymptoms, MatchCount),
            MatchCount > 0
        ),
        Matches
    ).

% Print the matches
print_matches([]).
print_matches([disease(Disease, MatchCount, Cure)|T]) :-
    write('Possible Disease: '), write(Disease), nl,
    write('Matching Symptoms: '), write(MatchCount), nl,
    write('Suggested Cure: '), write(Cure), nl, nl,
    print_matches(T).

% Main entry
main :-
    Symptoms = [fever, cough, dizziness],
    write('Your Symptoms: '), write(Symptoms), nl, nl,
    possible_diagnoses(Symptoms, Matches),
    ( Matches \= [] ->
        print_matches(Matches)
    ;
        write('No matching diseases found.'), nl
    ).
