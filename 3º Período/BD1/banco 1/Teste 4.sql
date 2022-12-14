USE teste1;

drop table if exists FINANCIA;
drop table if exists DEPARTAMENTOS1;
drop table if exists PROJETOS1;
drop table if exists FUNCIONARIOS1;
CREATE TABLE FUNCIONARIOS1(
	cpf CHAR(11),
    nome VARCHAR(100),
    vaga INTEGER,
    PRIMARY KEY (cpf)
);

CREATE TABLE PROJETOS1(
	inicio DATE,
    orcamento INTEGER,
    id INTEGER,
    PRIMARY KEY (id)
);

CREATE TABLE DEPARTAMENTOS1(
	inicio DATE,
    orcamento INTEGER,
    id INTEGER,
    PRIMARY KEY (ID)
);

CREATE TABLE FINANCIA(
	id_projeto INTEGER,
    id_departamento INTEGER,
    foreign key (id_projeto) references PROJETOS1 (id),
    foreign key (id_departamento) references DEPARTAMENTOS1 (id),
    PRIMARY KEY (id_projeto, id_departamento)
);

CREATE TABLE MONITORA(
	cpf_fun CHAR(11),
    id_projeto INTEGER,
    id_departamento INTEGER,
    ate DATE,
    PRIMARY KEY(cpf, id_projeto, id_departamento),
    FOREIGN KEY (cpf_fun) REFERENCES FUNCIONARIOS1,
    foreign key (id_projeto, id_departamento) REFERENCES FINANCIA(id_projeto, id_departamento)
);