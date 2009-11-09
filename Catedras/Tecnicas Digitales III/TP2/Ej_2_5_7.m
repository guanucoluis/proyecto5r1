
A = 10;      % Amplitud
f0 = 100;   % Frecuencia de la senoide
fs = 10000; % Frec de muestreo en Hz
phi = 0;    % pi/2; % Fase
N = 1000;   % Cantidad de muestras para 10 ciclos de la señal

%Respuesta al impulso
h = [0.0040  0.0045  0.0060  0.0083  0.0115  0.0155  0.0202  0.0253  0.0306  0.0361  0.0414  0.0463  0.0507  0.0543  0.0570  0.0586  0.0592  0.0586  0.0570  0.0543  0.0507  0.0463  0.0414  0.0361  0.0306  0.0253 0.0202 0.0155   0.0115   0.0083   0.0060   0.0045  0.0040];

n=0:N-1;

seno=A*sin(2*pi*(f0/fs)*n+phi); % Señal senoidal
ruido=4*(-1).^round(10*rand(1,N)).*rand(1,N);
senoruido = seno + ruido;

convolucion = conv(senoruido,h);

figure(1);
subplot(2,1,1), plot(senoruido,'b'), axis([0 N -15 15]);
subplot(2,1,2), plot(convolucion,'r'), grid on, axis([0 N -15 15]);

[p,W]=freqz(convolucion,senoruido);

figure(2);
subplot(4,1,4);
freqz(h),title('Respuesta en frecuencia');
