<!DOCTYPE html>
<html lang="en">
   <head>
      <?php
        $nome          = isset($_POST['nm_atleta']) ? $_POST['nm_atleta'] : null;
        $identificador = isset($_POST['nr_ident' ]) ? $_POST['nr_ident' ] : null;  
        $categoria     = isset($_POST['cd_categ' ]) ? $_POST['cd_categ' ] : null;  
        echo  $categoria;
      ?>
      <meta charset="utf-8">
      <meta http-equiv="X-UA-Compatible" content="IE=edge">
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <meta name="description" content="">
      <meta name="author" content="">
      <title>Administrador</title>
      <link href="css/bootstrap.min.css" rel="stylesheet">
      <link href="css/business-casual.css" rel="stylesheet">
      <link rel="stylesheet" href="css/grid/style.css" type="text/css" media="print, projection, screen" />
      <script language="JavaScript" type="text/javascript" src="js/jquery.js"></script> 
      <script language="JavaScript" type="text/javascript" src="js/tablesorter.js"></script> 
      <script language="JavaScript" type="text/javascript" src="js-util.js"></script> 
   </head>
   <body>
	
	  <div class="brand">Resultados</div>
	  
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
                </ul>
            </div>
            <!-- /.navbar-collapse -->
        </div>
        <!-- /.container -->
    </nav>
	
      <form name="res" action="resultados.php" method="POST">
        <div class="container">
           <div class="row">
              <div class="box">
                 <div class="col-lg-12 text-center">
                    <div class="carousel-inner">
                       <hr>
                       <h1 class="brand-name">Resultados</h1>
                       <hr>
                       <div class="form-group col-lg-2">
                          <label for="fNins">Número de inscrição</label>
                          <input type="text" id="nr_ident" name="nr_ident" class="form-control" maxlength="10" placeholder="Nº inscrição" value="<?php echo $identificador ?>"> 
                       </div>
                       <div class="form-group col-lg-5">
                          <label for="fNomeCompl">Nome completo</label>
                          <input type="text" id="nm_atleta" name="nm_atleta" class="form-control" placeholder="Nome completo" value="<?php echo $nome ?>">
                       </div>
                       <div class="form-group col-lg-5">
                          <label for="cbxSexo">Categoria</label>
                          <select class="form-control" id="cd_categ" name="cd_categ" placeholder="Categoria" selected="selected">
                            <?php
                              echo '<option value="1"  '. ($categoria == 1  ? 'selected=\"selected\"' : '""') .'> Geral Masculino 10km</option>            ';
                              echo '<option value="2"  '. ($categoria == 2  ? 'selected=\"selected\"' : '""') .'> Geral Masculino 21km</option>            ';
                              echo '<option value="3"  '. ($categoria == 3  ? 'selected=\"selected\"' : '""') .'> Geral Masculino 42km</option>            ';
                              echo '<option value="4"  '. ($categoria == 4  ? 'selected=\"selected\"' : '""') .'> Geral Feminino 10km</option>             ';
                              echo '<option value="5"  '. ($categoria == 5  ? 'selected=\"selected\"' : '""') .'> Geral Feminino 21km</option>             ';
                              echo '<option value="6"  '. ($categoria == 6  ? 'selected=\"selected\"' : '""') .'> Geral Feminino 42km</option>             ';
                              echo '<option value="7"  '. ($categoria == 7  ? 'selected=\"selected\"' : '""') .'> Masculino 10km acima de 60 anos</option> ';
                              echo '<option value="8"  '. ($categoria == 8  ? 'selected=\"selected\"' : '""') .'> Masculino 21km acima de 60 anos</option> ';
                              echo '<option value="9"  '. ($categoria == 9  ? 'selected=\"selected\"' : '""') .'> Masculino 42km acima de 60 anos</option> ';
                              echo '<option value="10" '. ($categoria == 10 ? 'selected=\"selected\"' : '""') .'>Feminino 10km acima de 60 anos</option>  ';
                              echo '<option value="11" '. ($categoria == 11 ? 'selected=\"selected\"' : '""') .'>Feminino 21km acima de 60 anos</option>  ';
                              echo '<option value="12" '. ($categoria == 12 ? 'selected=\"selected\"' : '""') .'>Feminino 42km acima de 60 anos</option>  ';
                              echo '<option value="" '. ($categoria == null ? 'selected=\"selected\"' : '""') .'></option>  ';
                            ?>
                          </select>
                       </div>
                       <div class="row">
                          <div class="form-group col-lg-5">
                          </div>
                          <div class="form-group col-lg-2">
                             <button type="submit" class="form-control btn btn-default" style="background-color:Green;color:white" data-toggle="modal" data-target="#myModal">Enviar</button>
                          </div>
                       </div>
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
                                 $resultado = $calculadorRes->calculaResultado($nome, $identificador, $categoria, null);
                                 
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
         });
      </script>
   </body>
</html>