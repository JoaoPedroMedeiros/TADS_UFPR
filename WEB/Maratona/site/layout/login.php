<!DOCTYPE html>
<html lang="en">
   <head>
      <meta charset="utf-8">
      <meta http-equiv="X-UA-Compatible" content="IE=edge">
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <meta name="description" content="">
      <meta name="author" content="">
      <title>Login</title>
      <!-- Bootstrap Core CSS -->
      <link href="css/bootstrap.min.css" rel="stylesheet">
      <!-- Custom CSS -->
      <link href="css/business-casual.css" rel="stylesheet">
      <script language="JavaScript" type="text/javascript" src="login.js"></script> 
      <?php
        session_start();
        $invalido = isset ($_GET['response']);
      ?>
   </head>
   <body>
	  
	  <div class="brand">Login</div>
	  
	  <nav class="navbar navbar-default" role="navigation">
        <div class="container">
            <!-- Brand and toggle get grouped for better mobile display -->
            <div class="navbar-header">
                <button type="button" class="navbar-toggle" data-toggle="collapse" data-target="#bs-example-navbar-collapse-1">
                    <span class="sr-only">Toggle navigation</span>
                    <span class="icon-bar"></span>
                    <span class="icon-bar"></span>
                    <span class="icon-bar"></span>
                </button>
                <!-- navbar-brand is hidden on larger screens, but visible when the menu is collapsed -->
                <a class="navbar-brand" href="index.php">Business Casual</a>
            </div>
            <!-- Collect the nav links, forms, and other content for toggling -->
            <div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">
                <ul class="nav navbar-nav">
                    <!-- Menus sempre existentes -->
                    <li>
                        <a href="index.php">Inicial</a>
                    </li>
					<li>
                        <a href="resultados.php">Resultados</a>
                    </li>
                </ul>
            </div>
            <!-- /.navbar-collapse -->
        </div>
        <!-- /.container -->
    </nav>
   
      <!-- Navigation -->
      <div class="container">
         <div class="row">
            <div class="box">
               <div class="col-lg-12 col-md-12">
                  <hr>
                  <h2 class="intro-text text-center">BEM-VINDO</h2>
                  <hr>
                  <form class="form form-default" action="../service/public/validaLogin.php" method="POST">                     
					<div class="row">
					   <div class="col-lg-4">
					   </div>
					   <div class="col-lg-4">
						  <div class="form-group">
							 <label>E-mail</label>
							 <input type="text" class="form-control" name="nm_login">
						  </div>
					   </div>
					</div>
					<div class="row">
						<div class="col-lg-4">
					   </div>
					   <div class="col-lg-4">
						  <div class="form-group">
							 <label>Senha</label>
							 <input type="password" class="form-control" name="ds_senha">
							 <?php
							   if ($invalido)
							   echo '<label style="color:red">Usuário ou senha inválidos</label>'
							 ?>
						  </div>
					   </div>
					</div>
					<div class="row">
					   <div class="col-lg-7">
					   </div>
					   <label style="cursor:pointer;text-decoration: underline" onClick="redirecionaParaCadastro()">Cadastrar-se</label>
					</div>
					<div class="row">
					   <div class="col-lg-7">
					   </div>
					   <div class="col-lg-2">
						  <div class="form-group">
							 <button type="submit" class="btn btn-default" style="background-color:Green;color:white">Entrar</button>
						  </div>
					   </div>
					</div>
                  </form>
               </div>
            </div>
         </div>
      </div>
      <!-- /.container -->
      <footer>
         <div class="container">
            <div class="row">
               <div class="col-lg-12 text-center">
                  <p>Copyright &copy; UFPR - TADS 2016</p>
               </div>
            </div>
         </div>
      </footer>
      <!-- jQuery -->
      <script src="js/jquery.js"></script>
      <!-- Bootstrap Core JavaScript -->
      <script src="js/bootstrap.min.js"></script>
   </body>
</html>