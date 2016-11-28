<?php
  
  // Recupera as classes de conexão com o banco de dados
  require_once('../private/conn/DBFactory.php');
  require_once('../private/conn/JSONUtil.php');
  
  //Recupera o parâmetro da URL.
  $param = JSONUtil::parameters($_SERVER);
  $maratona = sizeof($param) > 0 ? $param[0] : 1;
  
  //Executa a consulta
  DBFactory::getQuery()->exec("SELECT * FROM modalidade WHERE cd_marat = " . $maratona . ";");
?>