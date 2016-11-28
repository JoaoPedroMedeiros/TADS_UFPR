<?php
  require_once("IQuery.php");
  require_once("MySQLConnection.php");
  require_once("JSONFormatterDefault.php");
  
  class MySQLQuery implements IQuery {
    
    private function simpleExec($conn, $sql) {
      //Conecta com o banco de dados.
      $conn->connect();
      
      //Executa a query.
      $result = $conn->execQuery($sql);
      
      if (!$result) {
        http_response_code(404);
        die($conn->getError());
      }
      
      //Fecha a conexão
      $conn->close();
      
      return $result;
    }
    
    public function exec($sql) {
      $this->execFormat($sql, $this->getFormatterDefault());
    }
    
    public function execFormat($sql, $formatter) {
      //Executa a consulta
      $conn = $this->getConnection();
      $result = $this->simpleExec($conn, $sql);
      
      //Retorna no formato JSON.
      $formatter->format($conn, $result);
    }
    
    public function singleResult($sql) {
      $conn = $this->getConnection();
      $result = $this->simpleExec($conn, $sql);
      
      return $conn->fetchArray($result)[0];
    }
    
    public function result($sql) {
      $conn = $this->getConnection();
      return $this->simpleExec($conn, $sql);
    }
    
    public function getConnection() {
      return new MySQLConnection();
    }
    
    private function getFormatterDefault() {
      return new JSONFormatterDefault();
    }
  }
?>