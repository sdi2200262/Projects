% Οι υλοποιήσεις των μεθόδων Διχοτόμισης, Newton-Raphson, Τέμνουσα

% Συνδιαστική Μέθοδος Διχοτόμισης και Τέμνουσας

function out = syndiasmos_D_T(f, a, b, tolb, tolt, nb, nt)

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
x0 = a(i);
x1 = b(i);

% Έπειτα Tέμνουσα
fprintf("\nΑποτελέσματα Τέμνουσας από %.10f μέχρι %.10f\n" + ...
    "Έχουμε ως αρχικά x0 και x1 τα τελευταία [a,b] της μεθόδου Διχοτόμισης\n ",tolb, tolt);
x(2)=x1;
x(1)=x0;
i=3;
ksi=1.1986912435;
while i<=nt
    x(i)=x(i-1)-(f(x(i-1))*(x(i-1)-x(i-2))/(f(x(i-1))-f(x(i-2))));
    eps(i)=abs(x(i)-ksi);
    conv_rate(i)=eps(i)/(eps(i-1).^(1.6));
    if  abs(x(i)-x(i-1))<tolt    %abs(f(x(i)))<tol
        break;
    end
i = i + 1;
end
if i>nt
    k=1:nt;
else
    k=1:i;
end

out=[k', x(k)', f(x(k))', eps(k)', conv_rate(k)'];


fprintf('\nIteration       x(k)          f(k)       eps(k)          conv_rate(k)\n');
fprintf('-------------------------------------------------------------------------------\n');
for i = 1:size(out, 1)
    fprintf('%9d   %10.6f   %10.6f   %10.6f   %10.6f\n', out(i,1), out(i,2), out(i,3), out(i,4), out(i,5));
end

