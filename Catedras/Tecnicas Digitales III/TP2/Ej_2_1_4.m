% Señal senoidal
 
% Señal en tiempo continuo
% X(t) = A sen(W0*t+phi)
 
% Señal discreta -> t = nTs, donde Ts es el período de muestreo
% X[n] = A sen (W0*nTs+hi) = A sen(2*pi*f0/fs*n +phi) W0 = 2*pi*f0
% fn = f0/fs es la frecuencia normalizada y fs la frecuencia de muestreo
 
A = 10;     % Amplitud
f0 = 10;    % Frec de la señal en Hz
fs = 1000;  % Frec de muestreo en Hz
phi = 0;    % pi/2; % Fase
 
N=100; % Número de muestras
n=0:N-1;
 
y=A*sin(2*pi*(f0/fs)*n+phi); % Señal senoidal
figure(1);
stem(n,y,'r');
 
title('Señal Senoidal de 10Hz');
xlabel('n (muestras)');
ylabel('y[n]'); 