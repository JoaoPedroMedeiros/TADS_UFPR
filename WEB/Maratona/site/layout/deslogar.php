<?php  
     $requisicao = $_GET["req"];
     
     session_start();
     unset($_SESSION['codigo']);
     unset($_SESSION['nome']);
     
     header('location:'.$requisicao);
?> 