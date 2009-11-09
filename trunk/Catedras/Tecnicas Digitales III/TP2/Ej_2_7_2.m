
fs = 100;
N = 1024;
n=0:N-1;
fo= 20;

%{ Senoide
senoide= sin(2*pi*(fo/fs)*n);

% Calcula la fft
Yfft = fft(senoide);
%}
% Triangular
triangular=tripuls(N);

fs = 10000;
t = -1:1/fs:1;
w = .4;
x = tripuls(t,w);

%Cuadrada

figure(1);


Hz = fs*(n/N);
subplot(2,1,1),stem(Hz,abs(Yfft)),title('Absoluto'); 
subplot(2,1,2),stem(Hz,angle(Yfft)),title('Angulo');


% senoides

figure(2);

for i=1:4
    Y= sin(2*pi*(fo*i/fs)*n);
    Yfft = fft(Y);
    Hz = fs*(n/N);
    subplot(2,2,i),stem(Hz,abs(Yfft));
end

