<?php
require_once 'connect.php';
function bd() {
    $conexao = mysqli_connect(MYSQL_SERVER, MYSQL_USERNAME, MYSQL_PASSWORD) or die(mysqli_error($conexao));
    mysqli_select_db($conexao, MYSQL_DATABASE) or die(mysqli_error($conexao));
    return $conexao;
}

function valida_utilizador($username, $password) {
    $ligacao = bd();
    $expressao = "SELECT * FROM users WHERE username='$username' AND password='$password'";

    $resultado = mysqli_query($ligacao, $expressao) or die(mysqli_error($ligacao));
    $valor_retorno = false;

    if (mysqli_num_rows($resultado) === 1) {
        $dados = mysqli_fetch_array($resultado);
        if ($dados['password'] == $password) {
            $valor_retorno = $dados;
        }
    }

    mysqli_free_result($resultado);
    mysqli_close($ligacao);

    return $valor_retorno;
}

function registo($frist, $last, $user, $age, $gender, $email, $pass, $mynumber, $fristsosnumber, $secondsosnumber, $thirdsosnumber, $admin) {
    $ligacao = bd();
    $dados_login = "INSERT INTO users (fristname, lastname, username, age, gender, email, password, mynumber, fristsosnumber, secondsosnumber, thirdsosnumber, admin) VALUES ('$frist', '$last', '$user', '$age', '$gender', '$email', '$pass', '$mynumber', '$fristsosnumber', '$secondsosnumber', '$thirdsosnumber', '$admin')" or die(mysqli_error($ligacao));

    mysqli_query($ligacao, $dados_login) or die(mysqli_error($ligacao));
    mysqli_close($ligacao);

    echo "<meta http-equiv='refresh' content='0; url=thanks.html'>";
}

function altera($frist, $last, $user, $age, $gender, $email, $pass, $mynumber, $fristsosnumber, $secondsosnumber, $thirdsosnumber, $admin, $id) {
    $ligacao = bd();
    $dados_login = "UPDATE users SET fristname='$frist', lastname='$last', username='$user', age='$age', gender='$gender', email='$email', password='$pass', mynumber='$mynumber', fristsosnumber='$fristsosnumber', secondsosnumber='$secondsosnumber', thirdsosnumber='$thirdsosnumber', admin='$admin' where idUser = $id" or die(mysqli_error($ligacao));
    
    mysqli_query($ligacao, $dados_login) or die(mysqli_error($ligacao));
    mysqli_close($ligacao);

    echo "<meta http-equiv='refresh' content='0; url=client.php'>";
}

function defaultRoute($name, $latitude, $longitude, $idUser, $date) {
    $ligacao = bd();  
    $dados_login = "INSERT INTO defaultRoute (name, latitude, longitude, idUser, date) VALUES ('$name','$latitude', '$longitude', '$idUser', '$date')" or die(mysqli_error($ligacao));
    
    mysqli_query($ligacao, $dados_login) or die(mysqli_error($ligacao));
    mysqli_close($ligacao);
}

function routeValues($idRoute) {
    $ligacao = bd();
    $expressao = "SELECT * FROM coordinates WHERE idRoute='$idRoute'";
    $resultado = mysqli_query($ligacao, $expressao) or die(mysqli_error($ligacao));
    
    $latitude = null;
    $longitude = null;
    
    while ($row = mysqli_fetch_array($resultado)) {
        $latitude = $latitude ."|". $row['latitude'];
        $longitude = $longitude ."|". $row['longitude'];
    }
    
    $aEnviar = $latitude ."|". $longitude;
    
    mysqli_free_result($resultado);
    mysqli_close($ligacao);
    return $aEnviar;
    

                                
                               
}

