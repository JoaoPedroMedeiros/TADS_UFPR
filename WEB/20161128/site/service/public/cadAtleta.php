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
  
  $request = $_POST['parametro'];
  
  /*==========================================================================*/
  /* Validação dos campos
  /*==========================================================================*/
  /* Obrigatórios */
  if (!array_key_exists('nm_atleta', $request) || $request['nm_atleta'] === null)
    retornar(-30, 'Campo nome obrigatório.');
  if (!array_key_exists('nr_rg'    , $request) || $request['nr_rg'    ] === null)
    retornar(-30, 'Campo RG obrigatório.');
  if (!array_key_exists('nr_cpf'   , $request) || $request['nr_cpf'   ] === null)
    retornar(-30, 'Campo CPF obrigatório.');       
  if (!array_key_exists('id_sexo'  , $request) || $request['id_sexo'  ] === null)
    retornar(-30, 'Campo sexo obrigatório.');      
  if (!array_key_exists('id_estran', $request) || $request['id_estran'] === null)
    retornar(-30, 'Campo estrangeiro obrigatório.');  
  if (!array_key_exists('dt_nasc'  , $request) || $request['dt_nasc'  ] === null)
    retornar(-30, 'Campo nascimento obrigatório.');
  if (!array_key_exists('ds_email' , $request) || $request['ds_email' ] === null)
    retornar(-30, 'Campo email obrigatório.');     
  if (!array_key_exists('nr_tel'   , $request) || $request['nr_tel'   ] === null)
    retornar(-30, 'Campo telefone obrigatório.');  
  if (!array_key_exists('nm_login' , $request) || $request['nm_login' ] === null)
    retornar(-30, 'Campo login obrigatório.');     
  if (!array_key_exists('ds_senha' , $request) || $request['ds_senha' ] === null)
    retornar(-30, 'Campo senha obrigatório.');
  
  if ($request['id_sexo'] != 'M' && $request['id_sexo'] != 'F')
    retornar(-30, 'Sexo precisa ser masculino (M) ou feminino (F).');
  
  // Validação de número do passaporte.
  if ($request['id_estran'])
    if (!array_key_exists('nr_passap', $request))
      $request['nr_passap'] = null;  
    else
      if (!array_key_exists('nr_passap' , $request) || $request['nr_passap' ] === null)
        retornar(-30, 'Campo número do passaporte obrigatório para estrangeiro.');
  
  // Validação de conhecido
  if (!array_key_exists('nr_telcon' , $request) || $request['nr_telcon' ] === null)
    retornar(-30, 'Telefone do conhecido obrigatório.');
  if (!array_key_exists('nm_conhec' , $request) || $request['nm_conhec' ] === null)
    retornar(-30, 'Nome do conhecido obrigatório.');
  if (!array_key_exists('cd_parent' , $request) || $request['cd_parent' ] === null)
    retornar(-30, 'Parentesco é obrigatório.');
  
  /*==========================================================================*/
  /* Validaçções de negócio
  /*==========================================================================*/
  /* Valida o CPF */
  $cpf = $request['nr_cpf'];
  $cpfFormatado = maskCPF($cpf);
  
  $validator = new Validator();
  if (!$validator->checkCPF($cpf))
    retornar(10, 'CPF '. $cpfFormatado .' inválido.');
  
  /* Verifica se o CPF já está cadastrado na base de dados */
  $sqlBuscaCPF = 
    "SELECT               \n".
    "  nr_cpf             \n".
    "FROM                 \n".
    "  Atleta             \n".
    "WHERE                \n".
    "  nr_cpf = ". $cpf ."\n";
  
  $existeCPF = DBFactory::getQuery()->singleResult($sqlBuscaCPF);
  
  if ($existeCPF)
    retornar(20, 'CPF '. $cpfFormatado .' já cadastrado.');
  
  $login = $request['nm_login'];
  
  /* Verifica se o login já está cadastrado na base de dados */
  $sqlBuscaLogin = 
    "SELECT                   \n".
    "  nm_login               \n".
    "FROM                     \n".
    "  Atleta                 \n".
    "WHERE                    \n".
    "  nm_login = '". $login ."'\n";
  
  $existeLogin = DBFactory::getQuery()->singleResult($sqlBuscaLogin);
  
  
  if ($existeLogin)
    retornar(20, 'Login '. $login .' já cadastrado.');
  
  /*==========================================================================*/
  /* Cadastro do atleta   
  /*==========================================================================*/
  
  
  $sqlInsereAtleta = 
    "INSERT INTO atleta (
       nm_atleta,        
       nr_rg    ,        
       nr_cpf   ,        
       id_sexo  ,        
       id_estran,        
       nr_passap,        
       dt_nasc  ,        
       ds_email ,         
       nr_tel   ,        
       nm_login ,        
       ds_senha          
     )                   
     VALUES (                                                                  " .
      "'". ($request['nm_atleta'] === null ? "null" : $request['nm_atleta']) . "'," .
           ($request['nr_rg'    ] === null ? "null" : $request['nr_rg'    ]) . " ," .
           ($request['nr_cpf'   ] === null ? "null" : $request['nr_cpf'   ]) . " ," .
      "'". ($request['id_sexo'  ] === null ? "null" : $request['id_sexo'  ]) . "'," .
           ($request['id_estran'] === null ? "null" : $request['id_estran']) . " ," .
           ($request['nr_passap'] === null ? "null" : $request['nr_passap']) . " ," .
      "STR_TO_DATE('" . (($request['dt_nasc'] === null ? "null" : $request['dt_nasc'])) . "', '%d-%m-%Y')," .
      "'". ($request['ds_email' ] === null ? "null" : $request['ds_email' ]) . "'," .
           ($request['nr_tel'   ] === null ? "null" : $request['nr_tel'   ]) . " ," .
      "'". ($request['nm_login' ] === null ? "null" : $request['nm_login' ]) . "'," .
      "'". ($request['ds_senha' ] === null ? "null" : $request['ds_senha' ]) . "' 
     );";
  
  $inseriu = DBFactory::getQuery()->result($sqlInsereAtleta);
  
  //Verifica se inseriu o atleta.
  if (!$inseriu)
    trigger_error('Houve um erro ao inserir o atleta.', 500);
  
  /*==========================================================================*/
  /* Buscar o código do atleta inserido
  /*==========================================================================*/
  $sqlBuscaCodigo =
    "SELECT                        \n".
    "  COALESCE(MAX(cd_atleta), 0) \n".
    "FROM                          \n".
    "  Atleta                      \n";
  
  $codAtleta = DBFactory::getQuery()->singleResult($sqlBuscaCodigo);
  
  if ($codAtleta == 0)
    trigger_error('Houve um erro ao buscar o código do atleta.', 500);
  
  /*==========================================================================*/
  /* Inserir Conhecido                    
  /*==========================================================================*/
  
  $sqlInsereConhecido =
    "INSERT INTO Conhecido (          \n".
    "  cd_atleta,                     \n".
    "  cd_conhec,                     \n".
    "  nr_tel   ,                     \n".
    "  nm_conhec,                     \n".
    "  cd_parent                      \n".
    ")                                \n".
    "VALUES (                         \n".
    "  ".$codAtleta.",                \n".
    "  (SELECT                        \n".
    "     COALESCE(MAX(cd_conhec), 1) \n".
    "   FROM                          \n".
    "     Conhecido C                 \n".
    "   WHERE                         \n".  
    "     C.cd_atleta = ".$codAtleta. "),\n".
         ($request['nr_telcon'] === null ? "null" : $request['nr_telcon']) . " , \n" .
    "'". ($request['nm_conhec'] === null ? "null" : $request['nm_conhec']) . "', \n" .
         ($request['cd_parent'] === null ? "null" : $request['cd_parent']) . "   \n" .
    ")                           ";
  
  $inseriu = DBFactory::getQuery()->result($sqlInsereConhecido);
  
  //Verifica se inseriu o conhecido.
  if (!$inseriu)
    trigger_error('Houve um erro ao inserir o conhecido.', 500);
  
  retornar(0, "Cadastro efetuado com sucesso!");
?>