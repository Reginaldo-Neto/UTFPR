/* BANCO DE DADOS - ESPETARIA
ALUNO: REGINALDO GREGÓRIO DE SOUZA NETO
RA:2252813

LINK DO GIT-HUB: https://github.com/Reginaldo-Neto/BancoDeDados1.git

CORREÇÕES DA SEGUNDA ENTREGA:
-PORCOES deveria referenciar COZINHA (1:N); 
-SETORES deveria referenciar GERENTE; 
-ESPETOS deveria referenciar CHURRASQUEIRO; 
-FUNCIONARIOS deveria referenciar GERENTE e SETORES; 
-CLIENTES deveria referenciar MESA. 
/*CREATE DATABASE espetaria;		  COMANDO PARA CRIAR O BANCO DE DADOS*/
USE espetaria;						/*COMANDO PARA USAR O BANCO DE DADOS*/

drop table if exists SENTA;		/*DROPANDO RELACIONAMENTOS PARA EXECUTAR VAIRAS VEZES OS TESTES*/
drop table if exists ATENDE;
drop table if exists REALIZA;
drop table if exists ASSA;
drop table if exists GERENCIA_FUN;
drop table if exists GERENCIA_SET;
drop table if exists TRABALHA_EM;
drop table if exists PREPARA;
drop table if exists POSSUI;
drop table if exists VISUALIZA;

drop table if exists PORCOES;		/*DROPANDO TABELAS PARA EXECUTAR VAIRAS VEZES OS TESTES*/

drop table if exists PEDIDOS;
drop table if exists ESPETOS;

drop table if exists CHURRASQUEIRO;
drop table if exists GARCOM;
drop table if exists FUNCIONARIOS;

drop table if exists CAIXA;
drop table if exists COZINHA;
drop table if exists CHURRASQUEIRA;
drop table if exists SETORES;

drop table if exists GERENTE;

drop table if exists CLIENTES;
drop table if exists MESAS;



/* --------------------------------------------- TABELAS ----------------------------------------------*/

CREATE TABLE GERENTE(
	cod INTEGER,
    nome VARCHAR(100),
    comissao FLOAT,
    PRIMARY KEY(cod)
);

CREATE TABLE SETORES(
	cod INTEGER,
    nome VARCHAR(100),
    qtd_funcionarios INTEGER,
    cod_gerente INTEGER,
    FOREIGN KEY (cod_gerente) REFERENCES GERENTE(cod) ON DELETE CASCADE ON UPDATE NO ACTION,
    PRIMARY KEY(cod)
);

CREATE TABLE CAIXA(
	qtd_mesas_fechadas INT,
    saldo FLOAT,
    cod INTEGER,
    FOREIGN KEY (cod) references SETORES(cod) ON DELETE CASCADE ON UPDATE NO ACTION,
    PRIMARY KEY (cod)
);

CREATE TABLE COZINHA(
	qtd_porcoes_feitas INTEGER,
    capacidade_de_funcionarios INTEGER,
    cod INTEGER,
    FOREIGN KEY (cod) references SETORES(cod) ON DELETE CASCADE ON UPDATE NO ACTION,
    PRIMARY KEY (cod)
);

CREATE TABLE PORCOES(
	cod INTEGER,
    nome VARCHAR(100),
    valor FLOAT,
    cod_cozinha INTEGER,
    FOREIGN KEY (cod_cozinha) REFERENCES COZINHA(cod) ON DELETE CASCADE ON UPDATE NO ACTION,
    PRIMARY KEY(cod)
);

CREATE TABLE MESAS(
	num INTEGER,
    valor FLOAT,
    qtd_pessoas INTEGER,
    PRIMARY KEY(num)
); 

CREATE TABLE CHURRASQUEIRA(
	qtd_carvao_estoque INTEGER,
    qtd_espetos_assados INTEGER,
    cod INTEGER,
    FOREIGN KEY (cod) references SETORES(cod) ON DELETE CASCADE ON UPDATE NO ACTION,
    PRIMARY KEY (cod)
);

