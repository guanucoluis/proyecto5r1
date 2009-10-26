% Suma de Se�ales discretas

x1 = [0 1 1 1 1 0 ]; 
x2 = [0 1 2 3 4 5 ]; 
n=0:5;

figure(1);

stem(n,x1,'r');
hold on;
stem(n,x2,'b');
hold on;

y = x1+x2;

stem(n,y,'g');

xlabel('Se�al x1[n](rojo), Se�al x2[n] (azul), Se�al Suma x1+x2 (verde)');

