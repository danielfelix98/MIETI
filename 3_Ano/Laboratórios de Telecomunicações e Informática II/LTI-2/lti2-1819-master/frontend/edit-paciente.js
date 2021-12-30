$(document).ready(function () {
	jQuery.support.cors = true;
	// obter todas as areas e inserir no template
	$.ajax({
		url: localStorage.getItem("base_url") + "areas",
		type: 'GET',
		contentType: "application/json; charset=utf-8",
		dataType: "json",
		beforeSend: function (xhr) {
			xhr.setRequestHeader("Authorization", "Bearer " + localStorage.getItem('token'));
		},
		data: {},
		success: function (data) {
			appendAreaInfo(data.data);
			console.log(JSON.stringify(data.data));
		},
		error: function (xhr, ajaxOptions, thrownError) {
			console.log(xhr.status);
			console.log(thrownError);
		}
	});

	function appendAreaInfo(areas) {
		for (i = 0; i < areas.length; i++) {
			$("#area").append(
				"<option value=\"" + areas[i].id_area + "\"" + ">" + areas[i].id_area + " - " + areas[i].nome_area + "</option>");
		}
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
			appendPaciente(data.data);
			console.log(JSON.stringify(data.data));
		},
		error: function (xhr, ajaxOptions, thrownError) {
			console.log(xhr.status);
			console.log(thrownError);
		}
	});

	function appendPaciente(pac) {
		for (i = 0; i < pac.length; i++) {
			$("#select").append(
				"<option value=\"" + pac[i].id_paciente + "\"" + ">" + pac[i].id_paciente + " - " + pac[i].nome_paciente + "</option>");
		}
	}

	// carregar dados para paciente escolhido
	$('#select').change(function () {
		id = $('#select').val();
		console.log("selected: " + id);

		$.ajax({
			url: localStorage.getItem("base_url") + "pacientes/" + id,
			type: 'GET',
			contentType: "application/json; charset=utf-8",
			dataType: "json",
			beforeSend: function (xhr) {
				xhr.setRequestHeader("Authorization", "Bearer " + localStorage.getItem('token'));
			},
			data: {},
			success: function (data) {
				console.log(JSON.stringify(data.data));
				$('#nome').val(data.data[0].nome_paciente);
				$('#morada').val(data.data[0].morada);
				$('#nif').val(data.data[0].nif);
				$('#contacto').val(data.data[0].telefone);
				$('#obs_medicas').val(data.data[0].obs_medicas);
				$('#area').val(data.data[0].id_area);
			},
			error: function (xhr, ajaxOptions, thrownError) {
				console.log(xhr.status);
				console.log(thrownError);
			}
		});
	});

	$('#submit').click(function () {
		var id = $('#select').val();
		var nome = $('#nome').val();
		var morada = $('#morada').val();
		var nif = $('#nif').val();
		var contacto = $('#contacto').val();
		var obs_medicas = $('#obs_medicas').val();
		var area = $('#area').val();

		if (nome == '' || morada == '' || nif == '' || contacto == '' || obs_medicas == '' || area == '' || id == '') {
			alert("Preencha todos os dados.");
		}
		else {
			$.ajax({
				url: localStorage.getItem('base_url') + "pacientes/" + id,
				type: 'PUT',
				dataType: 'json',
				contentType: "application/json; charset=utf-8",
				crossDomain: true,
				beforeSend: function (xhr) {
					xhr.setRequestHeader("Authorization", "Bearer " + localStorage.getItem('token'));
				},
				data: JSON.stringify({ "nome_paciente": nome, "morada": morada, "nif": nif, "obs_medicas": obs_medicas, "telefone": contacto, "id_area": area }),
				success: function (data) {
					console.log(data);
					window.location.href = "admin.html";
				},
				error: function (xhr, ajaxOptions, thrownError) {
					console.log(JSON.stringify(xhr));
					console.log(JSON.stringify(thrownError));
					alert("Não foi possível editar o paciente.");
				}
			});
		}
	});

	$('#apagar').click(function (){
		var id = $('#select').val();

		$.ajax({
			url: localStorage.getItem('base_url')+"pacientes/"+id,
			type: 'DELETE',
			dataType : 'json',
			contentType: "application/json; charset=utf-8",
			crossDomain: true,
			beforeSend: function (xhr) {
				xhr.setRequestHeader("Authorization", "Bearer " + localStorage.getItem('token'));
			},
			
			success:function(data){
				console.log(data);
				// alert("Area removida.");
				window.location.href = "admin.html";
			},
			error: function (xhr, ajaxOptions, thrownError) {
				console.log(JSON.stringify(xhr));
				console.log(JSON.stringify(thrownError));
				alert("Não foi possível remover o paciente.");
			}


		});
	});
});