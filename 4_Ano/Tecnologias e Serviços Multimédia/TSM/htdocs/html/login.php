<?php
require_once 'function.php';
session_start();
if(isset($_POST['sub'])){
    $username = $_POST['username'];
    $password = $_POST['password'];
    $dados = valida_utilizador($username, $password);
    
    if ($dados) {
            $_SESSION['fristname'] = $dados['fristname'];
            $_SESSION['lastname'] = $dados['lastname'];
            $_SESSION['username'] = $dados['username'];
            $_SESSION['age'] = $dados['age'];
            $_SESSION['gender'] = $dados['gender'];
            $_SESSION['email'] = $dados['email'];
            $_SESSION['password'] = $dados['password'];
            $_SESSION['mynumber'] = $dados['mynumber'];
            $_SESSION['fristsosnumber'] = $dados['fristsosnumber'];
            $_SESSION['secondsosnumber'] = $dados['secondsosnumber'];
            $_SESSION['thirdsosnumber'] = $dados['thirdsosnumber'];     
            $_SESSION['admin'] = $dados['admin'];
            $_SESSION['idUser'] = $dados['idUser'];
            if ($_SESSION['admin'] == true) {
                header('Location: admin.php');
            }
            else if ($_SESSION['admin'] == false) {
                header('Location: client.php');
            }
    } 
    else {
           header('Location: login.php');
    }
}
?>

<!DOCTYPE html>
<html lang="en">

<head>

    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="description" content="">
    <meta name="author" content="">

    <title>GPStracker</title>

    <!-- Bootstrap Core CSS -->
    <link href="vendor/bootstrap/css/bootstrap.min.css" rel="stylesheet">

    <!-- Custom Fonts -->
    <link href="vendor/font-awesome/css/font-awesome.min.css" rel="stylesheet" type="text/css">
    <link href='https://fonts.googleapis.com/css?family=Open+Sans:300italic,400italic,600italic,700italic,800italic,400,300,600,700,800' rel='stylesheet' type='text/css'>
    <link href='https://fonts.googleapis.com/css?family=Merriweather:400,300,300italic,400italic,700,700italic,900,900italic' rel='stylesheet' type='text/css'>

    <!-- Plugin CSS -->
    <link href="vendor/magnific-popup/magnific-popup.css" rel="stylesheet">

    <!-- Theme CSS -->
    <link href="css/creative.min.css" rel="stylesheet">

    <!-- HTML5 Shim and Respond.js IE8 support of HTML5 elements and media queries -->
    <!-- WARNING: Respond.js doesn't work if you view the page via file:// -->
    <!--[if lt IE 9]>
        <script src="https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js"></script>
        <script src="https://oss.maxcdn.com/libs/respond.js/1.4.2/respond.min.js"></script>
    <![endif]-->

</head>

<body id="page-top">

    <nav id="mainNav" class="navbar navbar-default navbar-fixed-top">
        <div class="container-fluid">
            <!-- Brand and toggle get grouped for better mobile display -->
            <div class="navbar-header">
                <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#bs-example-navbar-collapse-1">
                    <span class="sr-only">Toggle navigation</span> Menu <i class="fa fa-bars"></i>
                </button>
                <a class="navbar-brand page-scroll" href="#page-top">Universidade do Minho</a>
            </div>

            <!-- Collect the nav links, forms, and other content for toggling -->
            <div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">
                <ul class="nav navbar-nav navbar-right">
                    <li>
                        <a href="index.html">Home</a>
                    </li>
                </ul>
            </div>
            <!-- /.navbar-collapse -->
        </div>
        <!-- /.container-fluid -->
    </nav>
    
    <header>
        <div class="header-content">
            <div class="header-content-inner" id="colorLogin">
                <h1 id="homeHeading">LOGIN</h1>
                <hr>
                <p>Please enter your credentials!</p> 
            </div>
        </div>
    </header>
    
    <section class="bg-primary">
        <div class="container">
            <div class="row">
                <div class="col-lg-8 col-lg-offset-2 text-center">
                   <form method="POST">
                    <label style="width: 15%;">Username</label>
                    <input type="text" placeholder="USERNAME" style="color: black" size="20" name="username"><br>
                    <label style="width: 15%;">Password</label>
                    <input type="password" placeholder="PASSWORD" style="color: black" size="20" name="password" id="pass"><br>
                    
                    <label style="width: 15%;">Show password</label>
                    <input type="checkbox" onchange="document.getElementById('pass').type = this.checked ? 'text' : 'password'"><br><br>
                    <input class="page-scroll btn btn-default btn-xl sr-button" type="submit" name="sub" value="Login">
                </form>  
                </div>
            </div>
        </div>
    </section>


    <!-- jQuery -->
    <script src="vendor/jquery/jquery.min.js"></script>

    <!-- Bootstrap Core JavaScript -->
    <script src="vendor/bootstrap/js/bootstrap.min.js"></script>

    <!-- Plugin JavaScript -->
    <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery-easing/1.3/jquery.easing.min.js"></script>
    <script src="vendor/scrollreveal/scrollreveal.min.js"></script>
    <script src="vendor/magnific-popup/jquery.magnific-popup.min.js"></script>

    <!-- Theme JavaScript -->
    <script src="js/creative.min.js"></script>

</body>

</html>

