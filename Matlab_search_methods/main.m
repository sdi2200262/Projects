% Main: 
clc
clear

% ΔΕΔΟΜΈΝΑ

% Ορισμός μέγιστου αριθμού επαναλήψεων
nb = 50; % μέθοδος Διχοτόμισης
nnr = 50; % μέθοδος Newton-Raphson
nt = 50; % μέθοδος Τέμνουσας

% Ορισμός f1 και f1'
f1 = @(x) (x + 1).^3 .* (x - 2); 
df1 = @(x) 3.*(x + 1).^2 .* (x - 2) + (x + 1).^3; %παράγωγος f1

% Ορισμός f2 και f2'
f2 = @(x) exp(x) - x.^2 - 2; 
df2 = @(x) exp(x) - 2.*x; %παράγωγος f2

%Γραφηκή Παράσταση 
x = linspace(-3, 3, 500);
graphplot(x, f1, f2);

% Ορισμός τιμών ανεκτικότητας
tolb = 0.5 * 10^(-2); % Ανεκτικότητα για μέθοδο Διχοτόμισης
tolnr = 0.5 * 10^(-6); % Ανεκτικότητα για μέθοδο Newton-Raphson
tolt = 0.5 * 10^(-6); % Aνεκτικότητα για νλεθοδο Τέμνουσας
                      
% Αρχικά είχαμε βαλει 0.5 * 10^(-8) στο tolt όμως αυτό είχε ώς αποτέλεσμα 
% την αύξηση των επαναλήψεων χωρίς ουσιαστική αλλαγή στο αποτέλεσμα

% Άκρα διαστήματος για την προφανή ρίζα της f1: x = -1
a11 = -3;
b11 = 0;

% Άκρα διαστήματος για την προγανή ρίζα της f1: x = 2
a12 = 0;
b12 = 3;

% Η f2 δεν έχει προφανή ρίζα
% Για να βρούμε 2 άκρα διαστήματος της f2 στο οποίο θα περιέχεται ρίζα
% πρέπει για αυτές τις δύο τιμές να ισχύει η ιδιότητα Bolzano
% Παρατηρούμε οτι: f2(0) = -1<0 και f2(2) = e^2 -6 >0 
% Άρα έχουμε:
a2 = 0;
b2 = 2;


% ΑΠΑΝΤΉΣΕΙΣ ΕΡΩΤΗΜΑΤΩΝ
% ΕΡΩΤΗΜΑ 1.1
fprintf("Ερώτημα 1.1\n\n");
fprintf('ΕΠΑΝΑΛΗΠΤΙΚΗ ΜΕΘΟΔΟΣ D_NR\n\n');

% Κλήση συνάρτησης syndiasmos_D_NR για f1
% Πρώτα για την προφανή ρίζα x=-1
fprintf(['\n\nΨάχνουμε τη ρίζα της f1 κοντά στο x = -1...\n' ...
    'Ελέγχουμε το διάστημα [-3,0]\n\n']);
f1a_NR_results = syndiasmos_D_NR(f1, df1, a11, b11, tolb,tolnr, nb,nnr);
% Έπειτα για την προφανή ρίζα x=2
fprintf(['\n\n\nΨάχνουμε τη ρίζα της f1 κοντά στο x = 2...\n' ...
    'Ελέγχουμε το διάστημα [0,3]\n\n']);
f1b_NR_results = syndiasmos_D_NR(f1, df1, a12, b12, tolb,tolnr, nb,nnr);

% Κλήση συνάρτησης syndiasmos_D_NR για f2
fprintf('\n\n\nΨάχνουμε τη ρίζα της f2 μέσα στο διάστημα [0,2]...\n');
f2_NR_results = syndiasmos_D_NR(f2, df2, a2, b2, tolb,tolnr, nb,nnr);

%ΕΡΩΤΗΜΑ 1.2
fprintf("\n\n\n\nΕρώτημα 1.2\n");
fprintf("Πίνακας 1: Αποτελέσματα Συνδιασμού D NR\n\n");

