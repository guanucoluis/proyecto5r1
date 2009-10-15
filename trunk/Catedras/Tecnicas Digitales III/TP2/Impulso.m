% La señal impulso se define como:
% impulso[n-n0] = 1 para n = n0
% impulso[n-n0] = 0 para n != n0

% Definimos la cantidad de muestras
L=5;

% Vector para graficar el impulso
n= -L:1:L;

% Crear señal "impulso" y setear todos sus elementos a cero
impulso=zeros(size(n));

% Setear el elemento 0 en 1
impulso(n==0)=1;

% Le indico que voy a crear un obejto que va ser la figura numero 1
figure(1);

% Grafico en la figura 1 el impulso
stem(n,impulso,'r','fill');

% Seteo los ejes del grafico 
axis([-L L -0.5 1.5]);

title('Señal impulso unidad');
xlabel('n (muestras)');
ylabel('x[n]'); 

