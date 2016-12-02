/*=========================================================*/
/* parentesco                                              */
/*=========================================================*/
INSERT INTO parentesco (cd_parent,   ds_parent) VALUES (1, 'Pai');
INSERT INTO parentesco (cd_parent,   ds_parent) VALUES (2, 'Mãe');
INSERT INTO parentesco (cd_parent,   ds_parent) VALUES (3, 'Tio(a)');
INSERT INTO parentesco (cd_parent,   ds_parent) VALUES (4, 'Avô(ó)');
INSERT INTO parentesco (cd_parent,   ds_parent) VALUES (5, 'Namorado(a)');
INSERT INTO parentesco (cd_parent,   ds_parent) VALUES (6, 'Outro');

/*=========================================================*/
/* Item                                                    */
/*=========================================================*/
INSERT INTO item (cd_item,   ds_item) VALUES (1, "Camiseta");
INSERT INTO item (cd_item,   ds_item) VALUES (2, "Sacola de treino");
INSERT INTO item (cd_item,   ds_item) VALUES (3, "Medalha de participação");
INSERT INTO item (cd_item,   ds_item) VALUES (4, "Jaqueta esportiva");
INSERT INTO item (cd_item,   ds_item) VALUES (5, "Cinto de hidratação");
INSERT INTO item (cd_item,   ds_item) VALUES (6, "Boné");

/*=========================================================*/
/* kit                                                     */
/*=========================================================*/
INSERT INTO kit (cd_kit, ds_kit) VALUES(1, "Kit VIP");
INSERT INTO kit (cd_kit, ds_kit) VALUES(2, "Kit Plus");
INSERT INTO kit (cd_kit, ds_kit) VALUES(3, "Kit Básico");

/*=========================================================*/
/* kit_itens                                               */
/*=========================================================*/
INSERT INTO kit_items(cd_kit, cd_item) VALUES (1, 1);
INSERT INTO kit_items(cd_kit, cd_item) VALUES (1, 2);
INSERT INTO kit_items(cd_kit, cd_item) VALUES (1, 3);
INSERT INTO kit_items(cd_kit, cd_item) VALUES (1, 4);
INSERT INTO kit_items(cd_kit, cd_item) VALUES (2, 1);
INSERT INTO kit_items(cd_kit, cd_item) VALUES (2, 2);
INSERT INTO kit_items(cd_kit, cd_item) VALUES (2, 3);
INSERT INTO kit_items(cd_kit, cd_item) VALUES (2, 5);
INSERT INTO kit_items(cd_kit, cd_item) VALUES (2, 6);
INSERT INTO kit_items(cd_kit, cd_item) VALUES (3, 1); 
INSERT INTO kit_items(cd_kit, cd_item) VALUES (3, 2);
INSERT INTO kit_items(cd_kit, cd_item) VALUES (3, 3);
INSERT INTO kit_items(cd_kit, cd_item) VALUES (3, 6);

/*=========================================================*/
/* maratona                                                */
/*=========================================================*/
INSERT INTO maratona(cd_marat, dt_marat, ds_local) VALUES (1, STR_TO_DATE('14-01-2017','%d-%m-%Y'), 'Praça Catedral - Santo Ângelo');

/*=========================================================*/
/* maratona_kits                                           */
/*=========================================================*/
INSERT INTO maratona_kits(cd_marat, cd_kit, vl_kit) VALUES (1, 1, 180.00);
INSERT INTO maratona_kits(cd_marat, cd_kit, vl_kit) VALUES (1, 2, 130.00);
INSERT INTO maratona_kits(cd_marat, cd_kit, vl_kit) VALUES (1, 3, 100.00);

/*=========================================================*/
/* modalidade                                              */
/*=========================================================*/
INSERT INTO modalidade(cd_mod, ds_mod, nr_dist, cd_marat) VALUES (1, "Iniciante"    , 10, 1);
INSERT INTO modalidade(cd_mod, ds_mod, nr_dist, cd_marat) VALUES (2, "Intermediário", 21, 1);
INSERT INTO modalidade(cd_mod, ds_mod, nr_dist, cd_marat) VALUES (3, "Avançado"     , 42, 1);

