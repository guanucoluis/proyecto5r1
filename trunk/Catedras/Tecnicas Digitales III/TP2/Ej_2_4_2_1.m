% Reflexi�n de se�ales

x = [-5 -4 -3 -2 -1 0 1 2 3 4 5 ];

n=-5:5;
figure(1);

stem(n,x,'r');
hold;

n = -n;

stem(n,x,'b');
xlabel('Se�al original x[n](rojo), Se�al Reflejada y[-n] (azul)');