% Τα δεδομένα εδώ είναι copy paste από το command window output
data = {
    '[-3,0]', -0.937500, -0.999999, 4+29;
    '[0,3]', 1.999878, 2.000000, 13+3;
    '[0,2]', 1.320312, 1.319074, 8+4
};

rowNames = {'f1   ', 'f1   ', 'f2   '};
colNames = {'[a,b]', 'x0', 'xn', 'n'};

fprintf('            ');
for j = 1:length(colNames)
    fprintf('%12s', colNames{j});
end
fprintf('\n');

for i = 1:size(data, 1)
    fprintf('%12s', rowNames{i}); 
    fprintf('%12s    ', data{i, 1}); 
    fprintf('%10.6f    ', data{i, 2:end});
    fprintf('\n');
end



%ΕΡΩΤΗΜΑ 1.3
fprintf("\n\n\n\nΕρώτημα 1.3\n");
fprintf("Πίνακας 2: Μελέτη Σύγκλισης f1 για ρίζα x=-1\n\n");

% Αυτόματη αντιγραφή δεδομένων Newton-Raphson για μελέτη σύγκλισης
n = 0:size(f1a_NR_results, 1) - 1; % Αριθμός εκτελέσεων
errors = abs(f1a_NR_results(:, 2) - f1a_NR_results(end, 2)); % Απόλυτο σφάλμα
p = 1;
ratios1 = [NaN; errors(2:end) ./ errors(1:end-1).^p]; % Ποσοστά με p=1
p = 2;
ratios2 = [NaN; errors(2:end) ./ errors(1:end-1).^p]; % Ποσοστά με p=2