CREATE TABLE PEDIDOS(
	cod INTEGER,
    valor FLOAT,
    num_mesa INTEGER,
    FOREIGN KEY (num_mesa) references MESAS(num) ON DELETE CASCADE ON UPDATE NO ACTION,
    PRIMARY KEY(cod)
);

CREATE TABLE FUNCIONARIOS(
	cod INTEGER,
    nome VARCHAR(100),
    salario FLOAT,
    cod_gerente INTEGER,
    cod_setor INTEGER,
    FOREIGN KEY (cod_setor) REFERENCES SETORES(cod) ON DELETE CASCADE ON UPDATE NO ACTION, 
    FOREIGN KEY (cod_gerente) REFERENCES GERENTE(cod) ON DELETE CASCADE ON UPDATE NO ACTION,    
    PRIMARY KEY(cod)
);

CREATE TABLE CHURRASQUEIRO(
	qtd_de_espetos INTEGER,
    media_de_tempo FLOAT,
    nota FLOAT,
    cod INTEGER,
    FOREIGN KEY (cod) references FUNCIONARIOS(cod) ON DELETE CASCADE ON UPDATE NO ACTION,
    PRIMARY KEY (cod)
);

CREATE TABLE ESPETOS(
	cod INTEGER,
    nome VARCHAR(100),
    qtd_em_estoque INTEGER,
    cod_churrasqueiro INTEGER,
    FOREIGN KEY (cod_churrasqueiro) REFERENCES CHURRASQUEIRO(cod) ON DELETE CASCADE ON UPDATE NO ACTION,
    PRIMARY KEY(cod)
);

CREATE TABLE GARCOM(
	comissao FLOAT,
    nota FLOAT,
    num_mesas_atendidas INTEGER,
    cod INTEGER,
    FOREIGN KEY (cod) references FUNCIONARIOS(cod) ON DELETE CASCADE ON UPDATE NO ACTION,
    PRIMARY KEY (cod)
);

CREATE TABLE CLIENTES(
	cpf CHAR(11),
    nome VARCHAR(100),
    qtd_visitas INTEGER,
    num_mesa INTEGER,
    FOREIGN KEY (num_mesa) REFERENCES MESAS(num) ON DELETE CASCADE ON UPDATE NO ACTION, 
    PRIMARY KEY (cpf)
);



/* ---------------------------------------------- RELACIONAMENTO ------------------------------------------------------------------ */

CREATE TABLE SENTA(
	entrada INTEGER,
    saida INTEGER,
    cpf_cliente CHAR(11),
    num_mesa INTEGER,
    FOREIGN KEY (cpf_cliente) REFERENCES CLIENTES(cpf) ON DELETE CASCADE ON UPDATE NO ACTION,
    FOREIGN KEY (num_mesa) REFERENCES MESAS(num) ON DELETE CASCADE ON UPDATE NO ACTION,
    PRIMARY KEY (cpf_cliente, num_mesa)    
);

CREATE TABLE ATENDE(
    cpf_cliente CHAR(11),
    cod_garcom INTEGER,
    FOREIGN KEY (cpf_cliente) REFERENCES CLIENTES(cpf) ON DELETE CASCADE ON UPDATE NO ACTION,
    FOREIGN KEY (cod_garcom) REFERENCES GARCOM(cod) ON DELETE CASCADE ON UPDATE NO ACTION,
    PRIMARY KEY (cpf_cliente, cod_garcom)    
);

CREATE TABLE REALIZA(
    cod_pedido INTEGER,
    cod_garcom INTEGER,
    FOREIGN KEY (cod_pedido) REFERENCES PEDIDOS(cod) ON DELETE CASCADE ON UPDATE NO ACTION,
    FOREIGN KEY (cod_garcom) REFERENCES GARCOM(cod) ON DELETE CASCADE ON UPDATE NO ACTION,
    PRIMARY KEY (cod_pedido, cod_garcom)    
);

