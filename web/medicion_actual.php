<?php
$pdo = new PDO ("sqlite:db.sqlite");
$query =
	"SELECT temperatura, humedad, luminosidad, timestamp, lat, lng "
	. "FROM  medicion ORDER BY timestamp DESC LIMIT 1";
$stmt = $pdo-> query ($query);
$datos_enviar = $stmt-> fetch (PDO::FETCH_ASSOC);
header ("Content-Type: application/json");
echo json_encode ($datos_enviar);
