% Escalado de Amplitud

x = [1 2 3 4 5 4 3 2 1]; 
n=-4:4;
A=2;

figure(1);

stem(n,x,'r');
hold;

y = A*x;

stem(n,y,'b');

xlabel('Se�al original x[n](rojo), Se�al Escalada A*x[n] (azul)');

