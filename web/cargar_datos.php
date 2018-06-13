<?php
$temperatura = $_POST["temperatura"];
$humedad = $_POST["humedad"];
$luminosidad = $_POST["luminosidad"];
$timestamp = isset ($_POST["timestamp"])? $_POST["timestamp"]: time();

//file_put_contents ("datos.csv", "$temperatura,$humedad,$luminosidad");

$create = (!file_exists ("db.sqlite"));
$pdo = new PDO ("sqlite:db.sqlite");

if ($create) {
	$pdo-> exec ("CREATE TABLE medicion (timestamp INTEGER, temperatura REAL, humedad REAL, luminosidad REAL)");
}

$pdo-> exec (
	"INSERT INTO medicion (timestamp, temperatura, humedad, luminosidad) "
	. " VALUES ($timestamp, $temperatura, $humedad, $luminosidad)"
);

