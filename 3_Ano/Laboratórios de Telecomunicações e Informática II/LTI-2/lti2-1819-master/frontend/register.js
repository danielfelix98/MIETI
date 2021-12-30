// var BASE_URL = 'http://localhost:8080/';

$(document).ready(function(){
	jQuery.support.cors = true;
	$('#register_btn').click(function (){
			var user = $('#username').val();
			var morada = $('#morada').val();
			var pass = $('#password').val();
			var mail = $('#mail').val();
			var tipo = $('#tipo_user').val();
			if(user == '' || morada == '' || pass == '' || mail == '' || tipo == ''){
				alert("Preencha todos os dados.");
				alert(""+user+" "+morada+" "+pass+" "+mail+" "+tipo);
			}
			else{
					$.ajax({
							url: localStorage.getItem('base_url')+"register",
							type: 'POST',
							dataType : 'json',
							contentType: "application/json; charset=utf-8",
							crossDomain: true,
							data: JSON.stringify({"username":user,"morada":morada,"mail":mail,"password":pass,"id_tipoUtilizador":tipo}),
							success:function(data){
								console.log(data);
								localStorage.setItem('token',data.data.token);
								console.log("localStorage: "+localStorage.getItem('token'));
								alert("Registado com sucesso.");
								// salto para próxima pagina
								if(tipo == 1){
									window.location.href = "admin.html";
								}
							},
							error: function (xhr, ajaxOptions, thrownError) {
								console.log(JSON.stringify(xhr));
								console.log(JSON.stringify(thrownError));
								alert("Não foi possível registar.");
							}
					});
			}
	});
});