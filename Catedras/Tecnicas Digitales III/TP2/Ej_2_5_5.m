%{

    Convolucion Discreta

    Y[n] = X[n]*H[n]
    Y[n] = Sum{X[k]H[n-k]} para k=-inf a k=inf

    X[k] = señal de entrada
    H[n-k] = respuesta del sistema al impulso unitario
    
    Pasos a seguir para realizar la convoluion de y(n0) = Sum{X[k]H[n0-k]

    1) Tomamos h(k) y la reflejamos -> h(-k)
    2) Desplazamos h(-k) a h(n0-k) 
    3) Realizamos el producto de los dos vectores para cada uno de los valores de k
    4) Se hace la sumatoria de todos los productos para obtener el valor de y(n0)

%}

% Demostración de propiedades

x = [1 2 3 4 3 2 1];

h1 = [1 1 1];

h2 = [1 2 1];

n=-4:4;
n1=-3:3;
n2=-1:1;
n3=-5:5;
k=-20:20;

%Propiedad Conmutativa
y1=conv(x,h1); 
y2=conv(h1,x);

figure(1);
subplot(2,2,1);
stem(n1,x);
xlabel('x[n]');
subplot(2,2,2);
stem(n2,h1);
xlabel('h[n]');
subplot(2,2,3);
stem(n,y1);
xlabel('y1 = x[n] * h[n]');
subplot(2,2,4);
stem(n,y2);
xlabel('y2 = h[n] * x[n]');

%Propiedad Asociativa
y1=conv(x,h1); 
y2=conv(y1,h2);

y3=conv(h1,h2);
y4=conv(x,y3);

figure(2);
subplot(2,3,1);
stem(n1,x);
xlabel('x[n]');
subplot(2,3,2);
stem(n2,h1);
xlabel('h1[n]');
subplot(2,3,3);
stem(n2,h2);
xlabel('h2[n]');
subplot(2,3,4);
stem(n3,y2);
xlabel('y2 = (x[n] * h1[n]) * h2[n]');
subplot(2,3,5);
stem(n3,y4);
xlabel('y4 = x[n] * (h1[n] * h2[n])');

%Propiedad Distributiva
y1=h1 + h2; 
y2=conv(x,y1);

y3=conv(x,h1);
y4=conv(x,h2);
y5= y3 + y4;

figure(3);
subplot(2,3,1);
stem(n1,x);
xlabel('x[n]');
subplot(2,3,2);
stem(n2,h1);
xlabel('h1[n]');
subplot(2,3,3);
stem(n2,h2);
xlabel('h2[n]');
subplot(2,3,4);
stem(n,y2);
xlabel('y2 = x[n] * (h1[n] + h2[n])');
subplot(2,3,5);
stem(n,y5);
xlabel('y5 = x[n] * h1[n] + x[n] * h2[n]');



