<?php

  // Recupera as classes de conexão com o banco de dados
  require_once('../private/conn/DBFactory.php');
  
  /**
   * Classe de retorno da execução.
   */
  class Retorno {
    public $codigo;
    public $mensagem;
  }
  
  /**
   * Retorna o JSON para o usuário.
   *
   * @param $codigo
   *   igual 0   = Sucesso na operação.
   *   menor 0   = Erro na estrutura de solicitação ou parâmetro faltando.
   *   maior 0   = Caiu em alguma consistência de negócio.
   *
   * @param $mensagem 
   *   Mensagem da execução.
   */
  function retornar($codigo, $mensagem) {
    $retorno = new Retorno();
    $retorno->codigo = $codigo;
    $retorno->mensagem = $mensagem;
    
    echo json_encode($retorno);
    exit(0);
  }
  
  if (!array_key_exists('nm_login', $_POST))
    retornar(-20, 'Nome do login não foi fornecido.');
  if (!array_key_exists('ds_senha', $_POST))
    retornar(-20, 'Senha não foi fornecida.');
  
  $nm_login = $_POST['nm_login'];
  $ds_senha = $_POST['ds_senha'];
  
  $sqlValidaLogin = 
    "SELECT                          \n".
    "  cd_atleta,                    \n".
    "  nm_atleta                     \n".
    "FROM                            \n".
    "  atleta                        \n".
    "where                           \n".
    "    nm_login = '". $nm_login ."'\n".
    "and ds_senha = '". $ds_senha ."'\n";

  $result = DBFactory::getQuery()->resultAsArray($sqlValidaLogin);
  
  
  
  if (($result == null) || sizeof($result) == 0 || !isset($result[0]['cd_atleta']) || !isset($result[0]['nm_atleta'])) {
    unset ($_SESSION['codigo']);
    unset ($_SESSION['nome']);
    header('location:../../layout/login.php?response="erro"');
    exit(0);
  }
  
  session_start();
  $codigo = $result[0]['cd_atleta'];
  $nome = $result[0]['nm_atleta'];
  $_SESSION['codigo'] = $codigo;
  $_SESSION['nome'] = $nome;
  header('location:../../layout/index.php');
?>