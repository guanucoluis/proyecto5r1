
% Convolucion-Deconvolucion

x = [1 0 1 4 3 -1 1];

h = [2 0 -3];

n=-4:4;
n1=-3:3;
n2=-1:1;
n3=-5:5;
k=-20:20;

%Convolucion de x(excitación) con h(kernel)
y=conv(x,h); 

%Deconvolucion de y(salida) con h(kernel) para obtener x(excitación)
[x1,r] = deconv(y,h);

figure(1);
subplot(2,2,1);
stem(n1,x);
xlabel('x[n]');
subplot(2,2,2);
stem(n2,h);
xlabel('h[n]');
subplot(2,2,3);
stem(n,y);
xlabel('y = x[n] * h[n]');
subplot(2,2,4);
stem(n1,x1);
xlabel('x1 = deconv(y,h)');

