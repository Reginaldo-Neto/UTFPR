a=input('\n Digite a condição inicial x0=a: ');
y0=input('\n Digite o valor de y0: ');
b=input('\n Insira o valor de b: ');
h=input('\n Digite o valor de h: ');
x = a:h:b; % d
% iscretização do intervalo [a,b] com passo h;
y = zeros(size(x)); 
% obt́em uma matriz coluna nula; 
% aqui o comando size(x) retorna um vetor linha
%cujos elementos s ̃ao os comprimentos das dimens̃oes 
% correspondentes de x;

y(1) = y0; % define-se o dado inicial;
n = (b-a)/h; % define o n ́umero de subintervalos n;
for i=1:n+1
y(i+1) = y(i)+h*f(x(i),y(i)) ;
aproximacao = y(i);
end
fprintf('Aproximação: %4.10f', aproximacao)