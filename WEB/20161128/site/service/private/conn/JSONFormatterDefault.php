<?php
  require_once("JSONFormatter.php");

  class JSONFormatterDefault implements JSONFormatter {
    
    public function format($conn, $resultQuery) {

      $result = array();
      for ($i=0; $i < $conn->rowsNumber($resultQuery); $i++)
        $result[$i] = $conn->fetchObject($resultQuery);
      
      echo json_encode($result);
    }
  }
?>