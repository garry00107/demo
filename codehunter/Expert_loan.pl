% -----------------------------
% Loan Approval Expert System
% -----------------------------

% --- Loan Eligibility Criteria ---
min_income(30000).
min_credit_score(650).
max_debt_ratio(0.4).

% --- Interest Rates for Loan Types ---
interest(home_loan, 6.5).
interest(car_loan, 8.5).

% --- Eligibility Conditions ---
eligible(Income, Credit, Debt, employed) :-
    min_income(MinI), Income >= MinI,
    min_credit_score(MinC), Credit >= MinC,
    DebtRatio is Debt / Income,
    max_debt_ratio(MaxR), DebtRatio =< MaxR.

% --- EMI Calculation Formula ---
emi(Amount, Rate, Months, EMI) :-
    R is Rate / (12 * 100),
    F is (1 + R) ** Months,
    EMI is Amount * R * F / (F - 1).

% --- Rounding Utility to 2 Decimal Places ---
round_2(X, Y) :- Y is round(X * 100) / 100.

% --- Rejection Reasoning ---
reason(Income, Credit, Debt, Job) :-
    (Income < 30000 ->
        write('Reason: Income below minimum requirement ($30000).'), nl ; true),
    (Credit < 650 ->
        write('Reason: Credit score below 650.'), nl ; true),
    R is Debt / Income,
    max_debt_ratio(MaxR),
    (R > MaxR ->
        format('Reason: Debt-to-income ratio (~2f) exceeds allowed maximum (0.4).~n', [R]) ; true),
    (Job \= employed ->
        write('Reason: Applicant must be employed.'), nl ; true).

% --- Main Execution ---
check_loan :-
    % ===== Modify These Inputs for Testing =====
    Income = 75000,
    Credit = 720,
    Debt = 20000,
    Job = employed,
    Loan = home_loan,
    Amount = 250000,
    Months = 240,

    % ===== Display Inputs =====
    write('========================================='), nl,
    write('        Loan Application Summary         '), nl,
    write('========================================='), nl,
    format('Annual Income       : $~w~n', [Income]),
    format('Credit Score        : ~w~n', [Credit]),
    format('Total Existing Debt : $~w~n', [Debt]),
    format('Employment Status   : ~w~n', [Job]),
    format('Loan Type Requested : ~w~n', [Loan]),
    format('Loan Amount         : $~w~n', [Amount]),
    format('Tenure              : ~w months~n', [Months]),
    write('-----------------------------------------'), nl, nl,

    % ===== Eligibility Check & Result =====
    ( eligible(Income, Credit, Debt, Job) ->
        write('Loan Approved!'), nl,
        interest(Loan, Rate),
        emi(Amount, Rate, Months, EMI),
        round_2(EMI, EMI2),
        format('Interest Rate       : ~w%%~n', [Rate]),
        format('Monthly EMI         : $~2f~n', [EMI2])
    ;
        write('Loan Not Approved.'), nl,
        reason(Income, Credit, Debt, Job)
    ).

% --- Auto-run on file load ---
:- initialization(check_loan).
