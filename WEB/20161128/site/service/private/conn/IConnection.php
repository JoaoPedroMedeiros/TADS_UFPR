<?php

  interface IConnection {
    
    /**
     * Conecta com o banco de dados.
     */
    public function connect();
    
    /**
     * Conecta com o banco de dados.
     */
    public function close();
    
    /**
     * Recupera um erro depois de alguma execução de SQL.
     */
    public function getError();
    
    /**
     * Executa uma query recebendo um objeto de conexão e o SQL do Select.
     */
    public function execQuery($sql);
    
    /**
     * Recebe um result e retorna o número de linhas existentes.
     */
    public function rowsNumber($result);
    
    /**
     * Recebe um resultset e passa ele para próxima linha em forma de objeto.
     */
    public function fetchObject($result);
    
    /**
     * Recebe um resultset e passa ele para próxima linha em forma de array.
     */
    public function fetchArray($result);
  }
?>