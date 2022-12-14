%Plotar gráfico 
 syms('OK', 'P0', 'P1', 'TOL', 'NO', 'FLAG', 'NAME', 'OUP', 'F0');
 syms('I', 'F1', 'P', 'FP','s','x');
 TRUE = 1;
 FALSE = 0;
 fprintf(1,'Plotar gráfico para encontrar a raiz\n');
 fprintf(1,'Insira a função f(x) em termos de  x\n');
 fprintf(1,'Por exemplo, cos(x)-x\n');
 s = input(' ');
 F = inline(s,'x');
 
 OK = FALSE;
 
 fprintf(1,'Insira as extremidades a < b em linhas separadas\n');
 P0 = input(' ');
 P1 = input(' ');
 if P0 > P1 
 X = P0;
 P0 = P1;
 P1 = X;
 
 end
  
%  if P0 == P1 
%  fprintf(1,'a não pode ser igual a b\n');
%  else
%  FA = F(P0);
%  FB = F(P1);
%  if FA*FB > 0
%  fprintf(1,'f(a) e f(b) têm o mesmo sinal. \n');
%  else
%  OK = TRUE;
%  if FA*FB<0
%       fprintf(1,'Temos que f(a)*f(b) < 0 . \n');
     x1=P0:.1:P1;
 title('Gráfico de f(x)');
 plot(x1,F(x1),'LineWidth', 1.5);
  title('Gráfico de f(x)');
 grid on
 

  
