% Escalado de Frecuencia (submuestreo)

A = 1;      % Amplitud
f0 = 50;    % Frecuencia de la Se�al
fs = 1000;  % Frec de muestreo en Hz
phi = 0;    % pi/2; % Fase
N = fs/f0 + 1;    % Nueva cantidad de muestras para mantener la escala
a = 2;      % Factor de escalado
n=0:N-1;

figure(1);

x=A*sin(2*pi*(f0/fs)*n+phi); % Se�al senoidal
stem(n,x,'r');
hold;

n=a*n;
stem(n,x,'b');

xlabel('Se�al original x[n](rojo), Se�al Escalada y[2*n] (azul)');

