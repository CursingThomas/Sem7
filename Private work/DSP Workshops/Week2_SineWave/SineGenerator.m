%%Time specifications:
Samplerate = 800;
timefactor = 5;
xReal = zeros(1,Samplerate * timefactor);
xImag = zeros(1,Samplerate * timefactor);

angle = 0.02;

    z1 = complex(1.0, 0.1);
    

for i = 1:(Samplerate * timefactor)
    z2 = complex(cos(angle), sin(angle));
    z1 = z1 * z2;
    angle = angle + 0.0001;
    xImag(i) = imag(z1);
    xReal(i) = real(z1);
end

figure;
plot(xImag);
hold on;
plot(xReal);

xlabel('time (in seconds)/Samplerate');
title('Signal vs Time');
zoom xon;s