CREATE TABLE ASSA(
    cod_espeto INTEGER,
    cod_churrasqueiro INTEGER,
    FOREIGN KEY (cod_espeto) REFERENCES ESPETOS(cod) ON DELETE CASCADE ON UPDATE NO ACTION,
    FOREIGN KEY (cod_churrasqueiro) REFERENCES CHURRASQUEIRO(cod) ON DELETE CASCADE ON UPDATE NO ACTION,
    PRIMARY KEY (cod_espeto, cod_churrasqueiro)    
);

CREATE TABLE GERENCIA_FUN(
    cod_gerente INTEGER,
    cod_funcionario INTEGER,
    FOREIGN KEY (cod_gerente) REFERENCES GERENTE(cod) ON DELETE CASCADE ON UPDATE NO ACTION,
    FOREIGN KEY (cod_funcionario) REFERENCES FUNCIONARIOS(cod) ON DELETE CASCADE ON UPDATE NO ACTION,
    PRIMARY KEY (cod_gerente, cod_funcionario)    
);

CREATE TABLE GERENCIA_SET(
    cod_gerente INTEGER,
    cod_setor INTEGER,
    FOREIGN KEY (cod_gerente) REFERENCES GERENTE(cod) ON DELETE CASCADE ON UPDATE NO ACTION,
    FOREIGN KEY (cod_setor) REFERENCES SETORES(cod) ON DELETE CASCADE ON UPDATE NO ACTION,
    PRIMARY KEY (cod_gerente, cod_setor)    
);

CREATE TABLE TRABALHA_EM(
    cod_funcionario INTEGER,
    cod_setor INTEGER,
    FOREIGN KEY (cod_funcionario) REFERENCES FUNCIONARIOS(cod) ON DELETE CASCADE ON UPDATE NO ACTION,
    FOREIGN KEY (cod_setor) REFERENCES SETORES(cod) ON DELETE CASCADE ON UPDATE NO ACTION,
    PRIMARY KEY (cod_funcionario, cod_setor)    
);

CREATE TABLE PREPARA(
    cod_porcao INTEGER,
    cod_cozinha INTEGER,
    FOREIGN KEY (cod_porcao) REFERENCES PORCOES(cod) ON DELETE CASCADE ON UPDATE NO ACTION,
    FOREIGN KEY (cod_cozinha) REFERENCES COZINHA(cod) ON DELETE CASCADE ON UPDATE NO ACTION,
    PRIMARY KEY (cod_porcao, cod_cozinha)    
);

CREATE TABLE POSSUI(
    cod_porcao INTEGER,
    cod_espeto INTEGER,
    cod_pedido INTEGER,
    FOREIGN KEY (cod_porcao) REFERENCES PORCOES(cod) ON DELETE CASCADE ON UPDATE NO ACTION,
    FOREIGN KEY (cod_espeto) REFERENCES ESPETOS(cod) ON DELETE CASCADE ON UPDATE NO ACTION,
    FOREIGN KEY (cod_pedido) REFERENCES PEDIDOS(cod) ON DELETE CASCADE ON UPDATE NO ACTION,
    PRIMARY KEY (cod_porcao, cod_espeto, cod_pedido)    
);

CREATE TABLE VISUALIZA(
    cod_garcom INTEGER,
    cod_setor INTEGER,
    cod_pedido INTEGER,
    FOREIGN KEY (cod_garcom) REFERENCES GARCOM(cod) ON DELETE CASCADE ON UPDATE NO ACTION,
    FOREIGN KEY (cod_setor) REFERENCES SETORES(cod) ON DELETE CASCADE ON UPDATE NO ACTION,
    FOREIGN KEY (cod_pedido) REFERENCES PEDIDOS(cod) ON DELETE CASCADE ON UPDATE NO ACTION,
    PRIMARY KEY (cod_garcom, cod_setor, cod_pedido)    
);

