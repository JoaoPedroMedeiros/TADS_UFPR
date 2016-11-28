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
 * Informa se um campo está vazio.
 */
function vazio(texto) {
  return texto.length == 0;
}
/*====================================================================*/
/* Máscaras                                                           */
/*====================================================================*/
/**
 * Remove a máscara de Data
 */
function removeMascaraData(texto) {
  return texto.replaceAll("/", "-");
}

/*====================================================================*/
/* Validação de todos os campos                                       */
/*====================================================================*/
/**
 * Recebe um form, faz a validação dos campos e retorna o componente que está inválido.
 * Se retornar nulo, significa que a validação está OK.
 */
function inscrever(form) {  
  if (vazio(form.rbgKit       .value)) {
    mensagem("Selecione um kit");
    return false;
  }
  if (vazio(form.cbxTamanho   .value)) {
    mensagem("Selecione o seu tamanho de camiseta.");
    form.cbxTamanho.focus();
    return false;
  }
  if (vazio(form.rbgModalidade.value)) {
    mensagem("Selecione uma modalidade.");
    return false;
  }
  if (vazio(form.rbgCartao    .value)) {
    mensagem("Selecione um cartão.");
    return false;
  }
  if (vazio(form.fNrCartao    .value)) {
    mensagem("Digite o número do cartão.");
    form.fNrCartao.focus();
    return false;
  }
  if (vazio(form.fCodSeguranca.value)) {
    mensagem("Digite o código de segurança.");
    form.fCodSeguranca.focus();
    return false;
  }
  if (vazio(form.fDataVal     .value)) {
    mensagem("Digite a data de validade do cartão.");
    form.fDataVal.focus();
    return false;
  }
  if (vazio(form.fNome        .value)) {
    mensagem("Digite o nome do titular do cartão.");
    form.fNome.focus();
    return false;
  }
  
  if (campoErro != null) {
    mensagem("Campo " + campoErro.placeholder + " precisa estar preenchido corretamente.");
    campoErro.focus();
    return false;
  }
  
  var _rbgKit        = form.rbgKit       .value;
  var _cbxTamanho    = form.cbxTamanho   .value;
  var _rbgModalidade = form.rbgModalidade.value;
  var _rbgCartao     = form.rbgCartao    .value;
  var _fNrCartao     = form.fNrCartao    .value;
  var _fCodSeguranca = form.fCodSeguranca.value;
  var _fDataVal      = form.fDataVal     .value;
  var _fNome         = form.fNome        .value;
  
  $codAtleta = request.getSession().getAttribute("codAtleta");
  
  json = {"parametro": {
     "cd_atleta": $codAtleta,
     "cd_mod"   : _rbgModalidade,
     "cd_kit"   : _rbgKit,
     "id_taman" : _cbxTamanho,
     "cd_cartao": _fNrCartao,
     "cd_seg"   : _fCodSeguranca,
     "dt_venc"  : _fDataVal,
     "nm_titul" : _fNome
  }};
  
  $.post('../service/public/inscrever.php', json, 
  
     function(resultado) {
       var retorno = JSON.parse(resultado);
       if (retorno.codigo != 0)
         mensagem(retorno.mensagem);
       else {
         window.location.href = "index.php";
         mensagem("Inscrição efetuada com sucesso!");
       }
     })
     .fail(
       function(resultado) {
         mensagem("Houve um erro ao efetuar a operação. Tente novamente mais tarde.");
       }
     );
  
  return true;
}