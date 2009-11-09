% Tren de impulsos

P = 5;
L = 100;
M = L/P;
tren_imp=zeros(1,L);
for n=0:L-1
    for i=0:M-1
        if n==(i*P)
            tren_imp(n+1)=1;
        end
    end
end

figure(1);
n=0:L-1;
stem(n,tren_imp);

title('Señal Tren de Impulsos'); 

% Tambien se puede hacer con las siguientes líneas 

tren_imp=[1;0;0;0;0;0;0;0;0;0]*ones(1,M);
tren_imp=tren_imp(:)';

figure(2);
stem(n,tren_imp);

title('Señal Tren de Impulsos'); 
