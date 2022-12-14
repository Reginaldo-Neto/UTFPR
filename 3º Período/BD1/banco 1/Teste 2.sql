USE teste1;
drop table if exists DEPENDENTES;
drop table if exists FUNCIONARIOS;
CREATE TABLE FUNCIONARIOS(
	cpf CHAR(11),
    nome VARCHAR(100),
    vaga INTEGER,
    PRIMARY KEY (cpf)
);

CREATE TABLE DEPENDENTES(
	cpf_fun CHAR(11),
	nome VARCHAR(100),
    idade INTEGER,
    FOREIGN KEY (cpf_fun) REFERENCES FUNCIONARIOS(cpf) ON DELETE CASCADE,
    PRIMARY KEY (cpf_fun, nome)
);
	
INSERT INTO FUNCIONARIOS (cpf, nome, vaga) VALUES ('12345678900', 'Neto', 1), ('12345678901', 'Greg', 2);
INSERT INTO DEPENDENTES (cpf_fun, nome, idade) VALUES ('12345678900','Netin', 10), ('12345678901','Greguin', 11);

