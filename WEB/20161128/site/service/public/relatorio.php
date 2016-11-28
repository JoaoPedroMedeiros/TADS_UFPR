<?php
  
  // Recupera as classes de conexão com o banco de dados
  require_once('../private/conn/DBFactory.php');
  require_once('../private/conn/JSONUtil.php');
  
  //Recupera os parâmetros da requisição
  $param = JSONUtil::parameters($_SERVER);
  
  $nm_atleta = null;
  $nr_ident  = null;
  $cd_categ  = null;
  $cd_mod    = null;
  
  if (sizeof($param) > 0) {
    $request = json_decode($param[0], true);
  
    if (array_key_exists('nm_atleta', $request))
      $nm_atleta = $request['nm_atleta'];
    
    if (array_key_exists('nr_ident', $request))
      $nr_ident  = $request['nr_ident'];
    
    if (array_key_exists('cd_categ', $request))
      $cd_categ  = $request['cd_categ'];
    
    if (array_key_exists('cd_mod', $request))
      $cd_mod    = $request['cd_mod'];
  }
  
  $sql = 
    "SELECT                                         \n
       nr_ident,                                    \n
       nm_atleta,                                   \n
       ds_mod + '(' + nr_dist + 'km' + ')',         \n
       ds_categ,                                    \n
       nr_tempin,                                   \n
       nr_tempfi,                                   \n
       0 + 'km/h',                                  \n
       (SELECT                                      \n
          @rowId                                    \n
        FROM                                        \n
          participacao as sub                       \n
        WHERE                                       \n
            sub.cd_mod   = participacao.cd_mod      \n
        AND sub.cd_categ = participacao.cd_categ    \n
        ORDER BY                                    \n
          nr_tempfi - nr_tempin                     \n
       ) nr_pos                                     \n
     FROM                                           \n
       participacao                                 \n
       INNER JOIN atleta ON (                       \n
         atleta.cd_atleta = participacao.cd_atleta  \n
       )                                            \n
       INNER JOIN modalidade ON (                   \n
         modalidade.cd_mod = participacao.cd_mod    \n
       )                                            \n
       INNER JOIN categoria ON (                    \n
         categoria.cd_categ = participacao.cd_categ \n
       )                                            \n
     WHERE                                          \n
         1 = 1                                      \n";
         
   if ($nm_atleta != null)
     $sql = $sql . "AND nm_atleta LIKE '" . $nm_atleta . "%'\n";
   if ($nr_ident  != null)
     $sql = $sql . "AND nr_ident = " . $nr_ident . "\n";
   if ($cd_categ  != null)
     $sql = $sql . "AND categoria.cd_categ = " . $cd_categ . "\n";
   if ($cd_mod    != null)
     $sql = $sql . "AND modalidade.cd_mod = " . $cd_mod . "\n";
     
  //Executa a consulta
  DBFactory::getQuery()->exec($sql);
?>