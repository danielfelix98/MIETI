$(document).ready(function () {
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

	// obter todos users e inserir no template
	$.ajax({
		url: localStorage.getItem("base_url") + "utilizadores",
		type: 'GET',
		contentType: "application/json; charset=utf-8",
		dataType: "json",
		beforeSend: function (xhr) {
			xhr.setRequestHeader("Authorization", "Bearer " + localStorage.getItem('token'));
		},
		data: {},
		success: function (data) {
			appendUsersInfo(data.data);
		},
		error: function (xhr, ajaxOptions, thrownError) {
			console.log(xhr.status);
			console.log(thrownError);
		}
	});

	function appendUsersInfo(users) {
		for (i = 0; i < users.length; i++) {
			$("#users").append(
				"<option value=" +
				users[i].id_utilizador + ">" + users[i].id_utilizador + " - " + users[i].username +
				"</option>"
			);
		}
	}

	function appendUserTypesInfo(userTypes) {
		for (i = 0; i < userTypes.length; i++) {
			$("#userTypes").append(
				"<option value=" +
				userTypes[i].id_tipoUtilizador + ">" + userTypes[i].id_tipoUtilizador + " - " + userTypes[i].tipo +
				"</option>"
			);
		}
	}

	// carregar dados para user escolhido
	$('#users').change(function(){
		id = $('#users').val();
		console.log("selected: "+id);

		$.ajax({
			url: localStorage.getItem("base_url") + "utilizadores/"+id,
			type: 'GET',
			contentType: "application/json; charset=utf-8",
			dataType: "json",
			beforeSend: function (xhr) {
				xhr.setRequestHeader("Authorization", "Bearer " + localStorage.getItem('token'));
			},
			data: {},
			success: function (data) {
				console.log(JSON.stringify(data.data));
				$('#username').val(data.data[0].username);
				$('#morada').val(data.data[0].morada);
				$('#mail').val(data.data[0].mail);
				$('#userTypes').val(data.data[0].id_tipoUtilizador);
			},
			error: function (xhr, ajaxOptions, thrownError) {
				console.log(xhr.status);
				console.log(thrownError);
			}
		});
	});

	$('#submit').click(function () {
		var id = $("#users").val();
		var username = $('#username').val();
		var password = $('#password').val();
		var morada = $('#morada').val();
		var mail = $('#mail').val();
		var userTypes = $('#userTypes').val();

		if (id=='' || username == '' || morada == '' || mail == '' || userTypes == '' || password == "") {
			alert("Preencha todos os dados.");
		}
		else {
			$.ajax({
				url: localStorage.getItem('base_url') + "utilizadores/"+id,
				type: 'PUT',
				dataType: 'json',
				contentType: "application/json; charset=utf-8",
				crossDomain: true,
				beforeSend: function (xhr) {
					xhr.setRequestHeader("Authorization", "Bearer " + localStorage.getItem('token'));
				},
				data: JSON.stringify({ "username": username, "password": password, "morada": morada, "mail": mail, "id_tipoUtilizador": userTypes }),
				success: function (data) {
					console.log(data);
					window.location.href = "all-users.html";
				},
				error: function (xhr, ajaxOptions, thrownError) {
					console.log(JSON.stringify(xhr));
					console.log(JSON.stringify(thrownError));
					alert("Não foi possível editar o utilizador.");
				}
			});
		}
	});

	$('#apagar').click(function (){
		var id = $('#users').val();

		$.ajax({
			url: localStorage.getItem('base_url')+"utilizadores/"+id,
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
				window.location.href = "all-users.html";
			},
			error: function (xhr, ajaxOptions, thrownError) {
				console.log(JSON.stringify(xhr));
				console.log(JSON.stringify(thrownError));
				alert("Não foi possível remover o utilizador.");
			}


		});
	});
});