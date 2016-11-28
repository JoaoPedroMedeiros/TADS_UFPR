/*============================================================*/
/* Script de criação das tabelas
/* Banco de dados: MySQL
/* Criador: João Pedro Medeiros
/* Versão 1
/*============================================================*/

START TRANSACTION;

CREATE TABLE Atleta                (
  cd_atleta INT          NOT NULL PRIMARY KEY AUTO_INCREMENT,
  nm_atleta VARCHAR(100) NOT NULL            ,
  nr_rg     BIGINT       NOT NULL            ,
  nr_cpf    BIGINT       NOT NULL            ,
  id_sexo   CHAR         NOT NULL            ,
  id_estran BIT(1)       NOT NULL            ,
  nr_passap BIGINT       NULL                ,
  dt_nasc   DATE         NOT NULL            ,
  ds_email  VARCHAR(100) NOT NULL            ,
  nr_tel    BIGINT       NOT NULL            ,
  nm_login  VARCHAR(50)  NOT NULL            ,
  ds_senha  VARCHAR(50)  NOT NULL
);
CREATE TABLE Maratona              (
  cd_marat  INT          NOT NULL PRIMARY KEY AUTO_INCREMENT,
  dt_marat  DATE         NOT NULL            ,
  ds_local  VARCHAR(100) NOT NULL
);
CREATE TABLE Modalidade            (
  cd_mod   INT           NOT NULL PRIMARY KEY,
  ds_mod   VARCHAR(50)   NOT NULL            ,
  nr_dist  INT           NOT NULL            ,
  cd_marat INT           NOT NULL            ,
  FOREIGN KEY (cd_marat) REFERENCES Maratona (cd_marat) ON DELETE RESTRICT
);
CREATE TABLE Categoria             (
  cd_categ  INT          NOT NULL PRIMARY KEY AUTO_INCREMENT,
  ds_categ  VARCHAR(50)  NOT NULL            ,
  id_sexcat CHAR         NOT NULL            ,
  nr_idamin TINYINT      NOT NULL            
);
CREATE TABLE Modalidade_Categorias (
  cd_mod   INT           NOT NULL            ,
  cd_categ INT           NOT NULL            ,
  PRIMARY KEY (cd_mod, cd_categ)             ,
  FOREIGN KEY (cd_mod  ) REFERENCES Modalidade (cd_mod  ) ON DELETE RESTRICT,
  FOREIGN KEY (cd_categ) REFERENCES Categoria  (cd_categ) ON DELETE RESTRICT
);
CREATE TABLE Kit                   (
  cd_kit    INT          NOT NULL PRIMARY KEY,
  ds_kit    VARCHAR(50)  NOT NULL
);
CREATE TABLE Participacao          (
  nr_ident  BIGINT        NOT NULL   PRIMARY KEY, 
  cd_atleta INT           NOT NULL              ,
  cd_mod    INT           NOT NULL              ,
  cd_categ  INT           NOT NULL              ,
  cd_kit    INT           NOT NULL              ,
  id_taman  CHAR(2)       NOT NULL              ,
  nr_tempin DATETIME      NULL                  ,
  nr_tempfi DATETIME      NULL                  ,
  FOREIGN KEY (cd_atleta) REFERENCES Atleta    (cd_atleta) ON DELETE RESTRICT,
  FOREIGN KEY (cd_mod   ) REFERENCES Modalidade(cd_mod   ) ON DELETE RESTRICT,
  FOREIGN KEY (cd_categ ) REFERENCES Categoria (cd_categ ) ON DELETE RESTRICT,
  FOREIGN KEY (cd_kit   ) REFERENCES Kit       (cd_kit   ) ON DELETE RESTRICT
);

CREATE TABLE Pagamento             (
  cd_pag    BIGINT        NOT NULL   PRIMARY KEY AUTO_INCREMENT,
  nr_ident  BIGINT        NOT NULL,
  vl_tot    NUMERIC(17,2) NOT NULL,
  cd_cartao BIGINT        NOT NULL,
  cd_seg    INT           NOT NULL,
  dt_venc   DATE          NOT NULL,
  nm_titul  VARCHAR(100)  NOT NULL,
  FOREIGN KEY (nr_ident)  REFERENCES Participacao(nr_ident) ON DELETE RESTRICT
);

CREATE TABLE Maratona_Kits         (
  cd_marat  INT           NOT NULL            ,
  cd_kit    INT           NOT NULL            , 
  vl_kit    NUMERIC(17,2) NOT NULL            , 
  PRIMARY KEY (cd_marat, cd_kit)              ,
  FOREIGN KEY (cd_marat) REFERENCES Maratona(cd_marat) ON DELETE RESTRICT,
  FOREIGN KEY (cd_kit)   REFERENCES Kit     (cd_kit)   ON DELETE RESTRICT
);
CREATE TABLE Item                  (
  cd_item   INT          NOT NULL PRIMARY KEY AUTO_INCREMENT,
  ds_item   VARCHAR(50)  NOT NULL
);
CREATE TABLE Kit_Items             (
  cd_kit    INT          NOT NULL            ,
  cd_item   INT          NOT NULL            ,
  PRIMARY KEY (cd_kit, cd_item)              ,
  FOREIGN KEY (cd_kit ) REFERENCES Kit (cd_kit)  ON DELETE RESTRICT,
  FOREIGN KEY (cd_item) REFERENCES Item(cd_item) ON DELETE RESTRICT
);
CREATE TABLE Parentesco            (
  cd_parent INT          NOT NULL PRIMARY KEY AUTO_INCREMENT,
  ds_parent VARCHAR(50)  NOT NULL
);
CREATE TABLE Conhecido             (
  cd_atleta INT          NOT NULL            ,
  cd_conhec INT          NOT NULL            ,
  nr_tel    BIGINT       NOT NULL            ,
  nm_conhec VARCHAR(100) NOT NULL            ,
  cd_parent INT          NOT NULL            ,
  PRIMARY KEY (cd_atleta, cd_conhec)         ,
  FOREIGN KEY (cd_parent) REFERENCES Parentesco(cd_parent)  ON DELETE RESTRICT
);

ROLLBACK;

/* DROP TABLE IF EXISTS Modalidade_Categorias; */
/* DROP TABLE IF EXISTS Pagamento            ; */
/* DROP TABLE IF EXISTS Participacao         ; */
/* DROP TABLE IF EXISTS Modalidade           ; */
/* DROP TABLE IF EXISTS Categoria            ; */
/* DROP TABLE IF EXISTS Atleta               ; */
/* DROP TABLE IF EXISTS Maratona_Kits        ; */
/* DROP TABLE IF EXISTS Kit_Items            ; */
/* DROP TABLE IF EXISTS Maratona             ; */
/* DROP TABLE IF EXISTS Kit                  ; */
/* DROP TABLE IF EXISTS Item                 ; */
/* DROP TABLE IF EXISTS Conhecido            ; */
/* DROP TABLE IF EXISTS Parentesco           ; */