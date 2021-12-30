$(document).ready(function(){
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
			dataglobal=data.data;
		},
		error: function (xhr, ajaxOptions, thrownError) {
			console.log(xhr.status);
			console.log(thrownError);
		}
	});

	function appendAreaInfo(areas) {
		for(i=0; i<areas.length;i++){
			$("#area").append(
				"<option value=\""+areas[i].id_area+"\"" + ">" + areas[i].id_area+" - "+areas[i].nome_area +"</option>");
		}
	}

	$('#submit').click(function (){
			var nome = $('#nome').val();
			var morada = $('#morada').val();
			var nif = $('#nif').val();
			var contacto = $('#contacto').val();
			var obs_medicas = $('#obs_medicas').val();
			var area = $('#area').val();
			
			if(nome=='' || morada=='' || nif=='' || contacto=='' || obs_medicas=='' || area==''){
				alert("Preencha todos os dados.");
			}
			else{
					$.ajax({
							url: localStorage.getItem('base_url')+"pacientes",
							type: 'POST',
							dataType : 'json',
							contentType: "application/json; charset=utf-8",
							crossDomain: true,
							beforeSend: function (xhr) {
								xhr.setRequestHeader("Authorization", "Bearer " + localStorage.getItem('token'));
							},
							data: JSON.stringify({"nome_paciente": nome,"morada": morada,"nif": nif,"obs_medicas": obs_medicas,"telefone": contacto,"id_area": area}),
							success:function(data){
								console.log(data);
								window.location.href = "admin.html";
							},
							error: function (xhr, ajaxOptions, thrownError) {
								console.log(JSON.stringify(xhr));
								console.log(JSON.stringify(thrownError));
								alert("Não foi possível adicionar paciente.");
							}
					});
			}
	});
});