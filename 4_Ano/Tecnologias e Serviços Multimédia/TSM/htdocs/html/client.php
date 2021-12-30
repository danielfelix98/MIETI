<?php
require_once 'function.php';
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
                            <a class="page-scroll" href="#info">Personal info</a>
                        </li>
                        <li>
                            <a class="page-scroll" href="#add">New route</a>
                        </li>
                        <li>
                            <a class="page-scroll" href="#all">All routes</a>
                        </li>
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

        <style>
            #map {
                height: 500px;
                width: 100%;
            }
        </style>

        <style>
            #map2 {
                height: 500px;
                width: 100%;
            }
        </style>

        <style>
            /* Dropdown Button */
            .dropbtn {
                border: none;
                cursor: pointer;
            }

            /* Dropdown button on hover & focus */
            .dropbtn:hover, .dropbtn:focus {
                background-color: #c9c7c7;
            }

            /* The container <div> - needed to position the dropdown content */
            .dropdown {
                position: relative;
                display: inline-block;
            }

            /* Dropdown Content (Hidden by Default) */
            .dropdown-content {
                display: none;
                position: absolute;
                background-color: #c9c7c7;
                min-width: 160px;
                box-shadow: 0px 8px 16px 0px rgba(0,0,0,0.2);
                z-index: 1;
            }

            /* Links inside the dropdown */
            .dropdown-content a {
                color: black;
                padding: 12px 16px;
                text-decoration: none;
                display: block;
            }

            /* Change color of dropdown links on hover */
            .dropdown-content a:hover {background-color: #f1f1f1}

            /* Show the dropdown menu (use JS to add this class to the .dropdown-content container when the user clicks on the dropdown button) */
            .show {display:block;}
        </style>

        <section class="bg-primary" id="info">
            <div class="container">
                <div class="row">
                    <div class="col-lg-8 col-lg-offset-2 text-center">
                        <h2 class="section-heading">Personal information</h2><br><br>
                        <label style="width: 50%;">Frist name: <?php echo $fristname; ?></label><br>

                        <label style="width: 50%;">Last name: <?php echo $lastname; ?></label><br>

                        <label style="width: 50%;">Username: <?php echo $username; ?></label><br>

                        <label style="width: 50%;">Age: <?php echo $age; ?></label><br>

                        <label style="width: 50%;">Gender: <?php echo $gender; ?></label><br>

                        <label style="width: 50%;">Email: <?php echo $email; ?></label><br>

                        <label style="width: 50%;">Phone number: <?php echo $mynumber; ?></label><br>

                        <label style="width: 50%;">1º SOS number: <?php echo $fristsosnumber; ?></label><br>

                        <label style="width: 50%;">2º SOS number: <?php echo $secondsosnumber; ?></label><br>

                        <label style="width: 50%;">3º SOS number: <?php echo $thirdsosnumber; ?></label><br><br> 

                        <a href="client2.php" class="page-scroll btn btn-default btn-xl sr-button">Change info</a>                       
                    </div>
                </div>
            </div>
        </section>

        <section id="add">
            <div class="container">
                <div class="row">
                    <div class="col-lg-8 col-lg-offset-2 text-center">
                        <h2 class="section-heading">Add a new route</h2><br><br>
                    </div>

                    <div id="map"></div>

                </div>
                <div class="col-lg-8 col-lg-offset-2 text-center">
                    <form id="addRoute">
                        <br>
                        <br>
                        <label style="width: 15%;">Route name</label>
                        <input id="routename" type="text" placeholder="NAME" style="color: black;" size="20" name="routename"><br>
                        <br>
                        <br>
                        <input onclick="envia_json()" class="btn btn-primary btn-xl page-scroll" type="submit" name="sub" value="Add route">
                    </form>  
                </div>
            </div>
        </section>

        <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
        <script>
                            var marker = [];
                            var latitude = [];
                            var longitude = [];
                            function initMap() {
                                var uluru = {lat: 41.45326927, lng: -8.28884125};
                                var map = new google.maps.Map(document.getElementById('map'), {
                                    zoom: 10,
                                    center: uluru
                                });
                                //Mapa das sessoes todas ***************************************
                                var map2 = new google.maps.Map(document.getElementById('map2'), {
                                    zoom: 10,
                                    center: uluru
                                });

                                //**************************************************************
                                map.addListener('rightclick', function (e) {
                                    placeMarker(e.latLng, map);
                                });
                            }
                            function putMarkers(latitude, longitude){
                                  var coordenadas = {lat: latitude, lng: longitude};
                                  var marker = new google.maps.Marker({
                                       position: coordenadas,
                                       map: map2
                                   });

                                   google.maps.event.trigger(map2, 'resize');
                            }
                            function placeMarker(latLng, map) {
                                var m = new google.maps.Marker({
                                    position: latLng,
                                    map: map
                                });
                                m.addListener('rightclick', function () {
                                    var index = marker.indexOf(m);
                                    marker.splice(index, 1);
                                    latitude.splice(index, 1);
                                    longitude.splice(index, 1);

                                    m.setMap(null);
                                });
                                marker.push(m);
                                latitude.push(m.getPosition().lat());
                                longitude.push(m.getPosition().lng());

                                map.panTo(latLng);
                            }
                            $("sub").click(function () {
                                envia_json();
                            });

                            function envia_json() {
                                var lat = JSON.stringify(latitude);
                                var lng = JSON.stringify(longitude);
                                var name = JSON.stringify(document.getElementById('routename').value);
                                $.ajax({
                                    url: "aux.php",
                                    type: "POST",
                                    data: {
                                        name: name,
                                        lat: lat,
                                        lng: lng
                                    }
                                });
                            }
        </script>               
        <script async defer
                src="https://maps.googleapis.com/maps/api/js?key=AIzaSyAvGutawyLFfdSUGnAk6QDHBwseq2pojlM&?libraries=drawing,places&sensor&callback=initMap">
        </script>

        <section class="bg-primary" id="all">

            <div class="container">

                <div class="row">

                    <div class="col-lg-8 col-lg-offset-2 text-center">
                        <h2 class="section-heading">All routes</h2><br><br>
                        <div>
                            <select id="selectBox" onchange="getValues();" class="page-scroll btn btn-default btn-xl sr-button dropbtn" style="position: relative;">
                                <option selected disabled hidden="true">Select route</option>
                                <?php
                                $ligacao = bd();
                                $query = "select * from routes where idUser= $idUser";
                                $result = mysqli_query($ligacao, $query);

                                while ($row = mysqli_fetch_array($result)) {
                                ?> 
                                    <option value="<?= $row['idRoute'] ?>"><?= $row['name'] ?> <?= $row['date'] ?></option>
                                <?php
                                }
                                ?>
                            </select>
                        </div>
                        <br>
                        <br>
                        <br>
                    </div>

                    <script type="text/javascript">
                        function getValues() {
                           var selectBox = document.getElementById("selectBox");
                           var id = selectBox.options[selectBox.selectedIndex].value;
                           var send = JSON.stringify(id);
                           var coordenadas;
                           $.ajax({
                                    url: "coord.php",
                                    type: "POST",
                                    data: {
                                        id: send
                                    },
                                    async: false,
                                    success: function(data) {
                                       coordenadas = data;
                                    }
                                });
                            var coord = coordenadas.split("||");
                            var lat = coord[0];
                            var lng = coord[1];
                            var aux = lat.split("|");
                            var aux2 = aux.toString();
                            var latitude = aux2.substring(1);
                            latitude = latitude.split(",");
                            var longitude = lng.split("|");
                            var numParam = latitude.length;
                            for(var i = 0; i < numParam; i++){
                                var x = parseFloat(latitude[i]);
                                var y = parseFloat(longitude[i]);
                                putMarkers(x, y);
                            }
                        }
                    </script>

                    <div id="map2"></div>

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


