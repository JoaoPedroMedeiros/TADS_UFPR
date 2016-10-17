<?php
  
  // Recupera as classes de conexão com o banco de dados
  require_once('../private/conn/DBFactory.php');
  require_once('../private/conn/JSONFormatter.php');
  require_once('../private/conn/JSONUtil.php');
  
  class JSONFormatterCadAtleta implements JSONFormatter {
    
    public function format($conn, $result) {
      print_r($result);
    }
  };
  
  //Recupera os parâmetros da requisição
  $param = JSONUtil::parameters($_SERVER);
  
  if (sizeof($param) == 0)
    trigger_error('Parâmetro para insert inexistente.', 256);
  
  $request = null;
  
  if (sizeof($param) > 0) {
    $request = json_decode($param[0], true);
    
    if (!$request)
      trigger_error('Parâmetro para insert inválido.', 256);  
  }
  
  /*==========================================================================*/
  /* Validação dos campos
  /*==========================================================================*/
  /* Obrigatórios */
  if (!array_key_exists('nm_atleta', $request) || $request['nm_atleta'] === null)
    trigger_error('Campo nome obrigatório.', 256);         
  if (!array_key_exists('nr_rg'    , $request) || $request['nr_rg'    ] === null)
    trigger_error('Campo RG obrigatório.', 256);           
  if (!array_key_exists('nr_cpf'   , $request) || $request['nr_cpf'   ] === null)
    trigger_error('Campo CPF obrigatório.', 256);          
  if (!array_key_exists('id_sexo'  , $request) || $request['id_sexo'  ] === null)
    trigger_error('Campo sexo obrigatório.', 256);         
  if (!array_key_exists('id_estran', $request) || $request['id_estran'] === null)
    trigger_error('Campo estrangeiro obrigatório.', 256);  
  if (!array_key_exists('dt_nasc'  , $request) || $request['dt_nasc'  ] === null)
    trigger_error('Campo nascimento obrigatório.', 256);   
  if (!array_key_exists('ds_email' , $request) || $request['ds_email' ] === null)
    trigger_error('Campo email obrigatório.', 256);        
  if (!array_key_exists('nr_tel'   , $request) || $request['nr_tel'   ] === null)
    trigger_error('Campo telefone obrigatório.', 256);     
  if (!array_key_exists('nm_login' , $request) || $request['nm_login' ] === null)
    trigger_error('Campo login obrigatório.', 256);        
  if (!array_key_exists('ds_senha' , $request) || $request['ds_senha' ] === null)
    trigger_error('Campo senha obrigatório.', 256);
  
  if ($request['id_sexo'] != 'M' && $request['id_sexo'] != 'F')
    trigger_error('Sexo precisa ser masculino (M) ou feminino (F).', 256);
  
  // Validação de número do passaporte.
  if ($request['id_estran'] == null)
    if (!array_key_exists('nr_passap', $request))
      $request['nr_passap'] = null;  
    else
      if (!array_key_exists('nr_passap' , $request) || $request['nr_passap' ] === null)
        trigger_error('Campo número do passaporte obrigatório para estrangeiro.', 256);
  
  
  echo $request['id_estran'] == null;
  
  $sql = 
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
  
  echo $sql;
  
  //Executa a consulta
  DBFactory::getQuery()->execFormat($sql, new JSONFormatterCadAtleta());
?>