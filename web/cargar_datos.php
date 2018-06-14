<?php
$temperatura = $_POST["temperatura"];
$humedad = $_POST["humedad"];
$luminosidad = $_POST["luminosidad"];
$lat = $_POST["lat"];
$lng = $_POST["lng"];
$timestamp = isset ($_POST["timestamp"])? $_POST["timestamp"]: time();

//file_put_contents ("datos.csv", "$temperatura,$humedad,$luminosidad");

$create = (!file_exists ("db.sqlite"));
$pdo = new PDO ("sqlite:db.sqlite");

if ($create) {
	$pdo-> exec ("CREATE TABLE medicion (timestamp INTEGER, temperatura REAL, humedad REAL, luminosidad REAL, lat REAL, lng REAL)");
}

$stmt = $pdo-> prepare (
	"INSERT INTO medicion (timestamp, temperatura, humedad, luminosidad, lat, lng) "
	. " VALUES (:timestamp, :temperatura, :humedad, :luminosidad, :lat, :lng)");

$stmt-> execute ([
	":timestamp" => $timestamp,
	":temperatura" => $temperatura,
	":humedad" => $humedad,
	":luminosidad" => $luminosidad,
	":lat" => $lat,
	":lng" => $lng
]);

