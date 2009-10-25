% Muestreo de señales senoidales
 
A = 1;      % Amplitud
fs = 8000;   % Frec de muestreo en Hz
phi = 0;    % pi/2; % Fase
N = 100;    % Nueva cantidad de muestras para mantener la escala
n=0:N-1;
 
figure(1);
 
subplot(2,2,1);
f0 = 32100;
y1=A*sin(2*pi*(f0/fs)*n+phi); % Señal senoidal
stem(n,y1,'r');
xlabel('fo = 32100 Hz, fs = 8 KHz');
ylabel('y1[n]');
 
subplot(2,2,2);
f0 = 32225;
y2=A*sin(2*pi*(f0/fs)*n+phi); % Señal senoidal
stem(n,y2,'r');
xlabel('fo = 32225 Hz, fs = 8 KHz');
ylabel('y2[n]'); 
 
subplot(2,2,3);
f0 = 32350;
y3=A*sin(2*pi*(f0/fs)*n+phi); % Señal senoidal
stem(n,y3,'r');
xlabel('fo = 32350 Hz, fs = 8 KHz');
ylabel('y3[n]'); 
 
subplot(2,2,4);
f0 = 32475;
y4=A*sin(2*pi*(f0/fs)*n+phi); % Señal senoidal
stem(n,y4,'r');
xlabel('fo = 32475 Hz, fs = 8 KHz');
ylabel('y4[n]'); 