/*=========================================================*/
/* modalidade                                              */
/*=========================================================*/
INSERT INTO Categoria (cd_categ, ds_categ, id_sexcat, nr_idamin) VALUES (1, "Geral Masculino 10km", "M", 16);
INSERT INTO Categoria (cd_categ, ds_categ, id_sexcat, nr_idamin) VALUES (2, "Geral Masculino 21km", "M", 16);
INSERT INTO Categoria (cd_categ, ds_categ, id_sexcat, nr_idamin) VALUES (3, "Geral Masculino 42km", "M", 16);
INSERT INTO Categoria (cd_categ, ds_categ, id_sexcat, nr_idamin) VALUES (4, "Geral Feminino 10km", "F", 16);
INSERT INTO Categoria (cd_categ, ds_categ, id_sexcat, nr_idamin) VALUES (5, "Geral Feminino 21km", "F", 16);
INSERT INTO Categoria (cd_categ, ds_categ, id_sexcat, nr_idamin) VALUES (6, "Geral Feminino 42km", "F", 16);
INSERT INTO Categoria (cd_categ, ds_categ, id_sexcat, nr_idamin) VALUES (7, "Masculino 10km acima de 60 anos", "M", 60);
INSERT INTO Categoria (cd_categ, ds_categ, id_sexcat, nr_idamin) VALUES (8, "Masculino 21km acima de 60 anos", "M", 60);
INSERT INTO Categoria (cd_categ, ds_categ, id_sexcat, nr_idamin) VALUES (9, "Masculino 42km acima de 60 anos", "M", 60);
INSERT INTO Categoria (cd_categ, ds_categ, id_sexcat, nr_idamin) VALUES (10, "Feminino 10km acima de 60 anos", "F", 60);
INSERT INTO Categoria (cd_categ, ds_categ, id_sexcat, nr_idamin) VALUES (11, "Feminino 21km acima de 60 anos", "F", 60);
INSERT INTO Categoria (cd_categ, ds_categ, id_sexcat, nr_idamin) VALUES (12, "Feminino 42km acima de 60 anos", "F", 60);

/*=========================================================*/
/* Modalidade_categorias                                   */
/*=========================================================*/
INSERT INTO Modalidade_Categorias (cd_mod, cd_categ) VALUES (1, 1);
INSERT INTO Modalidade_Categorias (cd_mod, cd_categ) VALUES (1, 4);
INSERT INTO Modalidade_Categorias (cd_mod, cd_categ) VALUES (1, 7);
INSERT INTO Modalidade_Categorias (cd_mod, cd_categ) VALUES (1, 10);
INSERT INTO Modalidade_Categorias (cd_mod, cd_categ) VALUES (2, 2);
INSERT INTO Modalidade_Categorias (cd_mod, cd_categ) VALUES (2, 5);
INSERT INTO Modalidade_Categorias (cd_mod, cd_categ) VALUES (2, 8);
INSERT INTO Modalidade_Categorias (cd_mod, cd_categ) VALUES (2, 11);
INSERT INTO Modalidade_Categorias (cd_mod, cd_categ) VALUES (3, 3);
INSERT INTO Modalidade_Categorias (cd_mod, cd_categ) VALUES (3, 6);
INSERT INTO Modalidade_Categorias (cd_mod, cd_categ) VALUES (3, 9);
INSERT INTO Modalidade_Categorias (cd_mod, cd_categ) VALUES (3, 12);

/*=========================================================*/
/* Administrador                                           */
/*=========================================================*/
INSERT INTO atleta (nm_atleta, nr_rg, nr_cpf, id_sexo, id_estran, dt_nasc, ds_email, nr_tel, nm_login, ds_senha) 
VALUES ('admin', 9999999, 9999999, 'M', false, '1990-01-01', 'admin', 9999999, 'admin', 'admin');  