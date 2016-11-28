<?php  
     print_r($_GET);

     $requisicao = $_GET["req"];
     
     echo $requisicao;
     
     session_start();
     unset($_SESSION['nome']);
     
     header('location:'.$requisicao);
?> 