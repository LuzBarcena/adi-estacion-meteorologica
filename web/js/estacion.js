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

}

window.setInterval (actualizar_medicion, 3000);
