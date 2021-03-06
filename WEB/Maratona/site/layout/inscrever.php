<!DOCTYPE html>
<html lang="en">
   <head>
      <meta charset="utf-8">
      <meta http-equiv="X-UA-Compatible" content="IE=edge">
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <meta name="description" content="">
      <meta name="author" content="">
      <title>Inscrever-se</title>
      <script language="JavaScript" type="text/javascript" src="MascaraValidacao.js"></script> 
      <script language="JavaScript" type="text/javascript" src="Inscrever.js"></script> 
      <!-- Bootstrap Core CSS -->
      <link href="css/bootstrap.min.css" rel="stylesheet">
      <!-- Custom CSS -->
      <link href="css/business-casual.css" rel="stylesheet">
      <?php
        session_start();
        $codigo = null;
        if (!isset($_SESSION['codigo']))
          header('location:login.php');
        else
          $codigo = $_SESSION['codigo'];
          
      ?>
   </head>
   <body>
      <div class="brand">Inscrever-se</div>
	  
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
      <div class="container">
         <form name="Inscrever" onsubmit="return inscrever(this);">
            <div class="row">
               <div class="box">
                  <div class="col-lg-12 text-center">
                     <hr>
                     <h1 class="brand-name">Kits</h1>
                     <h2 class="brand-before">
                        <small>Escolha seu kit</small>
                     </h2>
                     <hr>   
                     <?php
                       echo 
                        '<div class="col-lg-0">'.
                          '<input type="hidden" name="fCodigoAtleta" value='. $codigo .' />'.
                        '</div>';
                     ?>
                     <div class="row">
                        <div class="col-sm-4">
                           <h2 class="brand-before">
                              <label class="form-check-inline">
                                 <small>
                                   <input class="form-check-input" type="radio" name="rbgKit" id="inlineRadio1" value="3">
                                   Kit básico - R$ 100,00
                                 </small>
                              </label>
                           </h2>
                           <img class="img-responsive img-border img-center" src="img\kits\basico.PNG" alt="">
                        </div>
                        <div class="col-sm-4">
                           <h2 class="brand-before">
                              <label>
                                 <small>
                                    <input class="form-check-input" type="radio" name="rbgKit" id="inlineRadio2" value="2">
                                    Kit plus - R$ 130,00
                                 </small>
                              </label>
                           </h2>
                          <img class="img-responsive img-border img-center" src="img\kits\plus.PNG" alt="">
                        </div>
                        <div class="col-sm-4">
                           <h2 class="brand-before">
                              <label>
                                 <small>
                                    <input class="form-check-input" type="radio" name="rbgKit" id="inlineRadio3" value="1">
                                    Kit vip - R$ 180,00
                                 </small>
                              </label>
                           </h2>
                           <img class="img-responsive img-border img-center" src="img\kits\vip.PNG" alt="">
                        </div>
                     </div>
                     <div class="row">
                        <div class="col-sm-4">
                           <div class="col-sm-12">
                              <label>Camiseta</label>
                           </div>
                           <div class="col-sm-12">
                              <label>Sacola de treino</label>
                           </div>
                           <div class="col-sm-12">
                              <label>Medalha de participação</label>
                           </div>
                           <div class="col-sm-12">
                           <label>Boné</label>  
                           </div>
                        </div>
                        <div class="col-sm-4">
                           <div class="col-sm-12">
                              <label>Camiseta</label>
                           </div>
                           <div class="col-sm-12">
                              <label>Sacola de treino</label>
                           </div>
                           <div class="col-sm-12">
                              <label>Medalha de participação</label>
                           </div>
                           <div class="col-sm-12">
                              <label>Cinto de hidratação</label>  
                           </div>
                           <div class="col-sm-12">
                              <label>Boné</label>  
                           </div>
                        </div>
                        <div class="col-sm-4">
                           <div class="col-sm-12">                           
                              <label>Camiseta</label>
                           </div>
                           <div class="col-sm-12">
                              <label>Sacola de treino</label>
                           </div>
                           <div class="col-sm-12">
                              <label>Medalha de participação</label>
                           </div>
                           <div class="col-sm-12">
                              <label>Jaqueta esportiva</label>  
                           </div>
                        </div>
                     </div>
                     <div class="row">
                        <div class="col-lg-1 col-md-1 col-sm-2 col-xs-3">
                           <label>Tamanho camiseta:</label>
                        </div>
                        <div class="col-lg-2 col-md-2 col-sm-2 col-xs-3">
                           <select class="form-control" id="cbxTamanho" placeholder="Tamanho">
                              <option value="PP">PP</option>
                              <option value="P">P</option>
                              <option value="M">M</option>
                              <option value="G">G</option>
                              <option value="GG">GG</option>
                           </select>
                        </div>
                     </div>
                  </div>
               </div>
            </div>
            <div class="row">
               <div class="box">
                  <div class="col-lg-12 text-center">
                     <div>
                        <!-- Wrapper for slides -->
                        <div class="carousel-inner">
                           <hr>
                           <h1 class="brand-name">Modalidade</h1>
                           <h2 class="brand-before">
                              <small>Escolha sua modalidade</small>
                           </h2>
                           <div class="row">
                              <div class="col-lg-4">
                                 <label>
                                    <input class="form-check-input" type="radio" name="rbgModalidade" id="inlineRadio1" value="1">
                                    10 km
                                 </label>
                              </div>
                              <div class="col-lg-4">
                                 <label>
                                    <input class="form-check-input" type="radio" name="rbgModalidade" id="inlineRadio2" value="2">
                                    21 km
                                 </label>
                              </div>
                              <div class="col-lg-4">
                                 <label>
                                    <input class="form-check-input" type="radio" name="rbgModalidade" id="inlineRadio3" value="3">
                                    42 km
                                 </label>
                              </div>
                           </div>
                           <img class="img-responsive img-full" src="img\mapas\42km.PNG" alt="">
                        </div>
                     </div>
                  </div>
               </div>
            </div>
            <div class="row">
               <div class="box">
                  <div class="col-lg-12">
                     <hr>
                     <h2 class="intro-text text-center">Pagamento</h2>
                     <hr>
                  </div>
                  <div class="row">
                     <div class="col-sm-12 text-center">
                        <div class="col-sm-1">
                           <input class="form-check-input" type="radio" name="rbgCartao" id="inlineRadio1" value="0">
                           <img width="40" height="40" class="img-responsive img-center" src="img\cartao\master.png" alt="">
                        </div>
                        <div class="col-sm-1">            
                           <input class="form-check-input" type="radio" name="rbgCartao" id="inlineRadio2" value="0">
                           <img width="40" height="40" class="img-responsive img-center" src="img\cartao\visa.png" alt="">
                        </div>
                        <div class="col-sm-1">
                           <input class="form-check-input" type="radio" name="rbgCartao" id="inlineRadio3" value="0">
                           <img width="40" height="40" class="img-responsive img-center" src="img\cartao\elo.png" alt="">
                        </div>
                     </div>
                  </div>
                  <div class="row">
                     <div class="form-group col-lg-3">
                        <label>Número cartão</label>
                        <input type="tel" class="form-control" id="fNrCartao" maxlength="16"> 
                     </div>
                     <div class="form-group col-lg-2">
                        <label>Cod. segurança</label>
                        <input type="tel" class="form-control" id="fCodSeguranca" maxlength="3">
                     </div>
                  </div>
                  <div class="row">
                     <div class="form-group col-lg-3">
                        <label>Data validade (MM/AAAA)</label>
                        <input type="text" name="data" class="form-control" id="fDataVal" onKeyPress="MascaraMMAA(Inscrever.data);" onBlur="ValidaData(Inscrever.data);"maxlength="7">
                     </div>
                  </div>
                  <div class="row">
                     <div class="form-group col-lg-3">
                        <label>Nome titular</label>
                        <input type="tel" class="form-control" id="fNome">
                     </div>
                  </div>
                  <div class="form-group col-lg-2">
                     <button type="submit" class="form-control btn btn-default" style="background-color:Green;color:white" data-toggle="modal" data-target="#myModal">Confirmar</button>
                  </div>
               </div>
            </div>
         </form>
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