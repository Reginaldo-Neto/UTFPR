
imagem = imread('imagem.jpg');

novo_histograma = zeros(256, 1);

[M, N] = size(imagem);
total_pixels = M * N;
histograma = zeros(256, 1);

for i = 1:M
    for j = 1:N
        intensidade = imagem(i, j) + 1;
        histograma(intensidade) = histograma(intensidade) + 1;
    end
end

cdf = zeros(256, 1);
soma = 0;

for i = 1:256
    soma = soma + histograma(i);
    cdf(i) = soma / total_pixels;
end

imagem_equalizada = uint8(zeros(M, N));

for i = 1:M
    for j = 1:N
        intensidade = imagem(i, j) + 1;
        nova_intensidade = round(cdf(intensidade) * 255);
        imagem_equalizada(i, j) = nova_intensidade;
    end
end

histograma_equalizado = zeros(256, 1);

for i = 1:M
    for j = 1:N
        intensidade = imagem_equalizada(i, j) + 1;
        histograma_equalizado(intensidade) = histograma_equalizado(intensidade) + 1;
    end
end

subplot(2, 2, 1);
imshow(imagem);
title('Imagem Original');

subplot(2, 2, 2);
imshow(imagem_equalizada);
title('Imagem Equalizada');

imwrite(imagem_equalizada, 'imagem_equalizada.jpg');

subplot(2, 2, 3);
bar(0:255, histograma);
title('Histograma da Imagem Original');

subplot(2, 2, 4);
bar(0:255, histograma_equalizado);
title('Histograma da Imagem Equalizada');

csvwrite('histograma_equalizado.csv', histograma_equalizado);

figure;
plot(0:255, cdf);
axis([0 255 0 1]);
xlabel('Nível de Intensidade Original');
ylabel('Probabilidade Acumulada');
title('Função T(r) (CDF) após Equalização do Histograma');

