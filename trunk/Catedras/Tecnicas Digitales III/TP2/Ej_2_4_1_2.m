% Desplazamiento en el tiempo de se�ales

x = [0 3 2 1 0 1 2 3 0 ];
n=-4:4;
k=2;

figure(1);

stem(n,x,'r');
hold;

n = n-k;

stem(n,x,'b');

xlabel('Se�al original x[n](rojo), Se�al Desplazada y[n-2] (azul)');