/* ------------------------------------------------------------------------ INSERÇÃO DE DADOS ----------------------------------------------------------*/

INSERT INTO SETORES
(cod, nome, qtd_funcionarios) VALUES
(1, 'Churrasqueira', 1),
(2, 'Cozinha', 1),
(3, 'Caixa', 1),
(4, 'Pátio', 10);
INSERT INTO PORCOES 
(cod, nome, valor) VALUES 
(0, 'Molho de Alho', 0.50),
(1, 'Arroz', 2.50), 
(2, 'Vinagrete', 2.00), 
(3, 'Repolho', 2.00), 
(4, 'Farofa', 2.00),
(5, 'Mandioca', 0.00),
(6, 'Completo', 6.00),
(8, 'Simples', 2.00),
(9, 'Shoyu com Gengibre', 0.50),
(10, 'Bolinho de Mandioca', 10.00);

INSERT INTO MESAS
(num, valor, qtd_pessoas) VALUES
(1, 100.50, 2),
(2, 300, 4),
(3, 200.50, 3),
(4, 57, 1),
(5, 300, 3),
(6, 126, 4),
(7, 50, 1),
(8, 85, 2),
(9, 90.00, 1),
(10, 78.50, 2);

INSERT INTO CLIENTES 
(cpf, nome, qtd_visitas, num_mesa) VALUES 
(01234567890 , 'Aline', 1, 1),
(01234567891 , 'Bruno', 1, 2),
(01234567892 , 'Ana', 2, 3),
(01234567893, 'Clara', 2, 4),
(01234567894, 'José', 3, 5),
(01234567895, 'João', 1, 6),
(01234567896, 'André', 4, 7),
(01234567897, 'Sasha', 3, 8),
(01234567898, 'Felipe', 5, 9),
(01234567899, 'Cecília', 2, 10),
(09876543211, 'Geraldo', 1, 1),
(09876543212, 'Márcia', 3, 2),
(09876543213, 'Luís', 5, 3),
(09876543214, 'Catarina', 4, 4);

INSERT INTO GERENTE
(cod, nome, comissao) VALUES
(100, 'Reginaldo', 3000);

INSERT INTO FUNCIONARIOS 
(salario, nome, cod, cod_gerente, cod_setor) VALUES 
(1100.00, 'Jair', 10, 100, 4),
(1100.00, 'Claudia', 11, 100, 4),
(1100.00, 'Lucas', 12, 100, 4),
(1100.00, 'Marcio', 13, 100, 4),
(1100.00, 'Mateus', 14, 100, 4),
(1100.00, 'Luzia', 15, 100, 4),
(1100.00, 'Carla', 16, 100, 4),
(1100.00, 'Laura', 17, 100, 4),
(1100.00, 'Vivian', 18, 100, 4),
(1100.00, 'Guilherme', 19, 100, 4),
(1100.00, 'Ricardo', 20, 100, 1),
(1100.00, 'Celso', 21, 100, 1),
(1100.00, 'Sedano', 22, 100, 1),
(1100.00, 'Neto', 23, 100, 1),
(1100.00, 'Gregório', 24, 100, 1),
(1100.00, 'Oliveira', 25, 100, 1),
(1100.00, 'Perroni', 26, 100, 1),
(1100.00, 'Fiaux', 27, 100, 1),
(1100.00, 'Martins', 28, 100, 1),
(1100.00, 'Antonio', 29, 100, 1);

INSERT INTO GARCOM
(cod, comissao, nota, num_mesas_atendidas) VALUES
(10, 100, 5, 50),
(11, 80, 4, 12),
(12, 60, 3, 45),
(13, 40, 2, 14),
(14, 100, 5, 17),
(15, 80, 4, 83),
(16, 20, 1, 43),
(17, 40, 2, 73),
(18, 80, 4, 88),
(19, 60, 3, 22);

