% Reginaldo Gregório de Souza Neto
% 2252813
pkg load image
imagem = imread('pratica6.png');
imagem_double = im2double(imagem);
[m, n] = size(imagem_double);
transformada = fft2(imagem_double, m, n);
% Resposta da 4:
% A dimensão da transformada 2D é igual às dimensões da imagem original, que são 256x256 pixels,
% pois eu especifiquei no argumento da função o "m" e o "n".

transformada_centralizada = fftshift(transformada);
espectro = uint8(abs(transformada_centralizada));
figure;
imshow(espectro, []);
title('Espectro de Fourier');
[P, Q] = size(transformada_centralizada);
D0 = 20;

% Prof, aqui eu mantive D0=20 porque foi o que você pediu no enunciado do PDF, entretanto
% quando usei D0=10 o filtro ficou mais parecido com o seu e a imagem ficou mais borrada também,
% se assemelhando mais com a imagem no PDF

[u, v] = meshgrid(1:Q, 1:P);

% Aqui eu usei meshgrid (coisa que a professora não explicou em sala ainda)
% para criar matrizes 2D de coordenadas (X, Y) que serão usadas na construção
% do filtro passa-baixa gaussiano.

D = sqrt((u - P/2).^2 + (v - Q/2).^2);
H = exp(-D.^2 / (2 * D0^2));

figure;
imshow(H, []);
title('Filtro Passa-Baixa Gaussiano');
transformada_filtrada = transformada_centralizada .* H;
transformada_descentralizada = ifftshift(transformada_filtrada);
imagem_filtrada = ifft2(transformada_descentralizada);
imagem_final = real(imagem_filtrada);
M = size(imagem, 1);
N = size(imagem, 2);
imagem_final = imagem_final(1:M, 1:N);
imagem_final = im2uint8(imagem_final);
figure;
imshow(imagem_final, []);
title('Imagem Final');


