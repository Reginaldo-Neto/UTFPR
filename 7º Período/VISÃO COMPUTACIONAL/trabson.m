pkg load image;

% Carregando a imagem
img = imread('Imagem.jpg');
img = im2double(img);

% A dimensão da transformada é 2*M x 2*N
[M, N] = size(img);

% Zero padding
F = fft2(img, 2*M, 2*N);

% Centralizar a transformada de Fourier movendo a frequência zero para o centro da matriz
F = fftshift(F);
% Aplicar transformação logarítmica para visualização
spectro = log(1 + abs(F));

% Normalizar os valores para o intervalo [0,1]
spectro = mat2gray(spectro);

figure(1);
imshow(spectro);
colormap('jet'); % Aplicar um mapeamento de cores
colorbar; % Opcional: adicionar uma barra de cores para referência
title('Espectro de Fourier');

% Para salvar, pode ser necessário converter de volta para o intervalo de 8 bits
imwrite(im2uint8(spectro), 'espectro.png');

% Carregando Filtro Notch
notch = im2double(imread('mask_red.png'));
notch = imresize(notch, [2*M, 2*N], 'bicubic', 'Antialiasing', true);

% Filtro Notch na Transformada de Fourier
transformada_notch = F .* notch;

% Invertendo a Transformada de Fourier
Inversa = ifftshift(transformada_notch);
img2 = ifft2(Inversa);

% Tirar zero padding
img2 = img2(1:M, 1:N);

% Salvar a imagem resultante
imwrite(abs(img2), "resultado.png");

figure(2);
imshow(abs(img2));
title('Resultado');

