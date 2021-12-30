window.onload = function () {
	if(localStorage.getItem('tipo')!=1){
		$('#addp').hide();
		$('#editp').hide();
		$('#adda').hide();
		$('#edita').hide();
		$('#users').hide();
	}
	// obter todas os pacientes e inserir no template
	$.ajax({
		url: localStorage.getItem("base_url") + "pacientes",
		type: 'GET',
		contentType: "application/json; charset=utf-8",
		dataType: "json",
		beforeSend: function (xhr) {
			xhr.setRequestHeader("Authorization", "Bearer " + localStorage.getItem('token'));
		},
		data: {},
		success: function (data) {
			appendPacienteInfo(data.data);
			console.log(JSON.stringify(data.data));
		},
		error: function (xhr, ajaxOptions, thrownError) {
			console.log(xhr.status);
			console.log(thrownError);
		}
	});
	function appendPacienteInfo(pac) {
		for (i = 0; i < pac.length; i++) {
			$("#pacientes").append(
				"<option value=\"" + pac[i].id_paciente + "\"" + ">" + pac[i].id_paciente + " - " + pac[i].nome_paciente + "</option>");
		}
	}

	// carregar leituras para gráfico
	$('#pacientes').change(function () {
		id = $('#pacientes').val();
		console.log("selected: " + id);

		$.ajax({
			url: localStorage.getItem("base_url") + "pacientes/" + id + "/leituras",
			type: 'GET',
			contentType: "application/json; charset=utf-8",
			dataType: "json",
			beforeSend: function (xhr) {
				xhr.setRequestHeader("Authorization", "Bearer " + localStorage.getItem('token'));
			},
			data: {},
			success: function (data) {
				console.log("Leituras: " + JSON.stringify(data.data));
				// obter datas e estados para array
				var d = new Array();
				for (i = 0; i < data.data.length; i++) {
					date = new Date(data.data[i].ts);
					d.push({ x: date.toLocaleDateString() + " " + date.getHours() + ":" + date.getMinutes() + ":" + date.getSeconds(), y: data.data[i].estado_fisico });
				}
				// sucesso: carregar dados para o gráfico e criar gráfico
				var ctx = document.getElementById('canvas').getContext('2d');
				var config = {
					type: 'line',
					data: {
						yLabels: ['Queda!', 'Agitado!', 'Andamento', 'Parado', 'Desligado!'],
						datasets: [{
							label: 'Paciente ' + id,
							backgroundColor: 'rgb(2, 109, 240)',
							borderColor: 'rgb(2, 109, 240)',
							fill: false,
							data: d,
						}]
					},
					options: {
						scales: {
							xAxes: [{
								type: 'time',
								time: {
									parser: 'DD/MM/YYYY HH:mm:ss',
									// round: 'day'
									tooltipFormat: 'll HH:mm:ss'
								},
								scaleLabel: {
									display: true,
									labelString: 'Data'
								}
							}],
							yAxes: [{
								type: 'category',
								position: 'left',
								display: true,
								scaleLabel: {
									display: true,
									labelString: 'Estado físico'
								},
								ticks: {
									reverse: true
								}
							}]
						},
					}
				};

				if(window.myLine==null){
					window.myLine = new Chart(ctx, config);
				}else{
					window.myLine.data.datasets.pop();
					window.myLine.data.datasets.push({
						label: 'Paciente ' + id,
						backgroundColor: 'rgb(2, 109, 240)',
						borderColor: 'rgb(2, 109, 240)',
						fill: false,
						data: d,
					});
					window.myLine.update();
				}
			},
			error: function (xhr, ajaxOptions, thrownError) {
				console.log(xhr.status);
				console.log(thrownError);
				alert("Não existem dados..");
			}
		});
	});
};