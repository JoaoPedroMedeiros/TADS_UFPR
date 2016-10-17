<?php
  require_once("IQuery.php");
  require_once("MySQLConnection.php");
  require_once("JSONFormatterDefault.php");
  
  class MySQLQuery implements IQuery {
    
    public function exec($sql) {
      $this->execFormat($sql, $this->getFormatterDefault());
    }
    
    public function execFormat($sql, $formatter) {
      //Conecta com o banco de dados.
      $conn = $this->getConnection();
      $conn->connect();
      
      //Executa a query.
      $result = $conn->execQuery($sql);
      
      if (!$result) {
        http_response_code(404);
        die(mysqli_error());
      }
      
      //Retorna no formato JSON.
      $formatter->format($conn, $result);
      
      //Fecha a conexão
      $conn->close();
    }
    
    public function getConnection() {
      return new MySQLConnection();
    }
    
    private function getFormatterDefault() {
      return new JSONFormatterDefault();
    }
  }
?>