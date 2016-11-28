function MascaraCNPJ(cnpj) {
    if (mascaraInteiro(cnpj) == false) {
        event.returnValue = false;
    }
    return formataCampo(cnpj, '00.000.000/0000-00', event);
}

function MascaraCep(cep) {
    if (mascaraInteiro(cep) == false) {
        event.returnValue = false;
    }
    return formataCampo(cep, '00.000-000', event);
}

function MascaraMMAA(data) {
    if (mascaraInteiro(data) == false) {
        event.returnValue = false;
    }
    return formataCampo(data, '00/00', event);
}

function MascaraNumero(data) {
    if (mascaraInteiro(data) == false) {
        event.returnValue = false;
    }
    return formataCampo(data, '0', event);
}

function MascaraData(data) {
    if (mascaraInteiro(data) == false) {
        event.returnValue = false;
    }
    return formataCampo(data, '00/00/0000', event);
}

function MascaraTelefone(tel) {
    if (mascaraInteiro(tel) == false) {
        event.returnValue = false;
    }
    return formataCampo(tel, '(00) 0000-0000', event);
}

function MascaraCPF(cpf) {
    if (mascaraInteiro(cpf) == false) {
        event.returnValue = false;
    }
    return formataCampo(cpf, '000.000.000-00', event);
}

function ValidaTelefone(tel) {
    exp = /\(\d{2}\)\ \d{4}\-\d{4}/
    if (!exp.test(tel.value)) alert('Numero de Telefone Invalido!');
}

function ValidaCep(cep) {
    exp = /\d{2}\.\d{3}\-\d{3}/
    if (!exp.test(cep.value)) alert('Numero de Cep Invalido!');
}

function ValidaData(data) {
    if (data.value == '')
      return;
    
    exp = /\d{2}\/\d{4}/
	
	if (data.value.substring(0, 2) > 12) {
	  alert('Mês inválido');
	  return;
	}
	
    if (!exp.test(data.value)) { 
	  alert('Formato da data inválida!');
      return;
	}
	
	console.log(data.value.substring(3, 7));
	
	if (data.value.substring(3, 7) < 2016) {
	  alert('Ano menor que o ano atual!');
	  return;
	}
	
}

function ValidarCPF(Objcpf) {
    var cpf = Objcpf.value;
    exp = /\.|\-/g
    cpf = cpf.toString().replace(exp, "");
    var digitoDigitado = eval(cpf.charAt(9) + cpf.charAt(10));
    var soma1 = 0,
        soma2 = 0;
    var vlr = 11;
    for (i = 0; i < 9; i++) {
        soma1 += eval(cpf.charAt(i) * (vlr - 1));
        soma2 += eval(cpf.charAt(i) * vlr);
        vlr--;
    }
    soma1 = (((soma1 * 10) % 11) == 10 ? 0 : ((soma1 * 10) % 11));
    soma2 = (((soma2 + (2 * soma1)) * 10) % 11);
    var digitoGerado = (soma1 * 10) + soma2;
    if (digitoGerado != digitoDigitado) alert('CPF Invalido!');
}

function mascaraInteiro() {
    if (event.keyCode < 48 || event.keyCode > 57) {
        event.returnValue = false;
        return false;
    }
    return true;
}

function formataCampo(campo, Mascara, evento) {
    var boleanoMascara;
    var Digitato = evento.keyCode;
    exp = /\-|\.|\/|\(|\)| /g
    campoSoNumeros = campo.value.toString().replace(exp, "");
    var posicaoCampo = 0;
    var NovoValorCampo = "";
    var TamanhoMascara = campoSoNumeros.length;;
    if (Digitato != 8) {
        for (i = 0; i <= TamanhoMascara; i++) {
            boleanoMascara = ((Mascara.charAt(i) == "-") || (Mascara.charAt(i) == ".") || (Mascara.charAt(i) == "/"));
			boleanoMascara = boleanoMascara || ((Mascara.charAt(i) == "(") || (Mascara.charAt(i) == ")") || (Mascara.charAt(i) == " "));
			if (boleanoMascara) {
                NovoValorCampo += Mascara.charAt(i);
                TamanhoMascara++;
            } else {
                NovoValorCampo += campoSoNumeros.charAt(posicaoCampo);
                posicaoCampo++;
            }
        }
        campo.value = NovoValorCampo;
        return true;
    } else {
        return true;
    }
}