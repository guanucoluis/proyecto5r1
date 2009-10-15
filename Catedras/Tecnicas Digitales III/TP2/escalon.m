% La señal escalon unitario se define como:
% u[n]=1 para n > 0
% u[n]=0 para n< 0


L = 6;

% Vector para graficar el escalón
n= -L:1:L;

% Crear señal "escalon_unitario" y setear todos sus elementos a cero
escalon_unitario = zeros(size(n));

% Setear todos los elementos con n>=0 a 1
escalon_unitario(n>=0) = 1;

figure(1);

%Grafico en la figura 1 el escalón
stem(n,escalon_unitario);

axis([-L L -0.5 1.5]);
title('Señal escalón');
xlabel('n (muestras)');
ylabel('x[n]');  
 
