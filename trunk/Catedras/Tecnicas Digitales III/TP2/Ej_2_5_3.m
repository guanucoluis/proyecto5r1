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

% Convolución hecha manualmente

Lx = input('Ingrese numero de Muestras X=');
x=zeros(1,Lx);

x = input('Ingrese las Muestras de X( entre [] separadas por comas)=');

Lh = input('Ingrese numero de Muestras H=');
h=zeros(1,Lh);

h = input('Ingrese las Muestras de H( entre [] separadas por comas)=');

y = zeros(1,Lx+Lh-1);

for n=1:Lx+Lh-1;
    y(n)=0;
    for k=1:Lh
        if(n-k)>=0
            if(n-k)<Lx
                y(n)=y(n)+(h(k)*x(n-k+1));
            end
        end
    end
end

% La calculo con la funcion de MAtlab

y1=conv(x,h); 

n=1:Lx;
figure(1);
subplot(2,2,1);
stem(n,x);
title('X(n)');
n=1:Lh;
subplot(2,2,2);
stem(n,h);
title('H(n)');
n=1:Lh+Lx-1;
subplot(2,2,3);
stem(n,y);
title('Y(n)=X(n)*H(n) calculada');
subplot(2,2,3);
stem(n,y);
title('Y(n)=X(n)*H(n) calculada');
subplot(2,2,4);
stem(n,y1);
title('Y1(n)=X(n)*H(n) por conv');






