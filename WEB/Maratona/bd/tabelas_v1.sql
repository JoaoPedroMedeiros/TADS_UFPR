/*============================================================*/
/* Script de criação das tabelas
/* Banco de dados: MySQL
/* Criador: João Pedro Medeiros
/* Versão 1
/*============================================================*/

CREATE TABLE Atleta                (
  cd_atleta INT          NOT NULL PRIMARY KEY,
  nr_rg     BIGINT       NOT NULL            ,
  nr_cpf    BIGINT       NOT NULL            ,
  id_sexo   CHAR         NOT NULL            ,
  id_estran BIT(1)       NOT NULL            ,
  nr_passap BIGINT       NULL                ,
  dt_nasc   DATE         NOT NULL            ,
  ds_email  VARCHAR(100) NOT NULL            ,
  nr_tel    INT          NOT NULL            ,
  nm_login  VARCHAR(50)  NOT NULL            ,
  ds_senha  VARCHAR(50)  NOT NULL
)
CREATE TABLE Maratona              (
  cd_marat  INT          NOT NULL PRIMARY KEY,
  dt_marat  DATE         NOT NULL            ,
  ds_local  VARCHAR(100) NOT NULL
)

CREATE TABLE Modalidade            (
  cd_mod   INT           NOT NULL PRIMARY KEY
  ds_mod   VARCHAR(50)   NOT NULL
  nr_dist  INT           NOT NULL
  cd_marat INT           NOT NULL
)
CREATE TABLE Categoria             (
  cd_categ  INT          NOT NULL PRIMARY KEY,
  ds_categ  VARCHAR(50)  NOT NULL            ,
  id_sexcat CHAR         NOT NULL            ,
  nr_idamin TINYINT      NOT NULL            
)
CREATE TABLE Modalidade_Categorias (
  cd_mod   INT           NOT NULL
  cd_categ INT           NOT NULL
)
CREATE TABLE Participacao          (
  nr_ident  BIGINT       NOT NULL PRIMARY KEY 
  cd_atleta INT          NOT NULL
  cd_mod    INT          NOT NULL
  cd_categ  INT          NOT NULL
  cd_kit    INT          NOT NULL
  id_taman  CHAR(2)      NOT NULL
  nr_tempin DATETIME     NOT NULL
  nr_tempfi DATETIME     NOT NULL
)
CREATE TABLE Kit                   (
  cd_kit    INT          NOT NULL PRIMARY KEY,
  ds_kit    VARCHAR(50)  NOT NULL
)
CREATE TABLE Maratona_Kits         (
  cd_marat  INT          NOT NULL
  cd_kit    INT          NOT NULL 
)
CREATE TABLE Item                  (
  cd_item   INT          NOT NULL PRIMARY KEY,
  ds_item   VARCHAR(50)  NOT NULL
)
CREATE TABLE Kit_Items             (
  cd_kit    INT          NOT NULL
  cd_item   INT          NOT NULL
)
CREATE TABLE Conhecido             (
  cd_atleta INT          NOT NULL
  cd_conhec INT          NOT NULL
  nr_tel    BIGINT       NOT NULL
  nm_conhec VARCHAR(100) NOT NULL
  cd_parent INT          NOT NULL
)
CREATE TABLE Parentesco            (
  cd_parent INT          NOT NULL PRIMARY KEY,
  ds_parent VARCHAR(50)  NOT NULL
)