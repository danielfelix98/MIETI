$(document).ready(function () {
	jQuery.support.cors = true;
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
			alert(xhr.status);
			alert(thrownError);
		}
	});
});



function appendUsersInfo(users) {
	// console.log("APPEND INFO: "+JSON.stringify(info));
	for(i=0; i<users.length;i++){
		tipo = users[i].id_tipoUtilizador==1?"Admin":"Funcionário";
		$("#users").append(
			"<div class=\"col-lg-3 col-md-6 col-sm-6 col-xs-12\">"+
						"<div class=\"hpanel hblue contact-panel contact-panel-cs responsive-mg-b-30\">"+
							"<div class=\"panel-body custom-panel-jw\">"+
								"<img alt=\"logo\" class=\"img-circle m-b\" src=\"default-user.png\">"+
								"<h3><a href=\"edit-admin.html\">"+
									users[i].username+
									"</a></h3>"+
							"</div>"+
							"<div class=\"panel-footer contact-footer\">"+
								"<div class=\"professor-stds-int\">"+
									"<div class=\"professor-stds\">"+
										"<div class=\"contact-stat\"><span>ID: </span> <strong>"+
											users[i].id_utilizador+
											"</strong></div>"+
											"<div class=\"contact-stat\"><span>Mail: </span> <strong> "+
												users[i].mail+
												"</strong></div>"+
												"<div class=\"contact-stat\"><span>Tipo de utilizador: </span> <strong> "+
												tipo+
												"</strong></div>"+
									"</div>"+
								"</div>"+
							"</div>"+
						"</div>"+
					"</div>"
		);
	}
}
