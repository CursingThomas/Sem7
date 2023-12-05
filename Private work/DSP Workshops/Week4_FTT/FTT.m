close all;
%%Time specifications:
Fs = 128;                   % samples per second
dt = 1/Fs;                   % seconds per sample
StopTime = 0.25;             % seconds
t = (0:dt:StopTime-dt)';     % seconds

zReal = zeros(1,Fs);
zImag = zeros(1,Fs);

xReal = zeros(1,Fs);
xImag = zeros(1,Fs);

yReal = zeros(1,Fs);
yImag = zeros(1,Fs);

fftR= zeros(1,Fs);
fftI = zeros(1,Fs);


%%Sine wave:
angle = 0.02;
Fc = 60;
z = complex(1.0, 0.0);
z1 = complex(cos(2*pi/64), sin(2*pi/64));

x = complex(1.0, 0.0);
x1 = complex(cos(2*pi/128), sin(2*pi/128));

for i = 1:Fs
    z = z * z1;
    x = x * x1;
    xImag(i) = imag(x);
    xReal(i) = real(x);
    
    zImag(i) = imag(z);
    zReal(i) = real(z);
end


% Plot the signal versus time:

%% 128
figure;
subplot(2,1,1);
plot(xReal);
subplot(2,1,2);
plot(xImag);

xlabel('time (in seconds)');
title('Signal versus Time');
zoom xon;
%% 64
figure;
subplot(2,1,1);
plot(zReal);
subplot(2,1,2);
plot(zImag);

xlabel('time (in seconds)');
title('Signal versus Time');
zoom xon;

%% Addition of two (four) sinewaves.

for i = 1:Fs
    yImag(i) = zImag(i) + xImag(i);
    yReal(i) = zReal(i) + xReal(i);
end

figure;
subplot(2,1,1);
plot(yReal);
subplot(2,1,2);
plot(yImag);

xlabel('time (in seconds)');
title('Signal versus Time');
zoom xon;

%% FFT Analysis
figure;
subplot(2,1,1);
plot(abs(fft(yImag(1:64))));
subplot(2,1,2);
plot(abs(fft(yReal(1:128))));