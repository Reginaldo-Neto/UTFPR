clc;clear;
syms('NAME', 'OUP', 'I', 'P', 'Q','x','s');
 TRUE = 1;
 FALSE = 0;
 disp(' Regra 3/8 de Simpson');
a=input('Digite o limite inferior "a", por exemplo 0: '); % exmple a=1
 b=input('Digite o limite superior "b", por exemplo 6: ');  % exmple b=2
  fprintf(1,'Insira os valores de f(x) de sua tabela:\n');
 fprintf(1,'Por exemplo, [.21 .32 .42 .51 .82 0.91 1.12]\n');
 s = input(' ');
 n = length(s)-1;
%  n=input('insira o número de subintervalos n: '); % exmple n=21
 h=(b-a)/n;
if rem(n,3)~=0
   fprintf('\n Digite um valor válido de n!!!'); 
   n=input('\n Digite n como sendo um múltiplo de 3: ');
end
 fprintf(' \t %8s \t %13s\n','x','f(x)');
 fprintf(' \t %3f \t %7.10f\n',a,s(1));
for k=1:1:n
  x(k)=a+k*h;
  y(k)=s(k+1);
    fprintf(' \t %3f \t %7.10f\n',x(k),y(k)); 
end
 so=0;sm3=0;% Formula:  (3h/8)*[(y0+yn)+2*(y3+y6+..multiple of 3 terms)+3*(y1+y2+y4+y5+...remining terms)]
for k=1:1:n-1
    if rem(k,3)==0
       sm3=sm3+y(k); %sum of multiple of 3 terms 
     else
     so=so+y(k);%sum of others terms 
    end
end
answer=(3*h/8)*(s(1)+s(end)+3*so+2*sm3);
% xi = a:h:b;
% f_1sets = sum(s(2:3:end-1));  
% f_2sets = sum(s(3:2:end-3));
% I = 3*h/8*(s(1) + 3*f_1sets + 2*f_2sets + s(end));
 fprintf('\n O valor da integral é aproximadamente %7.10f',answer); % exmple The value of integration is 0.381665
