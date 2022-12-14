USE teste1;

DROP TABLE IF EXISTS CONCLUIDA;
DROP TABLE IF EXISTS MATRICULA;

DROP TABLE IF EXISTS CURSOS_TEM_DISCIPLINAS;
DROP TABLE IF EXISTS ALUNOS;
DROP TABLE IF EXISTS CURSOS;
DROP TABLE IF EXISTS DEPARTAMENTOS;
DROP TABLE IF EXISTS PREREQUISITOS;
DROP TABLE IF EXISTS DISCIPLINAS;

CREATE TABLE DEPARTAMENTOS(
	codigo INTEGER,
	detalhes VARCHAR(100),
    PRIMARY KEY (codigo)
);

CREATE TABLE CURSOS(
	nome VARCHAR(100),
    cod_dpto INTEGER NOT NULL,
    FOREIGN KEY (cod_dpto) REFERENCES DEPARTAMENTOS(codigo),
    PRIMARY KEY(nome)
);

CREATE TABLE ALUNOS(
	num INTEGER,
    nome VARCHAR(100),
    nome_curso VARCHAR(100),
    FOREIGN KEY (nome_curso) REFERENCES CURSOS(nome),
    PRIMARY KEY(num)
);

CREATE TABLE DISCIPLINAS(
	nome VARCHAR(100),
    ch INTEGER,
    ementa VARCHAR(200),
     PRIMARY KEY (nome)
);

CREATE TABLE MATRICULA(
	nome_disciplina VARCHAR(100),
    num_aluno INTEGER,
    FOREIGN KEY (nome_disciplina) REFERENCES DISCIPLINAS(nome),
    FOREIGN KEY (num_aluno) REFERENCES ALUNOS(num),
    PRIMARY KEY(nome_disciplina, num_aluno)
);

CREATE TABLE CONCLUIDA(
	nome_disciplina VARCHAR(100),
    num_aluno INTEGER,
    FOREIGN KEY (nome_disciplina) REFERENCES DISCIPLINAS(nome),
    FOREIGN KEY (num_aluno) REFERENCES ALUNOS(num),
    PRIMARY KEY(nome_disciplina, num_aluno)
);

CREATE TABLE PREREQUISITOS(
	nome_disciplina1 VARCHAR(100),
    nome_disciplina2 VARCHAR(100),
    FOREIGN KEY(nome_disciplina1) REFERENCES  DISCIPLINAS(nome),
    FOREIGN KEY(nome_disciplina2) REFERENCES  DISCIPLINAS(nome),
    PRIMARY KEY(nome_disciplina1, nome_disciplina2)
);

CREATE TABLE CURSOS_TEM_DISCIPLINAS(
	tipo ENUM('Optativa', 'Obrigatória'),
	nome_curso VARCHAR(100),
	nome_disciplina VARCHAR(100),
    FOREIGN KEY (nome_curso) REFERENCES CURSOS(nome),
    FOREIGN KEY (nome_disciplina) REFERENCES DISCIPLINAS(nome),
    PRIMARY KEY (nome_curso, nome_disciplina)
);

INSERT INTO DEPARTAMENTOS (codigo, detalhes) VALUES(1, 'DACOM'), (2, 'DACOC');
INSERT INTO CURSOS (nome, cod_dpto) VALUES('Ciência da Computação', 1), ('Engenharia Civil', 2);

INSERT INTO ALUNOS (num, nome, nome_curso) 
	VALUES (1, 'Joao Tiago', 'Ciência da Computação'), 
		(2, 'Maria Eduardo', 'Engenharia Civil');
INSERT INTO DISCIPLINAS(nome) VALUES ('BD1'),('BD2');
INSERT INTO MATRICULA(nome_disciplina, num_aluno) VALUES ('bd1', 1), ('bd1', 2), ('bd2', 1);