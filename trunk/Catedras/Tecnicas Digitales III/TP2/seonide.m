% Muestreo de señales senoidales

A = 1;      % Amplitud
fs = 197;   % Frec de muestreo en Hz
phi = 0;    % pi/2; % Fase
N = 100; % Nueva cantidad de muestras para mantener la escala
n=0:N-1;

figure(1);

subplot(2,1,1);
y1=A*sin(2*pi*(f0/fs)*n+phi); % Señal senoidal
stem(n,y1,'r');
xlabel('fs = 190 Hz');
ylabel('y1[n]'); 
subplot(2,1,2);
plot(n,y1);
xlabel('fs = 190 Hz');
ylabel('y1[n]'); 

%Señal sin aliasing
figure(2);
subplot(2,1,1);
N = 100; % Nueva cantidad de muestras para mantener la escala
fs = 1000;  % Nueva frec de muestreo en Hz
y2=A*sin(2*pi*(f0/fs)*n+phi); % Señal senoidal
stem(n,y2,'r');
xlabel('fs = 1000 Hz');
ylabel('y2[n]'); 
subplot(2,1,2);
plot(n,y2);
xlabel('fs = 1000 Hz');
ylabel('y2[n]'); 
