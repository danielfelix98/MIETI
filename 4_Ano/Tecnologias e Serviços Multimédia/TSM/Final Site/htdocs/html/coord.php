<?php
$id = json_decode($_POST['id'], true);
$idRoute = (int) $id; 

require_once 'function.php';
$dados = routeValues($idRoute);


echo $dados;

