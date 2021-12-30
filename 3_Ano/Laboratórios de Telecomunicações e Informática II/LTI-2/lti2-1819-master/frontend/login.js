// var BASE_URL = 'http://localhost:8080/';

$(document).ready(function(){
	jQuery.support.cors = true;
	$('#login_btn').click(function (){
			var user = $('#username_login').val();
			var pssw = $('#password_login').val();
			var token = '';
			if(user == '' || pssw == ''){
					alert("Preencha todos os dados");		
			}
			else{
					$.ajax({
							url: localStorage.getItem('base_url')+"login",
							type: 'POST',
							dataType : 'json',
							contentType: "application/json; charset=utf-8",
							crossDomain:true,
							data:JSON.stringify({"mail":user,"password":pssw}),
							success:function(data){
								console.log(data);

								if(data.data.auth == true ){
									localStorage.setItem('token',data.data.token);
									localStorage.setItem('tipo',data.data.id_tipoUtilizador);
									console.log("localStorage: "+localStorage.getItem('token'));
									window.location.href = "admin.html";
								}
								else{
									alert("Enganou-se no username e/ou password, tente novamente");
								}
							},
							error: function (xhr, ajaxOptions, thrownError) {
								console.log(JSON.stringify(xhr));
								console.log(JSON.stringify(thrownError));
								alert("Enganou-se no username e/ou password, tente novamente");
							}
					});
			}
	});
});