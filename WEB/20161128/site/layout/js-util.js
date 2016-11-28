/**
 * Função que preenche uma combobox apartir de uma lista.
 */
function preencheCombobox(cbx, itens, chave, valor) {
  cbx.options.length = itens.length;
  for (i = 0; i < itens.length; ++i)
    cbx.options[i] = new Option(itens[i][valor], itens[i][chave]);  
}