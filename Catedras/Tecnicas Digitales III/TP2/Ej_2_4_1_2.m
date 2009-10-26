% Desplazamiento en el tiempo de señales

x = [0 3 2 1 0 1 2 3 0 ];
n=-4:4;
k=2;

figure(1);

stem(n,x,'r');
hold;

n = n-k;

stem(n,x,'b');

xlabel('Señal original x[n](rojo), Señal Desplazada y[n-2] (azul)');

