$(document).ready(function(){
	jQuery.support.cors = true;
	
	$('#submit-button').click(function (){
			var nome = $('#nome').val();
			
			if(nome==''){
				alert("Preencha todos os dados.");
			}
			else{
					$.ajax({
							url: localStorage.getItem('base_url')+"areas",
							type: 'POST',
							dataType : 'json',
							contentType: "application/json; charset=utf-8",
							crossDomain: true,
							beforeSend: function (xhr) {
								xhr.setRequestHeader("Authorization", "Bearer " + localStorage.getItem('token'));
							},
							data: JSON.stringify({"nome_area": nome}),
							success:function(data){
								console.log(data);
								window.location.href = "all-areas.html";
							},
							error: function (xhr, ajaxOptions, thrownError) {
								console.log(JSON.stringify(xhr));
								console.log(JSON.stringify(thrownError));
								alert("Não foi possível adicionar a área.");
							}
					});
			}
	});
});