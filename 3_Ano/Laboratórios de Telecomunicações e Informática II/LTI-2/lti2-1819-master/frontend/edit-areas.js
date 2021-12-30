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
			alert(xhr.status);
			alert(thrownError);
		}
	});

	function appendAreaInfo(areas) {
		for(i=0; i<areas.length;i++){
			$("#select").append(
				"<option value=\""+areas[i].id_area+"\"" + ">" + areas[i].id_area+" - "+areas[i].nome_area +"</option>");
		}
	}

	$('#select').change(function (){
		id = $('#select').val();
		console.log("selected: "+id);

		$.ajax({
			url: localStorage.getItem("base_url") + "areas/"+id,
			type: 'GET',
			contentType: "application/json; charset=utf-8",
			dataType: "json",
			beforeSend: function (xhr) {
				xhr.setRequestHeader("Authorization", "Bearer " + localStorage.getItem('token'));
			},
			data: {},
			success: function (data) {
				console.log(JSON.stringify(data.data));
				$("#nome_area").val(data.data[0].nome_area);
			},
			error: function (xhr, ajaxOptions, thrownError) {
				console.log(xhr.status);
				console.log(thrownError);
			}

		});
		
		
	});

	$('#submit').click(function (){
		var id = $('#select').val();
		var nome = $('#nome_area').val();
		

		if(id=='' && nome==''){
				alert("Preencha todos os dados.");
		}					
		else{
				$.ajax({
						url: localStorage.getItem('base_url')+"areas/"+id,
						type: 'PUT',
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
							alert("Não foi possível editar a área.");
						}
				});
		}

	});

	


	$('#apagar').click(function (){
		var id = $('#select').val();

		$.ajax({
			url: localStorage.getItem('base_url')+"areas/"+id,
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
				window.location.href = "all-areas.html";
			},
			error: function (xhr, ajaxOptions, thrownError) {
				console.log(JSON.stringify(xhr));
				console.log(JSON.stringify(thrownError));
				alert("Não foi possível remover a área.");
			}


		});
	});


		
});