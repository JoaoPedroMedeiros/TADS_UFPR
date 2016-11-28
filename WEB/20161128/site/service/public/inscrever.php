<?php

  // Recupera as classes de conexão com o banco de dados
  require_once('../private/conn/DBFactory.php');
  require_once('../private/conn/JSONFormatter.php');
  require_once('../private/conn/JSONUtil.php');
  require_once('../private/util/Validator.php');
  require_once('../private/util/Mask.php');
  
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
  
  if (!array_key_exists('parametro', _POST) || _POST['parametro'] === null)
    retornar(-10, 'Parâmetro para inscrição não fornecido.');
  
  $request = $_POST['parametro'];
  
  /*==========================================================================*/
  /* Validação dos campos
  /*==========================================================================*/
  /* Obrigatórios */
  if (!array_key_exists('cd_atleta', $request) || $request['cd_atleta'] === null)
    retornar(-20, 'Codigo atleta obrigatório.');
  if (!array_key_exists('cd_mod'   , $request) || $request['cd_mod'   ] === null)
    retornar(-20, 'Modalidade obrigatório.');
  if (!array_key_exists('cd_kit'   , $request) || $request['cd_kit'   ] === null)
    retornar(-20, 'Kit obrigatório.');
  if (!array_key_exists('id_taman' , $request) || $request['id_taman' ] === null)
    retornar(-20, 'Tamanho obrigatório.');
  if (!array_key_exists('cd_cartao', $request) || $request['cd_cartao'] === null)
    retornar(-20, 'Codigo do cartão obrigatório.');
  if (!array_key_exists('cd_seg'   , $request) || $request['cd_seg'   ] === null)
    retornar(-20, 'Código de segurança obrigatório.');
  if (!array_key_exists('dt_venc'  , $request) || $request['dt_venc'  ] === null)
    retornar(-20, 'Data de vencimento obrigatória.');
  if (!array_key_exists('nm_titul' , $request) || $request['nm_titul' ] === null)
    retornar(-20, 'Nome do titular obrigatório.');
  
  /*=============================================================================*/
  /* Geração do identificador
  /*=============================================================================*/
  do {
    $identificador = rand(100000, 999999);
  
    $sqlBuscaIdentificador = 
      "SELECT       \n".
      "  nr_ident   \n".
      "FROM         \n".
      "  MA11       \n".
      "WHERE        \n".
      "  nr_ident = ". $identificador;
  
    $existeIdentificador = DBFactory::getQuery()->singleResult($sqlBuscaIdentificador);
  }
  while ($existeIdentificador);
  
  /*=============================================================================*/
  /* Cadastro da participação 
  /*=============================================================================*/
  /* Pega a categoria */
  
  
  
  /* Cadastra a participação */
  $sqlCadastraParticipacao = 
    "INSERT INTO Participacao (
       nr_ident ,
       cd_atleta,
       cd_mod   ,
       cd_categ ,
       cd_kit   ,
       id_taman
     )                   
     VALUES (" .
      $identificador . "'," .
      ($request['cd_atleta'] === null ? "null" : $request['cd_atleta']) . " ," .
      ($request['cd_categ' ] === null ? "null" : $request['cd_categ' ]) . " ," .
      ($request['cd_kit'   ] === null ? "null" : $request['cd_kit'   ]) . "'," .
      ($request['id_taman' ] === null ? "null" : $request['id_taman' ]) . " ," .
     ");";
     
   $inseriu = DBFactory::getQuery()->result($sqlCadastraParticipacao);
   
   if (!$inseriu)
     trigger_error('Houve um erro ao cadastrar a participação.', 500);
   
  /*=============================================================================*/
  /* Cadastro do pagamento    
  /*=============================================================================*/
  /* Busca o valor do kit */
  
?>