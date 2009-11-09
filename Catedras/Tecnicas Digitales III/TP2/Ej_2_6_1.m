%{

    Correlacion Cruzada de 2 señales 

    RXY[l] = Sum{X[n]Y[n-l]}  n=i N-|K|-1  para i=l K=0 l >=0  i=0 k=l l<0 
    RXY[l] = Sum{X[n+l]Y[n]}  

Ejemplo 
X = [0,1,-1,0,0,1,2,1,0,1,0] 15
Y = [1,2,1] 3

%}

% Ejemplo para verificar la tecnica

Lx = input('Ingrese numero de Muestras X=');

x=zeros(1,Lx);

x = input('Ingrese las Muestras de X( entre [] separadas por comas)=');

Ly = input('Ingrese numero de Muestras Y=');

y=zeros(1,Ly);

y = input('Ingrese las Muestras de Y( entre [] separadas por comas)=');

L = Lx+Ly-1;

rxy = zeros(1,L);

for n=1:L;
    m=Ly-n+1;
    for k=1:n
        if m>=1 & k<=Lx
          rxy(n)=rxy(n)+(x(k)*y(m));
        end
    m=m+1;    
    end
end

% La calculo con la funcion de MAtlab

rxy1=xcorr(x,y); 

figure(1);
subplot(2,2,1);
stem(x);
title('X(n)');
subplot(2,2,2);
stem(y);
title('Y(n)');
subplot(2,2,3);
stem(rxy);
title('RXY(n) calculada');
subplot(2,2,4);
stem(rxy1);
title('RXY1(n) por matlab');

