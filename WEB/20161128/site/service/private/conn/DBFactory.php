<?php

  require_once("MySQLQuery.php");

  class DBFactory {
      
    public function getQuery() {
      return new MySQLQuery();
    }
  }
?>