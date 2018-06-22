<?php

if (isset ($_GET["hora"]) && $_GET["hora"] != "") {
	$pdo = new PDO ("sqlite:db.sqlite");
	$ahora = time();
	#echo $ahora;
	$date = new DateTime();
	$date -> setTimestamp($ahora);
	#echo $date->format('U = Y-m-d H:i:s') . "\n";
	$desde = $ahora  - (intval($_GET["hora"]) * 60 * 60);
	$query =
		"SELECT temperatura, humedad, luminosidad, timestamp"
		. " FROM medicion WHERE timestamp > :desde ORDER BY timestamp";

	$stmt = $pdo-> prepare($query);
	$stmt-> execute([":desde"=>$desde]);
	$datos_enviar = $stmt-> fetchAll(PDO::FETCH_ASSOC);
	header ("Content-Type: application/json");
	echo json_encode ($datos_enviar);
}

