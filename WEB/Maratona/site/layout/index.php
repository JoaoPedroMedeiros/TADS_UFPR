<!DOCTYPE html>
<html lang="en">

<head>
    <?php  
       session_start();
       $logado = '';
       if (!isset ($_SESSION['nome']))
          unset($_SESSION['nome']);
       else
         $logado = $_SESSION['nome'];
       
       $codigo = '';
       if (!isset ($_SESSION['codigo']))
          unset($_SESSION['codigo']);
       else
         $codigo = $_SESSION['codigo'];
       
       if ($codigo == 1)
         header('location:admin.php');
    ?> 

    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="description" content="">
    <meta name="author" content="">

    <title>Página inicial</title>

    <!-- Bootstrap Core CSS -->
    <link href="css/bootstrap.min.css" rel="stylesheet">

    <!-- Custom CSS -->
    <link href="css/business-casual.css" rel="stylesheet">

</head>

<body>

    <div class="brand">Maratona de Santo Ângelo - RS</div>
    <div class="address-bar">Praça catedral</div>

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
                    <li>
                        <a href="index.php">Inicial</a>
                    </li>
                    <li>
                        <a href="#Ancora1">Percursos</a>
                    </li>
                    <li>
                        <a href="#Ancora2">Kits</a>
                    </li>
                    <li>
                        <a href="#Ancora3">Informações</a>
                    </li>
                    <li>
                        <a href="resultados.php">Resultados</a>
                    </li>
                    <?php
                      $usuarioLogado = $logado != '';
                      if ($usuarioLogado) {
                        echo 
                           '<li>                                     '.
                           '  <a href="inscrever.php">Participar</a>'.
                           '</li>';
                        echo 
                           '<li>                                     '.
                           '  <a href="deslogar.php?req=index.php"><strong>Sair</strong></a>'.
                           '</li>';
                      }
                      else
                        echo 
                           '<li>                                               '.
                           '    <a href="login.php"><strong>Login</strong></a>'.
                           '</li>                                              ';
                    ?>
                </ul>
            </div>
            <!-- /.navbar-collapse -->
        </div>
        <!-- /.container -->
    </nav>

    <div class="container">

        <div class="row">
			<a name="Ancora1"></a> 		
            <div class="box">
                <div class="col-lg-12 text-center">
                    <div id="carousel-example-generic" class="carousel slide">
                        <!-- Indicators -->
                        <ol class="carousel-indicators hidden-xs">
                            <li data-target="#carousel-example-generic" data-slide-to="0" class="active"></li>
                            <li data-target="#carousel-example-generic" data-slide-to="1"></li>
                            <li data-target="#carousel-example-generic" data-slide-to="2"></li>
                        </ol>

                        <!-- Wrapper for slides -->
                        <div class="carousel-inner">
                            <h2 class="brand-before">
                              <small><?php echo 'BEM-VINDO '. strtoupper($logado)?></small>
                            </h2>
                            <hr>
                            <h1 class="brand-name">Percursos</h1>
                            <hr>
                            <div class="item active">
                                <img class="img-responsive img-full" src="img\mapas\42km.PNG" alt="">
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>

        <div class="row">
			<a name="Ancora2"></a>
            <div class="box">
                <div class="col-lg-12 text-center">
                    <hr>
                    <h1 class="brand-name">Kits</h1>
                    <hr>
					
					<div class="row">
						<div class="col-sm-4">
							<h2 class="brand-before">
								<small>Kit básico</small>
							</h2>
							<img class="img-responsive img-border img-center" src="img\kits\basico.PNG" alt="">
						</div>
						<div class="col-sm-4">
							<h2 class="brand-before">
								<small>Kit plus</small>
							</h2>
							<img class="img-responsive img-border img-center" src="img\kits\plus.PNG" alt="">
						</div>
						<div class="col-sm-4">
							<h2 class="brand-before">
								<small>Kit vip</small>
							</h2>
							<img class="img-responsive img-border img-center" src="img\kits\vip.PNG" alt="">
						</div>
					</div>
                </div>
            </div>
        </div>

        <div class="row">
			<a name="Ancora3"></a>
            <div class="box">
                <div class="col-lg-12">
                    <hr>
                    <h2 class="intro-text text-center">Bem-vindo à maratona de 
                        <strong>Santo Ângelo - RS</strong>
                    </h2>
                    <hr>
                    <p class="text-justify">No dia <strong>14/01/2017</strong> acontecerá na histórica cidade de Santo Ângelo a 100º maratona missioneira.</p>
       					<p class="text-justify">A cerimônia de abertura será iniciada às <strong>7:00</strong> da manhã na <strong>catedral Angelopolitana</strong> e terminará na cidade de <strong>Entre-Ijuís</strong>, no <strong>Museu Antropológico Diretor Pestana</strong>, e contará com um churrasco comemorativo pelos 100 anos de sucesso do evento.</p>
       					<p class="text-justify">O participante poderá escolher entre três categorias, 10 km, 21 km e 42 km, de acordo com a sua resistência física. As categorias também serão divididas por sexo e idade. O atleta precisa ser maior de 18 anos.</p>
       					<p class="text-justify">Os patrocinadores oferecem kits com preços simbólicos para os participantes. São eles:</p>
       					<p class="text-justify">Kit Básico - R$ 100,00</p>
       					<p class="text-justify">Kit Plus - R$ 130,00</p>
       					<p class="text-justify">Kit Vip - R$ 180,00</p>
       					<p class="text-justify">Todos os kits incluem a inscrição para a maratona e para a confraternização de encerramento.</p>
       					<p class="text-justify">Desejamos à todos uma boa corrida!</p>
                    <p></p>
                </div>
            </div>
        </div>
		
        <div class="box">
		<div class="row">
                <div class="col-sm-12 text-center">
					<hr>
                    <h2 class="intro-text text-center">Patrocinadores</h2>
                    <hr>
					<div class="col-sm-2">
						<img width="100" height="75" class="img-responsive img-center" src="img\logo\caixa.png" alt="">
					</div>                                                     
					<div class="col-sm-2">                                     
						<img width="100" height="75" class="img-responsive img-center" src="img\logo\churrascaria.png" alt="">
					</div>                                                     
					<div class="col-sm-2">                                     
						<img width="100" height="75" class="img-responsive img-center" src="img\logo\IESA.png" alt="">
					</div>                                                     
					<div class="col-sm-2">                                     
						<img width="100" height="75" class="img-responsive img-center" src="img\logo\rodobens.png" alt="">
					</div>                                                     
					<div class="col-sm-2">                                     
						<img width="100" height="75" class="img-responsive img-center" src="img\logo\RS.png" alt="">
					</div>                                                     
					<div class="col-sm-2">                                     
						<img width="100" height="75" class="img-responsive img-center" src="img\logo\strat_lab.png" alt="">
					</div>
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

    <!-- Script to Activate the Carousel -->
    <script>
    $('.carousel').carousel({
        interval: 5000 //changes the speed
    })
    </script>

</body>

</html>
