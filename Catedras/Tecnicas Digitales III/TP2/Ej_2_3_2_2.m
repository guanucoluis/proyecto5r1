% Muestreo y decimación de señales senoidales

A = 1;      % Amplitud
f0 = 100;   % Frecuencia de la senoide
fs = 10000; % Frec de muestreo en Hz
phi = 0;    % pi/2; % Fase
N = 100;    % Nueva cantidad de muestras para mantener la escala
n=0:N-1;

figure(1);

subplot(2,1,1);
y1=A*sin(2*pi*(f0/fs)*n+phi); % Señal senoidal
stem(n,y1,'r');
xlabel('fs = 10 KHz');
ylabel('y1[n]');

subplot(2,1,2);
y2 = interp(y1,2);
N = 200;
n=0:N-1;
stem(n,y2,'r');
axis([0 200 -1 1]);
xlabel('fs = 2,5 KHz');
ylabel('y2[n]');

