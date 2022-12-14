USE teste1;
drop table if exists FUNCIONARIOS_CONTRATADOS;
drop table if exists FUNCIONARIOS_HORISTAS;
drop table if exists FUNCIONARIOS;

CREATE TABLE FUNCIONARIOS(
	cpf CHAR(11),
    nome VARCHAR(100),
    vaga INTEGER,
    PRIMARY KEY (cpf)
);

CREATE TABLE FUNCIONARIOS_HORISTAS(
	cpf CHAR(11),
	salario_hora DECIMAL (10,2),
    horas_trabalhadas INTEGER,
    foreign key (cpf) REFERENCES FUNCIONARIOS(cpf) ON DELETE CASCADE,
	primary key (cpf)
);

CREATE TABLE FUNCIONARIOS_CONTRATADOS(
	cpf CHAR(11),
    id INTEGER,
    foreign key (cpf) REFERENCES FUNCIONARIOS (cpf) ON DELETE CASCADE,
    primary key (cpf)
);

INSERT INTO FUNCIONARIOS (cpf, nome, vaga) VALUES ('12345678900', 'Neto', 1), ('12345678901', 'Greg', 2);
INSERT INTO FUNCIONARIOS_HORISTAS (cpf, salario_hora, horas_trabalhadas) VALUES ('12345678900', 5.80, 40);
INSERT INTO FUNCIONARIOS_CONTRATADOS (cpf, id) VALUES ('12345678900', 1);

select * from FUNCIONARIOS_CONTRATADOS