INSERT INTO CHURRASQUEIRO
(cod, nota, media_de_tempo, qtd_de_espetos) VALUES
(20, 5, 10, 500),
(21, 4, 12, 400),
(22, 3, 14, 300),
(23, 2, 16, 200),
(24, 1, 20, 100),
(25, 1, 20, 50),
(26, 2, 16, 100),
(27, 3, 14, 200),
(28, 4, 12, 300),
(29, 5, 10, 500);

INSERT INTO GERENCIA_FUN
(cod_gerente, cod_funcionario) VALUES
(100, 10),
(100, 11),
(100, 12),
(100, 13),
(100, 14),
(100, 15),
(100, 16),
(100, 17),
(100, 18),
(100, 19);

INSERT INTO GERENCIA_SET
(cod_gerente, cod_setor) VALUES
(100, 1),
(100, 2),
(100, 3);

INSERT INTO CAIXA
(qtd_mesas_fechadas, saldo, cod) VALUES
(250, 10000.00, 3);

INSERT INTO COZINHA
(qtd_porcoes_feitas, capacidade_de_funcionarios, cod) VALUES
(650, 4, 2);

INSERT INTO CHURRASQUEIRA
(cod, qtd_carvao_estoque, qtd_espetos_assados) VALUES
(1, 250, 3000);

INSERT INTO ESPETOS
(cod, nome, qtd_em_estoque, cod_churrasqueiro) VALUES
(1, 'Alcatra', 300, 20),
(2, 'Picanha', 50, 21),
(3, 'Maminha', 200, 22),
(4, 'Medalhão de Frango', 200, 23),
(5, 'Medalhão de Alcatra', 200, 24),
(6, 'Coração', 200, 25),
(7, 'Asa', 200, 26),
(8, 'Coxa', 200, 27),
(9, 'Pernil', 200, 28),
(10, 'Linguiça', 200, 29);

INSERT INTO PEDIDOS
(num_mesa, valor, cod) VALUES
(1, 100.50, 2510),
(2, 301, 2511),
(3, 200.50, 2512),
(4, 57, 2513),
(5, 300, 2514),
(6, 126, 2515),
(7, 50, 2516),
(8, 85, 2517),
(9, 90.00, 2518),
(10, 78.50, 2519);

INSERT INTO SENTA
(entrada, saida, cpf_cliente, num_mesa) VALUES
(19, 20, 01234567890, 1),
(19, 21, 01234567891, 2),
(20, 23, 01234567892, 3),
(20, 21, 01234567893, 4),
(21, 22, 01234567894, 5),
(21, 23, 01234567895, 6),
(19, 23, 01234567896, 7),
(22, 23, 01234567897, 8),
(19, 22, 01234567898, 9),
(21, 22, 01234567899, 10);

INSERT INTO ATENDE
(cpf_cliente, cod_garcom) VALUES
(01234567890, 10),
(01234567891, 11),
(01234567892, 12),
(01234567893, 13),
(01234567894, 14),
(01234567895, 15),
(01234567896, 16),
(01234567897, 17),
(01234567898, 18),
(01234567899, 19);

INSERT INTO REALIZA
(cod_pedido, cod_garcom) VALUES
(2510, 10),
(2511, 11),
(2512, 12),
(2513, 13),
(2514, 14),
(2515, 15),
(2516, 16),
(2517, 17),
(2518, 18),
(2519, 19);

/* --------------------------- CONSULTAS --------------------------------------
1) O NOME DOS CLIENTES SENTADOS NAS MESAS PARES*/
select c.nome 
from clientes c 
where c.cpf in (
	select s.cpf_cliente 
    from senta s 
    where num_mesa in(
		select m.num
        from mesas m
        where m.num%2=0));
        
/*------------------------------------------------------------
2) NOME DOS GARÇONS COM A MAIOR NOTA*/
select f.nome
from funcionarios f
where f.cod in(
	select g.cod
    from garcom g
    where g.nota >= ALL(
		select g1.nota
        from garcom g1));
        
