pkg load image;
imagem = imread('imagem.jpg');
histograma = imhist(imagem);
cdf = cumsum(histograma) / sum(histograma);
imagem_equalizada = uint8(255 * cdf(double(imagem) + 1));

figure;
plot(0:255, cdf);
axis([0 255 0 1]);
xlabel('Nível de Intensidade Original');
ylabel('Probabilidade Acumulada');
title('Função T(r) (CDF) após Equalização do Histograma');

imwrite(imagem_equalizada, 'imagem_equalizada.jpg');

figure;
imshow(imagem_equalizada);
title('Imagem Equalizada');

figure;
imhist(imagem_equalizada);
title('Histograma da Imagem Equalizada');


csvwrite('histograma_equalizado.csv', histograma);

