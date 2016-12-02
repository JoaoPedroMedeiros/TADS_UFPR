<?php

  // Recupera as classes de conexão com o banco de dados
  require_once('../private/conn/DBFactory.php');
  require_once('../private/conn/JSONUtil.php');
  
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

  if (!array_key_exists('parametro', $_POST) || $_POST['parametro'] === null)
    retornar(-10, 'Parâmetro para inscrição não fornecido.');
  
  $request = $_POST['parametro'];
  
  if (!array_key_exists('nr_ident', $request) || $request['nr_ident'] === null)
    retornar(-20, 'Identificador não informado.');
  if (!array_key_exists('nr_tempin'   , $request) || $request['nr_tempin'   ] === null)
    retornar(-20, 'Tempo inicial não informado.');
  if (!array_key_exists('nr_tempfi'   , $request) || $request['nr_tempfi'   ] === null)
    retornar(-20, 'Tempo final não informado.');

  $sqlVerificaId = 
    "SELECT                               \n".
    "  1                                  \n".
    "FROM                                 \n".
    "  Participacao                       \n".
    "WHERE                                \n".
    "  nr_ident = ".$request['nr_ident']."\n";
  
  $existeId = DBFactory::getQuery()->singleResult($sqlVerificaId);
  
  if (!$existeId)
    retornar(-30, 'ID '. $request['nr_ident'] . " não encontrado.");
  
  $sqlBuscaDtMaratona =
    "SELECT     \n".
    "  dt_marat \n".
    "FROM       \n".
    "  Maratona \n".
    "LIMIT 1    \n";
	
  $dtMarat = DBFactory::getQuery()->singleResult($sqlBuscaDtMaratona);
   
  $tempoIni = $dtMarat . ' '. $request['nr_tempin'];
  $tempoFin = $dtMarat . ' '. $request['nr_tempfi'];
   
  if ($dtMarat == null)
    retornar(-30, 'Houve um erro ao buscar a data da maratona.');

  $sqlAtualizaTempo =
    "UPDATE                               \n".
    "  Participacao                       \n".
    "SET                                  \n".
    "  nr_tempin = '". $tempoIni      ."',\n".
    "  nr_tempfi = '". $tempoFin      ."' \n".
    "WHERE                                \n".
    "  nr_ident = ".$request['nr_ident']."\n";

   $inseriu = DBFactory::getQuery()->result($sqlAtualizaTempo);
   
   if (!$inseriu)
     retornar(-40, 'Houve um erro ao atualizar o tempo.');
 
   retornar(0, 'Tempo do ID '. $request['nr_ident'] . " atualizado com sucesso!");
?>