/*------------------------------------------------------------
3) NOME DO GARÇOM QUE ATENDEU MAIOR QUANTIDADE DE MESAS*/
select f.nome
from funcionarios f
where f.cod in(
	select g.cod
    from garcom g
    where g.num_mesas_atendidas >= ALL(
		select g1.num_mesas_atendidas
        from garcom g1));
        
/*------------------------------------------------------------
4) NOME DO GARÇOM QUE ATENDEU MENOS MESAS 
E O NOME DO GARÇOM QUE TEM A MENOR NOTA*/
select f.nome
from funcionarios f
where f.cod in((
	select g.cod
    from garcom g
    where g.num_mesas_atendidas <= ALL( 
		select g1.num_mesas_atendidas
        from garcom g1))
        UNION
        select g.cod
		from garcom g
		where g.nota <= ALL(
			select g1.nota
			from garcom g1));
            
/*------------------------------------------------------------            
5) NOME DO CHURRASQUEIRO QUE É RESPONSAVEL POR ASSAR OS ESPETOS DE PICANHA*/
select f.nome
from funcionarios f
where f.cod in(
	select e.cod_churrasqueiro
    from espetos e
    where nome='Picanha');
    
/*------------------------------------------------------------            
6) NOME DOS CLIENTES QUE AINDA NÃO SENTARAM (NÃO ESTÃO CADASTRADOS NA TABELA SENTA)*/
select c.nome
from clientes c
where c.cpf NOT IN(
	select s.cpf_cliente
	from senta s);
    
/*------------------------------------------------------------    
7) NOME DOS FUNCIONÁRIOS QUE TRABALHAM NO "PÁTIO" (SÃO GARÇONS)*/
select f.nome
from funcionarios f
where f.cod_setor in(
	select s.cod
    from setores s
    where s.nome='Pátio');
    
/*------------------------------------------------------------  
8) NOME DO CLIENTE NA MESA MAIS CARA*/
select c.nome
from clientes c
where c.cpf in(
	select s.cpf_cliente
    from senta s
    where s.num_mesa in(
		select m.num
        from mesas m
        where m.valor >= ALL(
			select m1.valor
            from mesas m1)));
            
/*------------------------------------------------------------  
9) QUANTIDADE DE FUNCIONÁRIOS QUE O REGINALDO GERENCIA*/
select count(*) 
from funcionarios f
where cod_gerente = (
	select g.cod
    from gerente g
    where nome='Reginaldo');
    
/*------------------------------------------------------------  
10) O NOME DO CLIENTE QUE PERMANECEU MAIS TEMPO SENTADO*/
select c.nome
from clientes c
where c.cpf in(
	select s.cpf_cliente
    from senta s
    where s.saida-s.entrada >=ALL(
		select s1.saida-s1.entrada
        from senta s1
        where s1.saida-s1.entrada ));

/*CÓDIGO PARA OBSERVAR O CONTEÚDO DENTRO DAS TABELAS.
SELECT * FROM espetaria.porcoes;  <<<--- OBSERVAÇÃO: O código_cozinha DENTRO da tabela PORÇÕES está NULO pois o MySQL nao aceitou que eu inserisse o valor do código manualmente por se tratar de uma linha "filha" da tabela COZINHA.
SELECT * FROM espetaria.clientes;
SELECT * FROM espetaria.funcionarios;
SELECT * FROM espetaria.mesas;
SELECT * FROM espetaria.garcom;
SELECT * FROM espetaria.churrasqueiro;
SELECT * FROM espetaria.gerencia_fun;
SELECT * FROM espetaria.espetos;
SELECT * FROM espetaria.pedidos;
SELECT * FROM espetaria.senta;
SELECT * FROM espetaria.atende;
SELECT * FROM espetaria.realiza;
*/