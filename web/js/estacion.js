var datos;
var lineChart;

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

	var mes = date.getMonth() + 1;
	var fecha_formateada = date.getDate() + "/" + mes + "/" + date.getFullYear();
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


function get_mediciones(hora) {
	$.ajax ("xh_anteriores.php",
		{
			method: "GET",
			dataType: "json",
			data: {
					"hora": hora
				},
			success: actualizar_data
		}
	)	
}


function actualizar_grafico() {
	$.ajax ("medicion_actual.php",
		{
			method: "GET",
			dataType: "json",
			success: on_actualizar_grafico_success
		}
	)	
}


function on_actualizar_grafico_success(data) {
	datos.shift(1);
	datos.push(data)
	actualizar_data(datos);
}


function actualizar_data(data) {
	datos = data;
	lineChart.data = getData(data);
	lineChart.update();
}


function getChartOptions() {
	var options = {
        responsive: true,
        stacked: false,
        title: {
            display: true,
            text: 'Humedad vs Temperatura vs Luminosidad'
        },
        tooltips: {
            mode: 'index',
            intersect: false,
        },
        scales: {
			yAxes: [{
				type: 'linear',
				display: true,
				position: 'left',
				id: 'temperatura',
				ticks: {
	                suggestedMin: -10,
	                suggestedMax: 50
	            },
			}, {
				type: 'linear',
				display: true,
				position: 'left',
				id: 'humedad',
				ticks: {
	                suggestedMin: 0,
	                suggestedMax: 100
	            },
			}, {
				type: 'linear',
				display: true,
				position: 'right',
				id: 'luminosidad',
				ticks: {
	                suggestedMin: 0,
	                suggestedMax: 100
	            },
			}],
		}
    };
    return options;
}

function getData(datos) {
	var data = {
        labels: datos.map(function(item){
            //return new Date(parseInt (item.timestamp*1000)).getHours();
            var fecha_completa = new Date(parseInt (item.timestamp*1000));
            var anio = fecha_completa.getFullYear();
            var mes = fecha_completa.getMonth() + 1;
            var dia = fecha_completa.getDate();
            var hora = fecha_completa.getHours();
            var minutos = fecha_completa.getMinutes();
            return (dia+'/'+mes+'/'+anio+' '+hora+':'+minutos)
        }), 
        datasets: [{
            label: 'Temperatura',
            backgroundColor: 'rgba(255,2,0,0.7)',
            borderColor: 'rgba(255,2,0,0.7)',
            data: datos.map(function(item){
                return item["temperatura"];
            }),
            fill: false,
            pointRadius: 0,
            yAxisID: 'temperatura',
        }, {
            label: 'Humedad',
            fill: false,
            pointRadius: 0,
            backgroundColor: 'rgba(0,0,255,0.7)',
            borderColor: 'rgba(0,0,255,0.7)',
            data: datos.map(function(item){
                return item["humedad"];
            }),
            yAxisID: 'humedad',
        }, {
            label: 'Luminosidad',
            fill: false,
            pointRadius: 0,
            backgroundColor: 'rgba(0,0,0,0.7)',
            borderColor: 'rgba(0,0,0,0.7)',
            data: datos.map(function(item){
                return item["luminosidad"];
            }),
            yAxisID: 'luminosidad',
        }]
    };

    return data;
}


function agregar_evento_select_grafico() {
	var select_grafico = document.getElementById("select_hora_grafico");
	select_grafico.addEventListener("change", function() {
		switch (select_grafico.value) {
			case "24hs":
				get_mediciones(24); 
				break;
			case "12hs":
				get_mediciones(12); 
				break;
			case "1hs":
				get_mediciones(1); 
				break;
			default:

		}
	});
}

function descargar_mediciones(hora) {
	$.ajax ("descarga_medicion.php",
		{
			method: "GET",
			dataType: "json",
			data: {
					"hora": hora
				},
			success: descarga_succeed
		}
	)	
}

function descarga_succeed(data) {
	console.log("descarga success");
}

function agregar_evento_select_descarga() {
	var select_descarga = document.getElementById("select_hora_descarga");
	select_descarga.addEventListener("change", function() {
		switch (select_descarga.value) {
			case "24hs":
				descargar_mediciones(24); 
				break;
			case "12hs":
				descargar_mediciones(12); 
				break;
			case "1hs":
				descargar_mediciones(1); 
				break;
			default:

		}
	});
}

function agregar_evento_btn_descarga() {
	var btn_descarga = document.getElementById("btn_descargar");
	btn_descarga.addEventListener("click", function() {	
		console.log("hice click en el boton");
		var select_descarga = document.getElementById("select_hora_descarga");
		console.log(select_descarga.value);
		$.ajax ("descarga_medicion.php",
			{
				method: "GET",
				dataType: "json",
				data: {
						"hora": select_descarga.value
					},
				success: descarga_succeed
			}
		)
	});
}

window.onload = function () {
	//inicializo el select con materialize
	var elems = document.querySelectorAll('select');
	var instances = M.FormSelect.init(elems);
	//event de select para grafico
	agregar_evento_select_grafico();
	agregar_evento_btn_descarga();

	inicializar_mapa ();
	actualizar_medicion ();
	var ctx = document.getElementById('grafico').getContext('2d');	
	lineChart = new Chart(ctx, {
		type: 'line',
		options: getChartOptions()
	});
	// por defecto se muestran 24 horas anteriores
	get_mediciones(24);
	
	// Las mediciones se envían cada 60 segundos 
	// entonces se actualiza cada ese lapso de tiempo
	window.setInterval (actualizar_medicion, 60000); 
	window.setInterval (actualizar_grafico, 60000); 
}
