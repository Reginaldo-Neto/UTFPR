
% %This is for inputs
% m=inputdlg('Enter the function to be integrated:');   
% s=m{:};                                         
% d=str2func(['@(x)' s]);                         
% f=str2func(['@(x)' vectorize(s)]) 
% a=input('The lower limit is:');
% b=input('The upper limit is:');
clc;clear;
syms('NAME', 'OUP', 'I', 'P', 'Q','x','s');
 TRUE = 1;
 FALSE = 0;
 disp(' Quadratura de Gauss');
a=input('Digite o limite inferior "a", por exemplo 1: '); % exmple a=1
 b=input('Digite o limite superior "b", por exemplo 1.5: ');  % exmple b=2
  fprintf(1,'Insira a função f(x) em termos de  x\n');
 fprintf(1,'Por exemplo, exp(-x^2)\n');
 s = input(' ');
 f = inline(s,'x');
 
point=0;
while point==0
point=input('Escolha o valor de n para o método( 2 <= n <=6):\n');
if point<2||point>6
    point=0;
    fprintf('Entrada errada! Escolha um valor entre 2 e 6.\n\n');
end
end
a0=(b+a)/2;
a1=(b-a)/2;
if point==2
x0=a0+(a1*(-1/(sqrt(3))));
x1=a0+(a1*(1/(sqrt(3))));
fx0=a1*f(x0);
fx1=a1*f(x1);
I=fx0+fx1;
end
if point==3
    x0=a0+(a1*-0.774596669);
    x1=a0;
    x2=a0+(a1*0.774596669);
    fx0=a1*f(x0);
    fx1=a1*f(x1);
    fx2=a1*f(x2);
    I=(0.5555556*fx0)+(0.8888889*fx1)+(0.5555556*fx2);
end
if point==4
    x0=a0+(a1*-0.861136312);
    x1=a0+(a1*-0.339981044);
    x2=a0+(a1*0.339981044);
    x3=a0+(a1*0.861136312);
    fx0=a1*f(x0);
    fx1=a1*f(x1);
    fx2=a1*f(x2);
    fx3=a1*f(x3);
    I=(0.3478548*fx0)+(0.6521452*fx1)+(0.6521452*fx2)+(0.3478548*fx3);
end
if point==5
    x0=a0+(a1*-0.906179846);
    x1=a0+(a1*-0.538469310);
    x2=a0;
    x3=a0+(a1*0.538469310);
    x4=a0+(a1*0.906179846);
    fx0=a1*f(x0);
    fx1=a1*f(x1);
    fx2=a1*f(x2);
    fx3=a1*f(x3);
    fx4=a1*f(x4);
    I=(0.2369269*fx0)+(0.4786287*fx1)+(0.5688889*fx2)+(0.4786287*fx3)+(0.2369269*fx4);
end
if point==6
    x0=a0+(a1*-0.932469514);
    x1=a0+(a1*-0.661209386);
    x2=a0+(a1*-0.238619186);
    x3=a0+(a1*0.238619186);
    x4=a0+(a1*0.661209386);
    x5=a0+(a1*0.932469514);
    fx0=a1*f(x0);
    fx1=a1*f(x1);
    fx2=a1*f(x2);
    fx3=a1*f(x3);
    fx4=a1*f(x4);
    fx5=a1*f(x5);
    I=(0.1713245*fx0)+(0.3607616*fx1)+(0.4679139*fx2)+(0.4679139*fx3)+(0.3607616*fx4)+(0.1713245*fx5);
end
%Interpretation of results
fprintf('\n Usando %.0f-pontos para Quadratura de Gauss a integral é aproximadamente %.10f\n',point,I);