<?php
  
  // Recupera as classes de conexão com o banco de dados
  require_once('../private/conn/DBFactory.php');
  
  //Executa a consulta
  DBFactory::getQuery()->exec("SELECT * FROM parentesco;");
?>