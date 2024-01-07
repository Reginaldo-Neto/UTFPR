pkg load image; % Apenas para Octave, remova esta linha se estiver usando MATLAB

% Ler a imagem colorida
img = imread('Imagem.jpg');

% Converter a imagem para double
img = im2double(img);

% Separar os canais de cor
redChannel = img(:,:,1); % Canal Vermelho
greenChannel = img(:,:,2); % Canal Verde
blueChannel = img(:,:,3); % Canal Azul

% Função para calcular e mostrar o espectro de Fourier
function showFourierSpectrum(channel, titleStr)
    F = fft2(channel); % Transformada de Fourier
    F = fftshift(F); % Centralizar o espectro
    F = abs(F); % Magnitude do espectro
    F = log(F+1); % Uso de log para melhor visualização
    F = mat2gray(F); % Normalização para visualização

    figure;
    imshow(F, []);
    title(titleStr);
end

% Mostrar o espectro para cada canal
showFourierSpectrum(redChannel, 'Espectro de Fourier - Canal Vermelho');
showFourierSpectrum(greenChannel, 'Espectro de Fourier - Canal Verde');
showFourierSpectrum(blueChannel, 'Espectro de Fourier - Canal Azul');

