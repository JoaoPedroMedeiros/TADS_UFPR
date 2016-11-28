<?php

  interface IQuery {
    
    /**
     * Recupera o componente de conexão (IConnection) específico do componente de Query.
     */
    public function getConnection();
    
    /**
     * Executa a query.
     */
    public function exec($sql);
    
    /**
     * Executa a query recebendo um formatter de JSON para personalizar o resultado
     */
    public function execFormat($sql, $formatter);
    
    /**
     * Executa a query e retorna o valor do primeiro campo da primeira linha.
     */
    public function singleResult($sql);
    
    /**
     * Executa um update/insert no banco.
     */
     public function result($sql);
  }
?>

