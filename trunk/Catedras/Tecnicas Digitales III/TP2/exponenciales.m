% Exponenciales tiempo discreto

figure(1);

L = 10;

% Exponencial Decreciente 1
% 0 < a < 1
a=0.5;
exp1 = zeros(1,L);
for n=0:L-1
    exp1(n+1)=a^n;
end

n=0:L-1;
subplot(2,2,1),
stem(n,exp1),
title('Exponencial Decreciente 1');

% Exponencial Decreciente 2
% -1 < a < 0
a=-0.5;
exp2 = zeros(1,L);
for n=0:L-1
    exp2(n+1)=a^n;
end

n=0:L-1;
subplot(2,2,2),
stem(n,exp2),
title('Exponencial Decreciente 2');

% Exponencial Creciente 1
% a > 1
a=2;
exp3 = zeros(1,L);
for n=0:L-1
    exp3(n+1)=a^n;
end

n=0:L-1;
subplot(2,2,3),
stem(n,exp3),
title('Exponencial Creciente 1');

% Exponencial Creciente 2
% a < -1
a=-2;
exp4 = zeros(1,L);
for n=0:L-1
    exp4(n+1)=a^n;
end

n=0:L-1;
subplot(2,2,4),
stem(n,exp4),
title('Exponencial Creciente 2');

