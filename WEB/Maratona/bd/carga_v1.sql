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
INSERT INTO maratona(cd_marat, dt_marat, ds_local) VALUES (1, STR_TO_DATE('15-11-2015','%d-%m-%Y'), 'Praça Osório, Curitiba');

/*=========================================================*/
/* maratona_kits                                           */
/*=========================================================*/
INSERT INTO maratona_kits(cd_marat, cd_kit) VALUES (1, 1);
INSERT INTO maratona_kits(cd_marat, cd_kit) VALUES (1, 2);
INSERT INTO maratona_kits(cd_marat, cd_kit) VALUES (1, 3);

/*=========================================================*/
/* modalidade                                              */
/*=========================================================*/
INSERT INTO modalidade(cd_mod, ds_mod, nr_dist, cd_marat) VALUES (1, "Iniciante"    , 10, 1);
INSERT INTO modalidade(cd_mod, ds_mod, nr_dist, cd_marat) VALUES (2, "Intermediário", 21, 1);
INSERT INTO modalidade(cd_mod, ds_mod, nr_dist, cd_marat) VALUES (3, "Avançado"     , 42, 1);

