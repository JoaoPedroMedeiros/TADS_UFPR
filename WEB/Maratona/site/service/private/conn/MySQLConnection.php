<?php

  require_once("IConnection.php");

  class MySQLConnection implements IConnection {
    
    /**
     * Parâmetros para conexão com o banco de dados.
     */
    private $hostname = "127.0.0.1";
    private $user     = "root";
    private $password = "";
    private $bdname   = "maratona";
    
    /**
     * Abstração da conexão.
     */
    private $conn;
    
    public function connect() {
      
      $this->conn = mysqli_connect($this->hostname, $this->user, $this->password, $this->bdname);
      mysqli_set_charset($this->conn, 'utf8');
      
      return true;
    }
    
    public function close() {
      mysqli_close($this->conn);
    }
    
    public function execQuery($sql) {
      return mysqli_query($this->conn, $sql);
    }
    
    public function rowsNumber($result) {
      return mysqli_num_rows($result);
    }
    
    public function fetchObject($result) {
      return mysqli_fetch_object($result);
    }
    
    public function fetchArray($result) {
      return mysqli_fetch_array($result);
    }
  }
?>