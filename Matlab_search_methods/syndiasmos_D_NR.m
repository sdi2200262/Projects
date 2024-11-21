% Οι υλοποιήσεις των μεθόδων Διχοτόμισης, Newton-Raphson, Τέμνουσα

% Συνδιαστική Μέθοδος Διχοτόμισης και Newton-Raphson(NR)

function out = syndiasmos_D_NR(f, df, a, b, tolb, tolnr, nb,nnr)

%Πρώτα διχοτόμιση
fprintf("Αποτελέσματα Διχοτόμισης μέχρι %.10f\n ",tolb);

if f(a)*f(b)>0.0
error('function has same sign at end points')
end

a(1)=a;
b(1)=b;

i=1;

while i<=nb
     c(i)=(a(i)+b(i))/2;
     if  abs(f(c(i)))<tolb      
         break;
     end
     if f(a(i))*f(c(i))>0
        a(i+1)=c(i);
        b(i+1)=b(i);
     else
        a(i+1)=a(i);
        b(i+1)=c(i);
     end
     i=i+1;
end

if i>nb
    k=1:nb;
else
    k=1:i;
end

out=[k', a(k)', b(k)', c(k)', f(c(k))'];

fprintf('\nIteration        a            b            c               f(c)\n');
fprintf('------------------------------------------------------------------------\n');
for i = 1:size(out, 1)
    fprintf('%9d   %10.6f   %10.6f   %10.6f   %15.8f\n', out(i,1), out(i,2), out(i,3), out(i,4), out(i,5));
end

% Αποθήκευση τελευταίας προσέγγισης της μεθόδου Διχοτόμισης
x0 = c(i);

% Έπειτα Newton-Raphson
fprintf("\nΑποτελέσματα Newton-Raphson από %.10f μέχρι %.10f\n" + ...
    "Έχουμε ως αρχικό x0 το τελευταίο c της μεθόδου Διχοτόμισης\n ",tolb, tolnr);
x(1)=x0;
i=2;
while i<=nnr
    x(i)=x(i-1)-f(x(i-1))/df(x(i-1));
    if  abs(x(i)-x(i-1))<tolnr
        break;
    end
i = i + 1;
end
if i>nnr
    k=1:nnr;
else
    k=1:i;
end

% Το τελικό out περιέχει τα αποτελέσματα της μεθόδου Newton-Raphson
% Άρα στην  κλήση από την main θα επιστραφούν αυτά τα δεδομένα
% Μας χρησιμεύουν για την ολοκλήρωση του πίνακα 2 στο Ερώτημα 1.3
out=[k', x(k)', f(x(k))'];

fprintf('\nIteration       x(k)          f(k)\n');
fprintf('---------------------------------------------\n');
for i = 1:size(out, 1)
    fprintf('%9d   %10.6f   %10.6f\n', out(i,1), out(i,2), out(i,3));
end