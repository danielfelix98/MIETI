var info;
var j=0;
$(document).ready(function () {
	if(localStorage.getItem('tipo')!=1){
		$('#addp').hide();
		$('#editp').hide();
		$('#adda').hide();
		$('#edita').hide();
		$('#users').hide();
	}
	jQuery.support.cors = true;
	$.ajax({
		url: localStorage.getItem("base_url") + "info/pacientes",
		type: 'GET',
		contentType: "application/json; charset=utf-8",
		dataType: "json",
		beforeSend: function (xhr) {
			xhr.setRequestHeader("Authorization", "Bearer " + localStorage.getItem('token'));
		},
		data: {},
		success: function (data) {
			info=data.data;
			console.log(info);
			for(i=0;i<info.length;i++){
				$.ajax({
					url: localStorage.getItem("base_url") + "last/leituras/"+info[i].id_paciente,
					type: 'GET',
					contentType: "application/json; charset=utf-8",
					dataType: "json",
					beforeSend: function (xhr) {
						xhr.setRequestHeader("Authorization", "Bearer " + localStorage.getItem('token'));
					},
					data: {},
					success: function (data2) {
						console.log("Data2:"+JSON.stringify(data2.data));
						setEstado(data2);
					},
					error: function (xhr, ajaxOptions, thrownError) {
						// alert(xhr.status);
						// alert(thrownError);
					}
				});
			}

		},
		error: function (xhr, ajaxOptions, thrownError) {
			alert(xhr.status);
			alert(thrownError);
		}
	});
});

function setEstado(estado){
	// console.log("INFO: "+JSON.stringify(info)+" \nestado: "+JSON.stringify(estado));
	for(i=0;i<info.length;i++){
		if(info[i].id_paciente == estado.data[0].id_paciente){
			info[i].estado_fisico = estado.data[0].estado_fisico;
			appendPacienteInfo(i);
		}
	}
}

function appendPacienteInfo(i) {
	// console.log("APPEND INFO: "+JSON.stringify(info));
	$("#pacientes").append(
		"<div class=\"col-lg-3 col-md-6 col-sm-6 col-xs-12\">"+
			"<div class=\"hpanel hblue contact-panel contact-panel-cs responsive-mg-b-30\">"+
				"<div class=\"panel-body custom-panel-jw\">"+
					"<img alt=\"logo\" class=\"img-circle m-b\" src=\"default-user.png\">"+
						"<h3>"+info[i].nome_paciente+"</h3>"+
						"<p>Obs médicas: "+info[i].obs_medicas+"</p>"+
						"</div>"+
					"<div class=\"panel-footer contact-footer\">"+
						"<div class=\"professor-stds-int\">"+
							"<div class=\"professor-stds\">"+
								"<div class=\"contact-stat\"><span>"+
									"<p>Estado:"+
										"</span> <strong>"+info[i].estado_fisico+"</strong></div>"+
								"</div>"+
								"<span style=\"display:inline-block; width: 0.3cm;\"></span>"+
								"<div class=\"professor-stds\">"+
									"<div class=\"contact-stat\"><span>Área: </span> <strong> "+info[i].nome_area+"</strong></div>"+
								"</div>"+
								"<span style=\"display:inline-block; width: 0.3cm;\"></span>"+
								"<div class=\"professor-stds\">"+
									"<div class=\"contact-stat\"><span>ID: </span> <strong>"+info[i].id_paciente+"</strong></div>"+
								"</div>"+
							"</div>"+
						"</div>"+
					"</div>"+
				"</div>"
	)
}
