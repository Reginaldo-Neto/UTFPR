x=input('Insira os valores de x na tabela:\n ');
y=input('Insira os valores de y na tabela:\n ');
u=input('Insira o a ser interpolado:\n ');
L=0;
n = length(x); % n ́umero de elementos do vetor x.
P = 0; % define o valor inicial de P;
for i = 1 : n
    L(i) = 1;
    for j = 1 : n
        if j~=i
        L(i) = L(i)*(u-x(j))/(x(i)-x(j));
        end
    end
    P = P + y(i)*L(i);
end
disp(P)