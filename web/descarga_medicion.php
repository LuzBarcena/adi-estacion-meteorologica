<?php

if ($_GET["hora"] != "") {
	echo $_GET["hora"];
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
	$file = fopen("mediciones.csv", "w");
	$headers = array_keys($datos_enviar[0]);
	fputcsv($file, $headers);
	foreach($datos_enviar as $key=>$value){
		fputcsv($file, $value);
	}	
}
