% señal senodial

% Señal en tiempo continuo

% X(t) = A sen(W0*t+phi)

% Señal discreta t = nTs Ts periodo sampleo

% X[n] = A sen (W0*nTs+hi) = A sen(2*pi*f0/fs*n +phi) W0 = 2*pi*f0

% fn = f0/fs frec normailizada y fs frecunecia de muestreo

A = 10; % Amplitud
f0 = 50; % frec de la señal en Hz
fs = 5000; % frec de muestreo en Hz
phi = 0;%pi/2; %fase

N=200; %nuemero de muestras
n=0:N-1;

y=A*sin(2*pi*(f0/fs)*n+phi); % señal senoidal
figure(1);
stem(n,y,'r');

title('Señal senoidal 50Hz');

xlabel('n (muestras)');

ylabel('y[n]'); 
