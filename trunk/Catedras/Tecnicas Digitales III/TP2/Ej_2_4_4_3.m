% Multiplicaci�n de Se�ales discretas

x1 = [1 2 3 4 5 6]; 
x2 = [6 5 4 3 2 1]; 
  
n=0:5;

figure(1);

stem(n,x1,'r');
hold on;
stem(n,x2,'b');
hold on;

y = x1.*x2;

stem(n,y,'g');

xlabel('Se�al x1[n](rojo), Se�al x2[n] (azul), Se�al Producto x1*x2 (verde)');

