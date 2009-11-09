
x = [0 1 -1 0 0 1 2 1 0 0 0 1 0 -1 0]; 
y = [1 2 1]; 

L = 15+3-1;

rxy = zeros(1,L);

for n=1:L;
    m=3-n+1;
    for k=1:n
        if m>=1 & k<=15
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

