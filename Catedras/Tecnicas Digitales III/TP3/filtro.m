% Este script muestra como recibir un array de "fractional" del dsPIC por
% el puerto serie y transformarlo a un vector para ser utilizado en MATLAB.
% Cualquier cosa escribanme "Daniel Muñoz" <danymt01@gmail.com>
% Pásenlo a los compañeros que crean que les pueda servir, no tengo el mail
% de todos.

% Configura el puerto serie.
com1 = serial('COM1','BaudRate',115200,'DataBits',8,'StopBits',1);

% Abre el puerto serie con esa configuración para ser leído como un
% archivo.
fopen(com1);

% Numero de muestras "fractional" a recibir.
% Se espera que venga primero el bit menos significativo y luego el más
% significativo. Algo así sería el codigo en el dsPIC:
% for(i=0;i<NUMSAMP;i++){
%   putcUART1((unsigned char)(outputSignal[i]&0x00FF));
%   while(BusyUART1());
%	putcUART1((unsigned char)(((outputSignal[i]&0xFF00)>>8)));
%	while(BusyUART1());
% }
%
% outputSignal es el array de tipo fractional que contiene NUMSAMP
% muestras, que son el resultado el filtrado en el dsPIC.
%
% Aquí en MATLAB "num" debe ser igual a "NUMSAMP" en el dsPIC.
num=32;

% Asigno el tamaño que va a tener recibido. Aquí se van a recibir las
% muestras en formato fractional. Las inicializo a cero (no importa a
% cuanto, importa que se cree el vector, y zeros crea el vector).
recibido=zeros(1,num);

% Recibo las muestras y las guardo en recibido.
for x=1:num
    % Recibo de a dos bytes y rearmo el unsigned int de 16 bits.
    recibido(x)=fread(com1,1,'uint16');
end

% Cierro el puerto.
fclose(com1);

% Recupero el signo, que es el bit 15. Llevo lo que haya en el bit 15 al
% bit uno. Sería equivalente a esto en C:
% signo = (recibido&0x8000)>>15;
% Pero se aplica a todo el vector de una vez.
signo = bitshift(bitand(recibido,hex2dec('8000')),-15);

% Recupero el resto, sin el signo. Equivalente a:
% numero = recibido&0x7FFF;
% Pero se aplica a todo el vector de una vez.
numero = bitand(recibido,hex2dec('7FFF'));

% El formato fractional va de -1 a 1. El primer bit es el signo, que ya lo
% sacamos, así que lo que tenemos aquí es el módulo, que irá de 0 a 1. Por
% lo tanto divimos ese módulo, que actualmente va de 0 a 0x7FF por 0x7FFF.
% De esta forma dará siempre un valor entre 0 y 1.
% Lo aplicamos a todo el vector de una vez.
val = numero./hex2dec('7FFF');

% A continuación le restamos: 1 si era negativo, 0 si era positivo. Ese
% valor (0 ó 1) ya está en "signo", así que directamente restamos ambos
% vectores.
muestra = val-signo;

% Lo multiplicamos por 2.5 para acomodarlo al rango del dsPIC, que se
% supone que lo configuramos Vref- = 0V y Vref+=5V. El conversor devuelve
% -1V para una tensión de 0V, 0V para una tensión de 2,5V y 1V para una
% tensión de 5V. Por eso lo ajustamos.
muestra = muestra*2.5;

% Esta instrucción simplemente muestra los valores almacenados.
muestra

% OBSERVACIONES:
% Si a alguien no le funciona fíjese si está todo bien configurado. En mi
% máquina yo hago un get(com1) (el com1 es una variable, no importa como se
% llama, lo importante es que se le asignó el valor retornado por la 
% función "serial") y me tira:
% >> get(com1)
%     ByteOrder = littleEndian
%     BytesAvailable = 0
%     BytesAvailableFcn = 
%     BytesAvailableFcnCount = 48
%     BytesAvailableFcnMode = terminator
%     BytesToOutput = 0
%     ErrorFcn = 
%     InputBufferSize = 512
%     Name = Serial-COM1
%     ObjectVisibility = on
%     OutputBufferSize = 512
%     OutputEmptyFcn = 
%     RecordDetail = compact
%     RecordMode = overwrite
%     RecordName = record.txt
%     RecordStatus = off
%     Status = closed
%     Tag = 
%     Timeout = 10
%     TimerFcn = 
%     TimerPeriod = 1
%     TransferStatus = idle
%     Type = serial
%     UserData = []
%     ValuesReceived = 32
%     ValuesSent = 0

%     SERIAL specific properties:
%     BaudRate = 115200
%     BreakInterruptFcn = 
%     DataBits = 8
%     DataTerminalReady = on
%     FlowControl = none
%     Parity = none
%     PinStatus = [1x1 struct]
%     PinStatusFcn = 
%     Port = COM1
%     ReadAsyncMode = continuous
%     RequestToSend = off
%     StopBits = 1
%     Terminator = LF
%
% Otra cosa: este código está optimizado para ser entendido. Se podría
% optimizar para ejecución de la siguiente manera. Después de fclose(com1);
% simplemente se podría poner:
% muestra = (bitand(recibido,hex2dec('7FFF'))./hex2dec('7FFF'))-(bitshift(bitand(recibido,hex2dec('8000')),-15))
% Y eliminar todo el resto (no lo probé pero teóricamente...). Si no querés
% que se muestren las muestras ponele un punto y coma al final.