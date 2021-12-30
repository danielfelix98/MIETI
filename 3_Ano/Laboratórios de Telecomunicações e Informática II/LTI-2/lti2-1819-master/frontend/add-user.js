$(document).ready(function(){
	jQuery.support.cors = true;
	// obter todos tipos de user e inserir no template
	$.ajax({
		url: localStorage.getItem("base_url") + "tiposUtilizador",
		type: 'GET',
		contentType: "application/json; charset=utf-8",
		dataType: "json",
		beforeSend: function (xhr) {
			xhr.setRequestHeader("Authorization", "Bearer " + localStorage.getItem('token'));
		},
		data: {},
		success: function (data) {
			appendUserTypesInfo(data.data);
		},
		error: function (xhr, ajaxOptions, thrownError) {
			console.log(xhr.status);
			console.log(thrownError);
		}
	});

	function appendUserTypesInfo(userTypes) {
		for(i=0; i<userTypes.length;i++){
			$("#userTypes").append(
				"<option value="+
				userTypes[i].id_tipoUtilizador+">"+userTypes[i].id_tipoUtilizador+" - "+userTypes[i].tipo+
				"</option>"
			);
		}
	}

	$('#submit').click(function (){
			var username = $('#username').val();
			var password = $('#password').val();
			var morada = $('#morada').val();
			var mail = $('#mail').val();
			var userTypes = $('#userTypes').val();
			
			if(username=='' || morada=='' || mail=='' || userTypes=='' || password==""){
				alert("Preencha todos os dados.");
			}
			else{
					$.ajax({
							url: localStorage.getItem('base_url')+"register",
							type: 'POST',
							dataType : 'json',
							contentType: "application/json; charset=utf-8",
							crossDomain: true,
							beforeSend: function (xhr) {
								xhr.setRequestHeader("Authorization", "Bearer " + localStorage.getItem('token'));
							},
							data: JSON.stringify({"username": username, "password":password,"morada": morada,"mail": mail,"id_tipoUtilizador": userTypes}),
							success:function(data){
								console.log(data);
								window.location.href = "all-users.html";
							},
							error: function (xhr, ajaxOptions, thrownError) {
								console.log(JSON.stringify(xhr));
								console.log(JSON.stringify(thrownError));
								alert("Não foi possível adicionar o utilizador.");
							}
					});
			}
	});
});