/* BANCO DE DADOS - PROVA 2
ALUNO: REGINALDO GREGÓRIO DE SOUZA NETO
RA:2252813
*/
/*CREATE DATABASE Prova;		/*  COMANDO PARA CRIAR O BANCO DE DADOS*/
USE prova;	

drop table if exists Entidade_a;
drop table if exists Entidade_b;
drop table if exists tem;

create table Entidade_A(
	atributo_a1 INTEGER,
    atributo_a2 INTEGER,
    PRIMARY KEY (atributo_a1)
);

create table Entidade_B(
	atributo_b1 INTEGER,
    atributo_b2 INTEGER,
    PRIMARY KEY (atributo_b1)
);

create table Entidade_C(
	atributo_c1 INTEGER,
    atributo_c2 INTEGER,
    PRIMARY KEY (atributo_c1)
);

create table tem(
    atributo_a INTEGER,
    atributo_b INTEGER,
    atributo_c INTEGER,
    PRIMARY KEY (atributo_a, atributo_b, atributo_c),
    FOREIGN KEY (atributo_a) REFERENCES Entidade_A (atributo_a1),
    FOREIGN KEY (atributo_b) REFERENCES Entidade_B (atributo_b1),
    FOREIGN KEY (atributo_c) REFERENCES Entidade_C (atributo_c1)
);
/*
create table Entidade_A(
	atributo_a1 INTEGER,
    atributo_a2 INTEGER,
    PRIMARY KEY (atributo_a1)
);

create table Entidade_B(
	atributo_b1 INTEGER,
    atributo_b2 INTEGER,
    PRIMARY KEY (atributo_b1)
);

create table tem(
	atributo_rel INTEGER,
    atributo_a INTEGER,
    atributo_b INTEGER,
    PRIMARY KEY (atributo_b),
    FOREIGN KEY (atributo_a) REFERENCES Entidade_A (atributo_a1),
    FOREIGN KEY (atributo_b) REFERENCES Entidade_B (atributo_b1)    
);*/