<?php
    session_start();
    if (isset($_POST['logout'])) {
        session_destroy();
        header('location: index.html');
    }
    if (isset($_SESSION['username'])) {
        $fristname = $_SESSION['fristname'];
        $lastname = $_SESSION['lastname'];
        $username = $_SESSION['username'];
        $age = $_SESSION['age'];
        $gender = $_SESSION['gender'];
        $email = $_SESSION['email'];
        $password = $_SESSION['password'];
        $mynumber = $_SESSION['mynumber'];
        $fristsosnumber = $_SESSION['fristsosnumber'];
        $secondsosnumber = $_SESSION['secondsosnumber'];
        $thirdsosnumber = $_SESSION['thirdsosnumber'];
        $admin = $_SESSION['admin'];
        $idUser = $_SESSION['idUser'];
        
    } else {
        header('Location: index.html');
    }
    require_once 'function.php';  
    if(isset($_POST['sub'])) {
        $frist = $_POST['frist'];
        $last = $_POST['last'];
        $user = $_POST['user'];
        $idade = $_POST['aged'];
        $genero = $_POST['gend'];
        $mail = $_POST['mail'];
        $pass = $_POST['pass'];
        $number = $_POST['number'];
        $fristsos = $_POST['1sos'];
        $secondsos = $_POST['2sos'];
        $thirdsos = $_POST['3sos'];
        if ($frist == ''){ 
            $frist = $fristname;
        }
        if ($last == ''){ 
            $last = $lastname;
        }
        if ($user == ''){ 
            $user = $username;
        }
        if ($idade == ''){ 
            $idade = $age;
        }
        if ($genero == ''){ 
            $genero = $gender;
        }
        if ($mail == ''){ 
            $mail = $email;
        }
        if ($pass == ''){ 
            $pass = $password;
        }
        if ($number == ''){ 
            $number = $mynumber;
        }
        if ($fristsos == ''){ 
            $fristsos = $fristsosnumber;
        }
        if ($secondsos == ''){ 
            $secondsos = $secondsosnumber;
        }
        if ($thirdsos == ''){ 
            $thirdsos = $thirdsosnumber;
        }
        altera($frist, $last, $user, $idade, $genero, $mail, $pass, $number, $fristsos, $secondsos, $thirdsos, $admin, $idUser);  
        
        $dados = valida_utilizador($user, $pass);
    
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
            header('Location: client.php');
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
                        <form method="POST">
                        <button type="submit" style="margin-top: 11%; color: #939393; size: 10%;" name="logout" class="btn btn-link">Logout</button>
                        </form>
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
                <h1 id="homeHeading">your personal page</h1>
                <hr>
                <p>Hello, this is your personal page, you can edit your information and see all your sessions right here!
            </div>
        </div>
    </header>
    
    <section class="bg-primary">
        <div class="container">
            <div class="row">
                <div class="col-lg-8 col-lg-offset-2 text-center">
                    <h2 class="section-heading">Change personal information</h2><br><br>
                    <form method="POST">                      
                        <label style="width: 35%;"> <?php echo $fristname; ?></label>
                        <input type="text" placeholder="FIRST NAME" style="color: black;" size="20" name="frist"><br>

                        <label style="width: 35%;"><?php echo $lastname; ?></label>
                        <input type="text" placeholder="LAST NAME" style="color: black;" size="20" name="last"><br>
                        
                        <label style="width: 35%;"><?php echo $username; ?></label>
                        <input type="text" placeholder="USERNAME" style="color: black;" size="20" name="user"><br>

                        <label style="width: 35%;"><?php echo $age; ?></label>
                        <input type="int" placeholder="AGE" style="color: black;" size="20" name="aged"><br>

                        <label style="width: 35%;"><?php echo $gender; ?></label>
                        <input type="text" placeholder="GENDER" style="color: black;" size="20" name="gend"><br>

                        <label style="width: 35%;"><?php echo $email; ?></label>
                        <input type="text" placeholder="EMAIL" style="color: black;" size="20" name="mail"><br>

                        <label style="width: 35%;">Password</label>
                        <input type="password" placeholder="PASSWORD" style="color: black;" size="20" name="pass" id="pass"><br>
                        
                        <label style="width: 35%;"><?php echo $mynumber; ?></label>
                        <input type="int" placeholder="YOUR NUMBER" style="color: black;" size="20" name="number" id="phonenumber"><br>
                        
                        <label style="width: 35%;"><?php echo $fristsosnumber; ?></label>
                        <input type="int" placeholder="FIRST SOS NUMBER" style="color: black;" size="20" name="1sos" id="1sosnum"><br>
                      
                        <label style="width: 35%;"><?php echo $secondsosnumber; ?></label>
                        <input type="int" placeholder="SECOND SOS NUMBER" style="color: black;" size="20" name="2sos" id="2sosnum"><br>
                        
                        <label style="width: 35%;"><?php echo $thirdsosnumber; ?></label>
                        <input type="int" placeholder="THIRD SOS NUMBER" style="color: black;" size="20" name="3sos" id="3sosnum"><br>
                        
                        <label style="width: 35%;">Show password</label>
                        <input type="checkbox" onchange="document.getElementById('pass').type = this.checked ? 'text' : 'password'"><br><br>
                       
                        <input class="page-scroll btn btn-default btn-xl sr-button" type="submit" name="sub" value="Submit changes"> <br><br>
                               
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


