function adicionaReplaceAll() {
  String.prototype.replaceAll = function(search, replacement) {
    var target = this;
    return target.split(search).join(replacement);
  };  
}

function mensagem($msg) {
  alert($msg);
}


/*====================================================================*/
/* Validações                                                         */
/*====================================================================*/
/**
 * Verifica se o email é valido.
 */
function validaEmail(componente) {
  return true;
}

/**
 * Informa se um campo está vazio.
 */
function vazio(texto) {
  return texto.length == 0;
}
/*====================================================================*/
/* Máscaras                                                           */
/*====================================================================*/
/**
 * Remove a máscara de Telefone
 */
function removeMascaraTelefone(texto) {
  return texto.replaceAll("-", "").replaceAll("\(", "").replaceAll("\)", "").replaceAll(" ", "");
}

/**
 * Remove a máscara de Data
 */
function removeMascaraData(texto) {
  return texto.replaceAll("/", "-");
}

/**
 * Remove a máscara de CPF
 */
function removeMascaraCPF(texto) {
  return texto.replaceAll("\.", "").replaceAll("-", "");
}

/*====================================================================*/
/* Validação de todos os campos                                       */
/*====================================================================*/
/**
 * Recebe um form, faz a validação dos campos e retorna o componente que está inválido.
 * Se retornar nulo, significa que a validação está OK.
 */
function validaCampos(form) {
  
  //CPF
  if (vazio(form.fCPF.value)) 
    return form.fCPF;
  
  //Nome completo
  if (vazio(form.fNomeCompl.value)) 
    return form.fNomeCompl;
  
  //RG
  if (vazio(form.fRG.value)) 
    return form.fRG;
  
  //Passaporte
  if (form.ckbxEstrangeiro.checked)
    if (vazio(form.fPassaporte.value)) 
      return form.fPassaporte;
    
  //Data de nascimento
  if (vazio(form.fDataNasc.value)) 
    return form.fDataNasc;
  
  //Sexo
  if (vazio(form.cbxSexo.value)) 
    return form.cbxSexo;
  
  //Telefone
  if (vazio(form.fTel.value)) 
    return form.fTel;
  
  //Telefone de conhecido
  if (vazio(form.fTelConhec.value)) 
    return form.fTelConhec;
  
  //Nome do conhecido
  if (vazio(form.fNomeConhec.value)) 
    return form.fNomeConhec;
  if (vazio(form.cbxParentesco.value)) 
    return form.cbxParentesco;
  
  //Email
  if (vazio(form.fEmail.value)) 
    return form.fEmail;
  if (!validaEmail(form.fEmail)) 
    return form.fEmail;
  
  //Valida senha
  if (vazio(form.fSenha.value)) 
    return form.fSenha;
  if (vazio(form.fConfirmSenha.value)) 
    return form.fConfirmSenha;
}

function cadastrarAtleta(form) {  
  adicionaReplaceAll();
  
  campoErro = validaCampos(form);
  
  if (campoErro != null) {
    mensagem("Campo " + campoErro.placeholder + " precisa estar preenchido corretamente.");
    campoErro.focus();
    return false;
  }
  
  //Valida se as duas senhas estão iguais
  if (form.fSenha.value != form.fConfirmSenha.value) {
    mensagem("As senhas digitadas não correspondem.");
    form.fSenha.focus();
    return false; 
  }
    
  var _CPF             = removeMascaraCPF(form.fCPF.value);
  var _NomeCompl       = form.fNomeCompl.value;
  var _RG              = form.fRG.value;
  var _ckbxEstrangeiro = form.ckbxEstrangeiro.checked;
  var _Passaporte      = form.fPassaporte.value;
  var _DataNasc        = removeMascaraData(form.fDataNasc.value);
  var _cbxSexo         = form.cbxSexo.value;
  var _Tel             = removeMascaraTelefone(form.fTel.value);
  var _TelConhec       = removeMascaraTelefone(form.fTelConhec.value);
  var _NomeConhec      = form.fNomeConhec.value;
  var _cbxParentesco   = form.cbxParentesco.value;
  var _Email           = form.fEmail.value;
  var _Senha           = form.fSenha.value;
 
  json = {"parametro": {
    "nm_atleta": _NomeCompl,
    "nr_rg"    : _RG,
    "nr_cpf"   : _CPF,
    "id_sexo"  : _cbxSexo,
    "id_estran": _ckbxEstrangeiro,
    "dt_nasc"  : _DataNasc,
    "ds_email" : _Email,
    "nr_tel"   : _Tel,
    "nm_login" : _Email,
    "ds_senha" : _Senha,
    "nr_telcon": _TelConhec,
    "nm_conhec": _NomeConhec,
    "cd_parent": _cbxParentesco
  }};
  
  if (!vazio(_Passaporte))
    json["parametro"]["nr_passap"] = _Passaporte;
  
  $.post('../service/public/cadAtleta.php', json, 
  
     function(resultado) {
       var retorno = JSON.parse(resultado);
       if (retorno.codigo != 0)
         mensagem(retorno.mensagem);
       else {
         window.location.href = "login.php";
         mensagem("Cadastro efetuado com sucesso!");
       }
     })
     .fail(
       function(resultado) {
         mensagem("Houve um erro ao efetuar a operação. Tente novamente mais tarde.");
       }
  );
  
  return false;
}