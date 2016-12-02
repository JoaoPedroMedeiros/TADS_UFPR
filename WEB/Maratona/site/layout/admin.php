<!DOCTYPE html>
<html lang="en">
   <head>
      <meta charset="utf-8">
      <meta http-equiv="X-UA-Compatible" content="IE=edge">
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <meta name="description" content="">
      <meta name="author" content="">
      <title>Administrador</title>
      <!-- Bootstrap Core CSS -->
      <link href="css/bootstrap.min.css" rel="stylesheet">
      <!-- Custom CSS -->
      <link href="css/business-casual.css" rel="stylesheet">
	    <script language="JavaScript" type="text/javascript" src="Atualizar.js"></script> 
      <link rel="stylesheet" href="css/grid/style.css" type="text/css" media="print, projection, screen" />
      <script language="JavaScript" type="text/javascript" src="js/jquery.js"></script> 
      <script language="JavaScript" type="text/javascript" src="js/tablesorter.js"></script> 
      <script language="JavaScript" type="text/javascript" src="js-util.js"></script> 
   </head>
   <body>
      <!-- Navigation -->
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
                  <?php
                     echo 
                        '<li>                                     '.
                        '  <a href="deslogar.php?req=index.php"><strong>Sair</strong></a>'.
                        '</li>';				  
                   ?>
               </ul>
            </div>
            <!-- /.navbar-collapse -->
         </div>
         <!-- /.container -->
      </nav>
	  <form name="Atualizar" onsubmit="return atualizar(this);">
		  <div class="container">
			 <div class="row">
				<div class="box">
				   <div class="col-lg-12 text-center">
					  <div class="carousel-inner">
						 <hr>
						 <h1 class="brand-name">Bem-vindo Administrador!</h1>
						 <h2 class="brand-before">
							<small>Cadastre os tempos dos inscritos</small>
						 </h2>
						 <hr>
             <div class="row">
               <div class="col-md-12">
                  <table cellspacing="1" class="tablesorter">
                     <colgroup>
                       <col style="width: 8%;">
                       <col style="width: 8%;">
                       <col style="width: 20%;">
                       <col style="width: 10%;">
                       <col style="width: 18%;">
                       <col style="width: 10%;">
                       <col style="width: 10%;">
                       <col style="width: 10%;">
                     </colgroup>
                     <thead>
                        <tr>
                           <th class="header">Posição</th>
                           <th class="header">Nr. insc.</th>
                           <th class="header">Nome</th>
                           <th class="header">Modalidade</th>
                           <th class="header">Categoria</th>
                           <th class="header">Tempo inicial</th>
                           <th class="header">Tempo final</th>
                           <th class="header">Veloc. média</th>
                        </tr>
                     </thead>
                     <tbody>
                       <?php
                         require_once('../service/private/entity/Resultado.php');
                         require_once('../service/private/conn/DBFactory.php');
                         require_once('../service/private/conn/JSONUtil.php');
                   
                         $calculadorRes = new Resultado();
                         $resultado = $calculadorRes->calculaResultado(null, null, null, null);
                         
                         $max = sizeof($resultado);
                         
                         for ($i = 0; $i < $max; $i++) {
                           echo 
                             '<tr class="odd">'.
                             '   <td> '. $resultado[$i]->nr_pos .'º </td>   '.
                             '   <td> '. $resultado[$i]->nr_ident .' </td>   '.
                             '   <td> '. $resultado[$i]->nm_atleta .' </td>   '.
                             '   <td> '. $resultado[$i]->ds_mod .' </td>   '.
                             '   <td> '. $resultado[$i]->ds_categ .' </td>   '.
                             '   <td> '. $resultado[$i]->nr_tempin .' </td>   '.
                             '   <td> '. $resultado[$i]->nr_tempfi .' </td>   '.
                             '   <td> '. $resultado[$i]->nr_velmed .' km/h </td>   '.
                             '</tr>';
                         }
                       ?>
                      </tbody>
                  </table>
               </div>
             </div>
						 <div class="form-group col-lg-1">
						 </div>
						 <div class="form-group col-lg-2">
							<label for="fNins">Número de inscrição</label>
							<input type="text" id="fNInscricao" class="form-control" maxlength="10" placeholder="Nº inscrição"> 
						 </div>
						 <div class="form-group col-lg-2">
						 </div>
						 <div class="form-group col-lg-2">
							<label for="ftempo">Tempo inicial</label>
							<input type="time" id="ftempoini" class="form-control"> 
						 </div>
						 <div class="form-group col-lg-2">
						 </div>
						 <div class="form-group col-lg-2">
							<label for="ftempo">Tempo final</label>
							<input type="time" id="ftempofim" class="form-control"> 
						 </div>
					  </div>
				   </div>
				   <div class="row">
					  <div class="form-group col-lg-5">
					  </div>
				   </div>
				   <div class="row">
					  <div class="form-group col-lg-5">
					  </div>
					  <div class="form-group col-lg-2">
						 <button type="submit" class="form-control btn btn-default" style="background-color:Green;color:white" data-toggle="modal" data-target="#myModal">Enviar</button>
					  </div>
				   </div>
				</div>
			 </div>
		  </div>
	  </form>
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
      <!-- Script to Activate the Carousel -->
      <script>
         $('.carousel').carousel({
             interval: 5000 //changes the speed
         })
      </script>
   </body>
</html>