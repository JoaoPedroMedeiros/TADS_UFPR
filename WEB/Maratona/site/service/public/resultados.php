<?php

  // Recupera as classes de conexão com o banco de dados
  require_once('../private/conn/DBFactory.php');
  require_once('../private/conn/JSONUtil.php');
  require_once('../private/entity/Resultado.php');
  
  $param = JSONUtil::parameters($_SERVER);
  
  if (isset($_POST['parametro']))
    $request = $_POST['parametro'];
  
  $nome          = isset($request['nm_atleta']) ? $request['nm_atleta'] : null;
  $identificador = isset($request['nr_ident' ]) ? $request['nr_ident' ] : null;
  $categoria     = isset($request['cd_categ' ]) ? $request['cd_categ' ] : null;
  $modalidade    = isset($request['cd_mod'   ]) ? $request['cd_mod'   ] : null;
  
  $calculoResultado = new Resultado();
  $resultado = $calculoResultado->calculaResultado($nome, $identificador, $categoria, $modalidade);
  echo json_encode($resultado);
?>




