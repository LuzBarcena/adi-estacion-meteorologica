function actualizar_medicion () {
	$.ajax ("medicion_actual.php",
		{
			method: "GET",
			dataType: "json",
			success: on_actualizar_medicion_success
		}
	)	
}

function on_actualizar_medicion_success (data) {
	var span_temperatura = document.getElementById ("temperatura_actual");
	var span_humedad = document.getElementById ("humedad_actual");
	var bar_luminosidad = document.querySelector (".lum_bar");
	var svg_temperatura  = document.getElementById ("icono_temperatura");
	var svg_humedad = document.getElementById ("icono_humedad");
	var svg_luminosidad = document.getElementById ("icono_luminosidad");

	var temperatura = data.temperatura;
	var humedad = data.humedad;
	var luminosidad = data.luminosidad;
	var timestamp = data.timestamp;
	var lat = data.lat;
	var lng = data.lng;
	var date = new Date (parseInt (timestamp*1000));

	var time_fecha = document.getElementById ("fecha");
	var time_hora = document.getElementById ("hora");

	var fecha_formateada = date.getDate() + "/" + date.getMonth() + "/" + date.getFullYear();
	var hora_formateada = date.getHours() + ":" + date.getMinutes();

	time_fecha.textContent = fecha_formateada;
	time_hora.textContent = hora_formateada;
	

	span_temperatura.textContent = temperatura + " ºC";
	span_humedad.textContent = humedad + " %";
	bar_luminosidad.style.height = luminosidad + "%";

	var mercurio = svg_temperatura.contentDocument.querySelector ("#mercurio");
	var bulbo = svg_temperatura.contentDocument.querySelector ("#bulbo");
	var alto_mercurio = 5 +(temperatura * 0.66);
	mercurio.setAttribute ("height", alto_mercurio);
	mercurio.setAttribute ("y", 95 -alto_mercurio);
	var gradiente_agua = svg_humedad.contentDocument.querySelector("#gradiente_agua");
	var alto_agua = humedad*0.34;
	gradiente_agua.setAttribute ("y1", 105.1 - alto_agua);
	gradiente_agua.setAttribute ("y2", 105 - alto_agua);

	if (temperatura > 15) {
		bulbo.style.fill = "#ff3333";
		mercurio.style.fill = "#ff3333";
	} else {
		bulbo.style.fill="#3333ff";
		mercurio.style.fill="#3333ff";
	}

	actualizar_mapa (lat, lng);

}

function inicializar_mapa () {
	var mapa = L.map('mapa');
	GLOBAL_MAPA = mapa;
	var osmUrl='https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png';
	var osmAttrib='Map data © <a href="https://openstreetmap.org">OpenStreetMap</a> contributors';
	var osm = new L.TileLayer(osmUrl, {minZoom: 8, maxZoom: 20, attribution: osmAttrib});		
	mapa.addLayer (osm);

	GLOBAL_MARKER = null;
}

function actualizar_mapa (lat, lng) {
	if (GLOBAL_MARKER == null) {
		GLOBAL_MAPA.setView ([lat, lng], 16);
		GLOBAL_MARKER = L.marker ([lat, lng], {icon: L.icon ({
			iconUrl: "img/marker-icon.png",
			iconSize: [25, 41],
			iconAnchor: [13, 41]
		})});
		GLOBAL_MARKER.addTo (GLOBAL_MAPA);
	}
	var marker = GLOBAL_MARKER;
	var previous = marker.getLatLng ();
	if (previous.lat != lat || previous.lng != lng) {
		marker.setLatLng ([lat, lng]);
		GLOBAL_MAPA.flyTo ([lat, lng], 16);

	}
}

window.onload = function () {
	inicializar_mapa ();
	actualizar_medicion ();
	window.setInterval (actualizar_medicion, 3000);
}
