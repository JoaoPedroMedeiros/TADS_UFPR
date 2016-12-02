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

  function calcularIdade($dtAtual, $dtNasc) {
    $data = $dtNasc;
   
    list($dia, $mes, $ano) = explode('/', $data);
    list($diaH, $mesH, $anoH) = explode('/', $dtAtual);
   
    $nascimento = mktime( 0, 0, 0, $mes, $dia, $ano);
    $hoje = mktime( 0, 0, 0, $mesH, $diaH, $anoH);
   
   
    $idade = floor((((($hoje - $nascimento) / 60) / 60) / 24) / 365.25);
    return $idade;
  }
  
  if (!array_key_exists('parametro', $_POST) || $_POST['parametro'] === null)
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
  
  $cd_atleta = $request['cd_atleta'];
  
  /*=============================================================================*/
  /* Valida se o atleta já esta inscrito.
  /*=============================================================================*/
  $sqlVerificaUsuarioJaInscrito =
    "SELECT                      \n".
    "  nr_ident                  \n".
    "FROM                        \n".
    "  Participacao              \n".
    "WHERE                       \n".
    "  cd_atleta = ".$cd_atleta."\n";

  
  $identAnterior = DBFactory::getQuery()->singleResult($sqlVerificaUsuarioJaInscrito);
  
  if ($identAnterior != null)
    retornar(-30, "Você já está inscrito para a maratona. Verifique os dados da inscrição através do identificador ". $identAnterior);
  
  /*=============================================================================*/
  /* Geração do identificador
  /*=============================================================================*/
  do {
    $identificador = rand(100000, 999999);
  
    $sqlBuscaIdentificador = 
      "SELECT        \n".
      "  nr_ident    \n".
      "FROM          \n".
      "  Participacao\n".
      "WHERE         \n".
      "  nr_ident = ". $identificador;
  
    $existeIdentificador = DBFactory::getQuery()->singleResult($sqlBuscaIdentificador);
  }
  while ($existeIdentificador);
  
  /*=============================================================================*/
  /* Busca data de nascimento do atleta         
  /*=============================================================================*/
  $sqlBuscaDataNasc =
    "SELECT        \n".
    "  dt_nasc     \n".
    "FROM          \n".
    "  Atleta      \n".
    "WHERE         \n".
    "  cd_atleta = ". $cd_atleta ."\n";
  
  $dtNasc = DBFactory::getQuery()->singleResult($sqlBuscaDataNasc);
  
  if ($dtNasc == null)
	  retornar(-110, "Não foi possível recuperar a data de nascimento");
  
  /*=============================================================================*/
  /* Busca a data da maratona                   
  /*=============================================================================*/
  $sqlBuscaDataMarat =
    "SELECT    \n".
    "  dt_marat\n".
    "FROM      \n".
    "  Maratona\n".
    "LIMIT 1   \n";
  
  $dtMaratona = DBFactory::getQuery()->singleResult($sqlBuscaDataMarat);
  
  if ($dtMaratona == null)
	  retornar(-110, "Não foi possível recuperar a data da maratona");
	
  /*=============================================================================*/
  /* Calcula a idade a partir da data de nascimento e da data da maratona
  /*=============================================================================*/    
  $idade = calcularIdade(date('d/m/Y', strtotime($dtMaratona)), date('d/m/Y', strtotime($dtNasc))); 

  if ($idade < 16)
    retornar(-110, "Infelizmente você não tem idade suficiente para correr na maratona. Inscreva-se ano que vem.");
  
  /*=============================================================================*/
  /* Busca o sexo do atleta                                               
  /*=============================================================================*/  
  $sqlBuscaSexo =
    "SELECT        \n".
    "  id_sexo     \n".
    "FROM          \n".
    "  Atleta      \n".
    "WHERE         \n".
    "  cd_atleta = ". $cd_atleta ."\n";
  
  $sexo = DBFactory::getQuery()->singleResult($sqlBuscaSexo);
  
  if ($sexo == null)
	  retornar(-110, "Não foi possível buscar o sexo.");
  
  /*=============================================================================*/
  /* Busca a categoria a partir dos dados encontrados                     
  /*=============================================================================*/
  $modalidade = $request['cd_mod'];
  
  $sqlBuscaCategoria =
    "SELECT                                    \n".
    "  C.cd_categ                              \n".
    "FROM                                      \n".
    "  Categoria C                             \n".
    "  INNER JOIN Modalidade_categorias MC ON (\n".
    "    C.cd_categ = MC.cd_categ              \n".
    "  )                                       \n".
    "WHERE                                     \n".
    "    id_sexcat = '". $sexo ."'             \n".
    "AND nr_idamin <= ". $idade ."             \n".
    "AND cd_mod = ". $modalidade ."            \n".
    "ORDER BY                                  \n".
    "  nr_idamin                               \n".
    "DESC                                      \n".
    "LIMIT 1                                   \n";
  
  $categoria = DBFactory::getQuery()->singleResult($sqlBuscaCategoria);
  
  if ($categoria == null)
	  retornar(-110, "Não foi possível buscar a categoria do competidor.");
  
  /*=============================================================================*/
  /* Busca o valor do kit
  /*=============================================================================*/
  $kit = $request['cd_kit'];
  
  $sqlBuscaValorKit =
    "SELECT              \n".
    "  vl_kit            \n".
    "FROM                \n".
    "  Maratona_Kits     \n".
    "WHERE               \n".
    "  cd_kit = ".$kit." \n".
    "LIMIT 1             \n";
  
  $valorKit = DBFactory::getQuery()->singleResult($sqlBuscaValorKit);
  
  if ($valorKit == null)
	  retornar(-110, "Não foi possível buscar o valor do kit.");
  
  /*=============================================================================*/
  /* Cadastra a participação
  /*=============================================================================*/
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
      $identificador . " ," .
      $cd_atleta .     " ," .
      $modalidade .    " ," .
      $categoria .     " ,".
      $kit .           ",'" .
      ($request['id_taman' ] === null ? "null" : $request['id_taman' ]). "'".
     ");";
   
   $inseriu = DBFactory::getQuery()->result($sqlCadastraParticipacao);
   
   if (!$inseriu)
     retornar(-110, 'Houve um erro ao cadastrar a participação.');
   
  /*=============================================================================*/
  /* Cadastro do pagamento    
  /*=============================================================================*/
  $sqlCadastraPagamento = 
    "INSERT INTO Pagamento (\n".
    "  nr_ident ,           \n".
    "  vl_tot   ,           \n".
    "  cd_cartao,           \n".
    "  cd_seg   ,           \n".
    "  dt_venc  ,           \n".
    "  nm_titul             \n".
    ")                      \n".
    "VALUES (".
      $identificador .",".
      $valorKit .",".
      ($request['cd_cartao'] === null ? "null" : $request['cd_cartao']) . " ," .
      ($request['cd_seg'   ] === null ? "null" : $request['cd_seg'   ]) . " ,'" .
      ($request['dt_venc'  ] === null ? "null" : $request['dt_venc'  ]) . "','" .
      ($request['nm_titul' ] === null ? "null" : $request['nm_titul' ]) . "'" .
    ")";

  $inseriu = DBFactory::getQuery()->result($sqlCadastraPagamento);
   
   if (!$inseriu)
     retornar(-110, 'Houve um erro ao cadastrar o pagamento.', 500);
   
   retornar(0, 'Inscrição efetuada com sucesso!');
?>