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

/**
 * Recebe um form, faz a validação dos campos e retorna o componente que está inválido.
 * Se retornar nulo, significa que a validação está OK.
 */
function atualizar(form) {  
  
  adicionaReplaceAll();
  
  if (vazio(form.fNInscricao.value)) {
	  mensagem("Digite o número de inscrição.");
    form.fNInscricao.focus();
    return false;
  }
  if (vazio(form.ftempoini.value)) {
	  mensagem("Digite o tempo inicial.");
    form.ftempoini.focus();
    return false;
  }
  if (vazio(form.ftempofim.value)) {
	  mensagem("Digite o tempo final.");
    form.ftempofim.focus();
    return false;
  }
  
  var _NInscricao = form.fNInscricao.value;
  var _tempoini   = form.ftempoini  .value;
  var _tempofim   = form.ftempofim  .value;
  
  json = {"parametro": {
     "nr_ident" : _NInscricao,
     "nr_tempin": _tempoini  ,
     "nr_tempfi": _tempofim  
  }};
  
  $.post('../service/public/atualizaTempo.php', json, 
  
     function(resultado) {
       var retorno = JSON.parse(resultado);
       if (retorno.codigo != 0) {
         var msg = retorno.mensagem;
         console.log(msg);
       }
       else {
         window.location.href = "index.php";
         mensagem("Atualizado com sucesso!");
       }
     })
     .fail(
       function(resultado) {
         console.log(resultado);
         mensagem("Houve um erro ao efetuar a operação. Tente novamente mais tarde.");
       }
     );
  
  return false;
}