% Τα δεδομένα εδώ είναι copy paste αυτόματα <3 κώδικας από πάνω
data = [n', errors, ratios1, ratios2];

% Display Results
fprintf('%10s %20s %20s %20s\n', 'n', '|ε_n|', '|ε_(n+1)/ε_n^1|', '|ε_(n+1)/ε_n^2|');
fprintf('-----------------------------------------------------------------------------\n');
for i = 1:size(data, 1)
    fprintf('%10d %20.10f %20.10f %20.10f\n', data(i, 1), data(i, 2), data(i, 3), data(i,4));
end


fprintf("\n\n\nΠίνακας 2: Μελέτη Σύγκλισης f1 για ρίζα x=2\n\n");

% Αυτόματη αντιγραφή δεδομένων Newton-Raphson για μελέτη σύγκλισης
n = 0:size(f1b_NR_results, 1) - 1; % Αριθμός εκτελέσεων
errors = abs(f1b_NR_results(:, 2) - f1b_NR_results(end, 2)); % Απόλυτο σφάλμα
p = 1;
ratios1 = [NaN; errors(2:end) ./ errors(1:end-1).^p]; % Ποσοστά με p=1
p = 2;
ratios2 = [NaN; errors(2:end) ./ errors(1:end-1).^p]; % Ποσοστά με p=2

% Τα δεδομένα εδώ είναι copy paste αυτόματα <3 κώδικας από πάνω
data = [n', errors, ratios1, ratios2];

% Display Results
fprintf('%10s %20s %20s %20s\n', 'n', '|ε_n|', '|ε_(n+1)/ε_n^1|', '|ε_(n+1)/ε_n^2|');
fprintf('----------------------------------------------------------------------------\n');
for i = 1:size(data, 1)
    fprintf('%10d %20.10f %20.10f %20.10f\n', data(i, 1), data(i, 2), data(i, 3), data(i,4));
end


fprintf("\n\n\nΠίνακας 2: Μελέτη Σύγκλισης f2 για άγνωστη ρίζα μέσα στο δίαστημα [0,2]\n\n");

% Αυτόματη αντιγραφή δεδομένων Newton-Raphson για μελέτη σύγκλισης
n = 1:size(f2_NR_results, 1) - 1; % Αριθμός εκτελέσεων
xn = f2_NR_results(:, 2); % Παίρνουμε την θέση x(k) από τα αποτελέσματα
differences = abs(xn(2:end) - xn(1:end-1)); % |x_(n+1) - x_n| Απόλυτο σφάλμα
p = 1;
ratios1 = [NaN; differences(2:end) ./ differences(1:end-1).^p]; % Ποσοστά με p=1
p = 2;
ratios2 = [NaN; differences(2:end) ./ differences(1:end-1).^p]; % Ποσοστά με p=2

% Τα δεδομένα εδώ είναι copy paste αυτόματα <3 κώδικας από πάνω
data = [n', differences, ratios1, ratios2];

% Display Results
fprintf('%10s %20s %20s %20s\n', 'n', '|x_{n+1} - x_n|', '(...)/(...)^1', '(...)/(...)^2');
fprintf('----------------------------------------------------------------------------\n');
for i = 1:size(data, 1)
    fprintf('%10d %20.10f %20.10f %20.10f\n', data(i, 1), data(i, 2), data(i, 3), data(i,4));
end


%ΕΡΩΤΗΜΑ 1.5
% Σε αυτό το ερώτημα οι μόνες αλλαγές κώδικα είναι κάποιες ονομασίες
% μεταβλητών και η κλήση της syndiasmos_D_T
% 
% Επομένως χρησιμοποιήσαμε τον παραπάνω κώδικα που γράψαμε γιαυτό κάποιες
% εντολές και κάποια σχόλια είναι ίδια...........
% Πρόκειται για αντιγραφή από τον εαυτό μας!

fprintf("\n\n\n\nΕρώτημα 1.5\n");
fprintf('ΕΠΑΝΑΛΗΠΤΙΚΗ ΜΕΘΟΔΟΣ D_T\n\n');


% Κλήση συνάρτησης syndiasmos_D_T για f1
% Πρώτα για την προφανή ρίζα x=-1
fprintf(['\n\nΨάχνουμε τη ρίζα της f1 κοντά στο x = -1...\n' ...
    'Ελέγχουμε το διάστημα [-3,0]\n\n']);
f1a_T_results = syndiasmos_D_T(f1, a11, b11, tolb,tolt, nb,nt);
% Έπειτα για την προφανή ρίζα x=2
fprintf(['\n\n\nΨάχνουμε τη ρίζα της f1 κοντά στο x = 2...\n' ...
    'Ελέγχουμε το διάστημα [0,3]\n\n']);
f1b_T_results = syndiasmos_D_T(f1, a12, b12, tolb,tolt, nb,nt);

% Κλήση συνάρτησης syndiasmos_D_NR για f2
fprintf('\n\n\nΨάχνουμε τη ρίζα της f2 μέσα στο διάστημα [0,2]...\n');
f2_T_results = syndiasmos_D_T(f2, a2, b2, tolb,tolt, nb,nt);


% Πίνακας ερωτήματος 1.2 με δεδομένα ερωτήματος 1.5
fprintf("\n\nΠίνακας ερωτήματος 1.2 με δεδομένα ερωτήματος 1.5\n");
fprintf("Αποτελέσματα Συνδιασμού D T\n\n");
% Τα δεδομένα εδώ είναι copy paste από το command window output
data = {
    '[-3,0]', -0.937500, -1.000001, 4+42;
    '[0,3]', 1.999878, 2.000000, 13+4;
    '[0,2]', 1.320312, 1.319074, 8+5
};

rowNames = {'f1   ', 'f1   ', 'f2   '};
colNames = {'[a,b]', 'x0', 'xn', 'n'};

fprintf('            ');
for j = 1:length(colNames)
    fprintf('%12s', colNames{j});
end
fprintf('\n');


for i = 1:size(data, 1)
    fprintf('%12s', rowNames{i}); 
    fprintf('%12s    ', data{i, 1}); 
    fprintf('%10.6f    ', data{i, 2:end});
    fprintf('\n');
end


%Πίνακες ερωτήματος 1.3 με δεδομένα ερωτήματος 1.5
fprintf("\n\n\nΠίνακες ερωτήματος 1.3 με δεδομένα ερωτήματος 1.5\n");
fprintf("Πίνακας 2: Μελέτη Σύγκλισης f1 για ρίζα x=-1\n\n");

% Αυτόματη αντιγραφή δεδομένων για μελέτη σύγκλισης
n = 0:size(f1a_T_results, 1) - 1; % Αριθμός εκτελέσεων
errors = abs(f1a_T_results(:, 2) - f1a_T_results(end, 2)); % Απόλυτο σφάλμα
p = 1;
ratios1 = [NaN; errors(2:end) ./ errors(1:end-1).^p]; % Ποσοστά με p=1
p = 2;
ratios2 = [NaN; errors(2:end) ./ errors(1:end-1).^p]; % Ποσοστά με p=2

% Τα δεδομένα εδώ είναι copy paste αυτόματα <3 κώδικας από πάνω
data = [n', errors, ratios1, ratios2];

% Display Results
fprintf('%10s %20s %20s %20s\n', 'n', '|ε_n|', '|ε_(n+1)/ε_n^1|', '|ε_(n+1)/ε_n^2|');
fprintf('-----------------------------------------------------------------------------\n');
for i = 1:size(data, 1)
    fprintf('%10d %20.10f %20.10f %20.10f\n', data(i, 1), data(i, 2), data(i, 3), data(i,4));
end


fprintf("\n\n\nΠίνακας 2: Μελέτη Σύγκλισης f1 για ρίζα x=2\n\n");

% Αυτόματη αντιγραφή δεδομένων  για μελέτη σύγκλισης
n = 0:size(f1b_T_results, 1) - 1; % Αριθμός εκτελέσεων
errors = abs(f1b_T_results(:, 2) - f1b_T_results(end, 2)); % Απόλυτο σφάλμα
p = 1;
ratios1 = [NaN; errors(2:end) ./ errors(1:end-1).^p]; % Ποσοστά με p=1
p = 2;
ratios2 = [NaN; errors(2:end) ./ errors(1:end-1).^p]; % Ποσοστά με p=2

% Τα δεδομένα εδώ είναι copy paste αυτόματα <3 κώδικας από πάνω
data = [n', errors, ratios1, ratios2];

% Display Results
fprintf('%10s %20s %20s %20s\n', 'n', '|ε_n|', '|ε_(n+1)/ε_n^1|', '|ε_(n+1)/ε_n^2|');
fprintf('----------------------------------------------------------------------------\n');
for i = 1:size(data, 1)
    fprintf('%10d %20.10f %20.10f %20.10f\n', data(i, 1), data(i, 2), data(i, 3), data(i,4));
end


fprintf("\n\n\nΠίνακας 2: Μελέτη Σύγκλισης f2 για άγνωστη ρίζα μέσα στο δίαστημα [0,2]\n\n");

% Αυτόματη αντιγραφή δεδομένων για μελέτη σύγκλισης
n = 1:size(f2_T_results, 1) - 1; % Αριθμός εκτελέσεων
xn = f2_T_results(:, 2); % Παίρνουμε την θέση x(k) από τα αποτελέσματα
differences = abs(xn(2:end) - xn(1:end-1)); % |x_(n+1) - x_n| Απόλυτο σφάλμα
p = 1;
ratios1 = [NaN; differences(2:end) ./ differences(1:end-1).^p]; % Ποσοστά με p=1
p = 2;
ratios2 = [NaN; differences(2:end) ./ differences(1:end-1).^p]; % Ποσοστά με p=2

% Τα δεδομένα εδώ είναι copy paste αυτόματα <3 κώδικας από πάνω
data = [n', differences, ratios1, ratios2];

% Display Results
fprintf('%10s %20s %20s %20s\n', 'n', '|x_{n+1} - x_n|', '(...)/(...)^1', '(...)/(...)^2');
fprintf('----------------------------------------------------------------------------\n');
for i = 1:size(data, 1)
    fprintf('%10d %20.10f %20.10f %20.10f\n', data(i, 1), data(i, 2), data(i, 3), data(i,4));
end
