numb = rand(100,1);
m = 10;
b = [1 , 1,1];

fir = filter(ones(m, 1)/m, 1, numb);
iir = movmean(numb, [9,1]);

figure;
plot(numb); 
hold on;
plot(fir);
hold on;
plot(iir);
legend('Original', 'fir', 'iir');

figure;
stem(fir);

figure;
stem(iir);

