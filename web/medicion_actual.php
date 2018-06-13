<?php

$temp = rand(-10, 50) + rand(0, 9) / 10;
$hum = rand(0, 100);
$lum = rand(0, 100);

$datos_enviar = [
	"temperatura" => $temp,
	"humedad" => $hum,
	"luminosidad" => $lum 
];

header ("Content-Type: application/json");
echo json_encode ($datos_enviar);
