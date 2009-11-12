% Exponencial compleja
 
figure(1)
 
L=60;
 
r=0.9;
Xre = zeros(1,L);
Xim = zeros(1,L);
 
for n=0:L-1
    Xre(n+1)=(r^n)*cos((1/10)*n);
    Xim(n+1)=(r^n)*sin((1/10)*n);
end
 
n=0:L-1;
subplot(2,1,1),
stem(n,Xre),
title('Parte Real');
 
subplot(2,1,2),
stem(n,Xim),
title('Parte Imaginaria');