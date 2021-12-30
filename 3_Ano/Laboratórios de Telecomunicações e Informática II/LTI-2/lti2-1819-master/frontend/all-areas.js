$(document).ready(function () {
	jQuery.support.cors = true;
	console.log("tipo: " + localStorage.getItem('tipo'));
	if (localStorage.getItem('tipo') != 1) {
		$('#addp').hide();
		$('#editp').hide();
		$('#adda').hide();
		$('#edita').hide();
		$('#users').hide();
	}
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

		},
		error: function (xhr, ajaxOptions, thrownError) {
			alert(xhr.status);
			alert(thrownError);
		}
	});
});

function appendAreaInfo(areas) {
	// console.log("APPEND INFO: "+JSON.stringify(info));
	for (i = 0; i < areas.length; i++) {
		$("#areas").append(
			"<div class= \"col-lg-3 col-md-6 col-sm-6 col-xs-12\">" +
			"<div class=\"hpanel hblue contact-panel contact-panel-cs responsive-mg-b-30\">" +
			"<div class=\"panel-body custom-panel-jw\"><img alt=\"logo\" class=\"img-circle m-b\"" +
			"src=\"location-pointer.png\">" +
			"<h3>" + areas[i].nome_area + "</h3>" +
			"</div>" +
			"<div class=\"panel-footer contact-footer\">" +
			"<div class=\"professor-stds-int\">" +
			"<div class=\"professor-stds\">" +
			"<div class=\"contact-stat\"><span>ID: </span> <strong> " + areas[i].id_area + "</strong></div>" +
			"</div>" +
			"</div>" +
			"</div>" +
			"</div>" +
			"<table id=\"pac_area" + areas[i].id_area + "\"" + "class=\"table table-striped\">" +
			"<thead>" +
			"<th>Pacientes:</th>" +
			"<tr>" +
			"<th>Nome</th>" +
			"<th>Estado físico</th>" +
			"</tr>" +
			"</thead>" +
			"<tbody id=\"area_" + areas[i].id_area + "\"" + ">" +

			"</tbody>" +
			"</table>" +
			"</div>"
		);
		// obter sujeitos da area 
		$.ajax({
			url: localStorage.getItem("base_url") + "info/pacientes/" + areas[i].id_area,
			type: 'GET',
			contentType: "application/json; charset=utf-8",
			dataType: "json",
			beforeSend: function (xhr) {
				xhr.setRequestHeader("Authorization", "Bearer " + localStorage.getItem('token'));
			},
			data: {},
			success: function (data) {
				// appendAreaInfo(data.data);
				console.log(JSON.stringify(data));
				for(i=0;i<data.data.length;i++){
					$("#area_" + data.data[i].id_area).append(
						"<tr>" +
						"<td>" +
						"<span>" + data.data[i].nome_paciente + "</span>" +
						"</td>" +
						"<td>" + data.data[i].estado_fisico + "</td>" +
						"</tr>"
					);
				}
			},
			error: function (xhr, ajaxOptions, thrownError) {
				alert(xhr.status);
				alert(thrownError);
			}
		});
	}
}
