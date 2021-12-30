const express = require('express');
const app = express();
const bodyParser = require('body-parser');
const status = require('http-status');
var dataHandler = require("./dataHandler");
const jwt = require('jsonwebtoken');
var cors = require('cors');

//cors middleware
var allowCrossDomain = function (req, res, next) {
	res.header('Access-Control-Allow-Origin', '*');
	res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
	res.header('Access-Control-Allow-Headers', 'Content-Type');
	next();
}

app.use(allowCrossDomain);
app.use(cors({ credentials: true, origin: true }));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({
	extended: true
}));

app.listen(8080);
console.log('Server listening on port 8080');

// 
// LOGIN, REGISTER e UTILIZADORES
// 
//route: register user
app.post('/register', function (req, res) {
	dataHandler.register(req, function (error, results) {
		if (error) {
			res.status(error.code).send(error.message);
		}
		else {
			return res.status(status.CREATED).send({ error: false, data: results, message: 'New User has been registered successfully' });
		}
	});
});
//route: login user
app.post('/login', function (req, res) {
	dataHandler.login(req, function (error, results) {
		if (error) {
			res.status(error.code).send(error.message);
		}
		else {
			return res.status(status.OK).send({ error: false, data: results, message: 'User logged in successfully' });
		}
	});
});
// route: get all utilizadores
app.get('/utilizadores', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.getUtilizadores(function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					res.status(status.OK).send({ error: false, data: results, message: 'Utilizadores.' });
				}
			});
	// 	}
	// });
});
// route: get one utilizador
app.get('/utilizadores/:id_utilizador', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.getUtilizadoresById(req, function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					return res.status(status.OK).send({ error: false, data: results, message: 'Utilizador.' });
				}
			});
	// 	}
	// });
});
// route: update utilizador
app.put('/utilizadores/:id_utilizador', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.updateUtilizador(req, function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					return res.status(status.CREATED).send({ error: false, data: results, message: 'New utilizador has been modified successfully.' });
				}
			});
	// 	}
	// });
});
// route: delete utilizador
app.delete('/utilizadores/:id_utilizador', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.deleteUtilizador(req, function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					return res.status(status.CREATED).send({ error: false, data: results, message: 'Utilizador deleted successfully' });
				}
			});
	// 	}
	// });
});

// 
// AREAS
// 
// route: get all areas
app.get('/areas', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.getAreas(function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					res.status(status.OK).send({ error: false, data: results, message: 'Areas.' });
				}
			});
	// 	}
	// });
});
// route: get one area
app.get('/areas/:id_area', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.getAreaById(req, function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					return res.status(status.OK).send({ error: false, data: results, message: 'Area.' });
				}
			});
	// 	}
	// });
});
// route: post area
app.post('/areas', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.insertArea(req, function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					return res.status(status.CREATED).send({ error: false, data: results, message: 'New area has been created successfully.' });
				}
			});
	// 	}
	// });
});
// route: update area
app.put('/areas/:id_area', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.updateArea(req, function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					return res.status(status.CREATED).send({ error: false, data: results, message: 'New area has been modified successfully.' });
				}
			});
	// 	}
	// });
});
// route: delete area
app.delete('/areas/:id_area', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.deleteArea(req, function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					return res.status(status.CREATED).send({ error: false, data: results, message: 'Area deleted successfully' });
				}
			});
	// 	}
	// });
});

// 
// TIPOS DE UTILIZADOR
// 
// route: get all tiposUtilizador
app.get('/tiposUtilizador', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.getTiposUtilizador(function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					res.status(status.OK).send({ error: false, data: results, message: 'TiposUtilizador.' });
				}
			});
	// 	}
	// });
});
// route: get one tipoUtilizador
app.get('/tiposUtilizador/:id_tipoUtilizador', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.getTiposUtilizadorById(req, function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					return res.status(status.OK).send({ error: false, data: results, message: 'TipoUtilizador.' });
				}
			});
	// 	}
	// });
});
// route: post tipoUtilizador
app.post('/tiposUtilizador', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.insertTiposUtilizador(req, function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					return res.status(status.CREATED).send({ error: false, data: results, message: 'New tipoUtilizador has been created successfully.' });
				}
			});
	// 	}
	// });
});
// route: update tipoUtilizador
app.put('/tiposUtilizador/:id_tipoUtilizador', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.updateTiposUtilizador(req, function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					return res.status(status.CREATED).send({ error: false, data: results, message: 'New tipoUtilizador has been modified successfully.' });
				}
			});
	// 	}
	// });
});
// route: delete tipoUtilizador
app.delete('/tiposUtilizador/:id_tipoUtilizador', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.deleteTiposUtilizador(req, function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					return res.status(status.CREATED).send({ error: false, data: results, message: 'TipoUtilizador deleted successfully' });
				}
			});
	// 	}
	// });
});

// 
// PACIENTES
// 
// route: get all pacientes
app.get('/pacientes', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.getPacientes(function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					res.status(status.OK).send({ error: false, data: results, message: 'Pacientes.' });
				}
			});
	// 	}
	// });
});
// route: get one paciente
app.get('/pacientes/:id_paciente', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.getPacienteById(req, function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					return res.status(status.OK).send({ error: false, data: results, message: 'Paciente.' });
				}
			});
	// 	}
	// });
});
// route: post paciente
app.post('/pacientes', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.insertPaciente(req, function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					return res.status(status.CREATED).send({ error: false, data: results, message: 'New paciente has been created successfully.' });
				}
			});
	// 	}
	// });
});
// route: update paciente
app.put('/pacientes/:id_paciente', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.updatePaciente(req, function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					return res.status(status.CREATED).send({ error: false, data: results, message: 'New paciente has been modified successfully.' });
				}
			});
	// 	}
	// });
});
// route: delete paciente
app.delete('/pacientes/:id_paciente', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.deletePaciente(req, function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					return res.status(status.CREATED).send({ error: false, data: results, message: 'Paciente deleted successfully' });
				}
			});
	// 	}
	// });
});
// route: get one paciente info
app.get('/info/pacientes', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.getInfoPacientes(function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					res.status(status.OK).send({ error: false, data: results, message: 'Pacientes.' });
				}
			});
	// 	}
	// });
});
// route: get paciente info in an area
app.get('/info/pacientes/:id_area', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.getPacienteInfoByArea(req, function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					res.status(status.OK).send({ error: false, data: results, message: 'Pacientes.' });
				}
			});
	// 	}
	// });
});

// 
// LEITURAS
// 
// route: get all leituras
app.get('/leituras', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.getLeituras(function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					res.status(status.OK).send({ error: false, data: results, message: 'Leituras.' });
				}
			});
	// 	}
	// });
});
// route: get one leitura
app.get('/leituras/:id_leitura', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.getLeituraById(req, function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					return res.status(status.OK).send({ error: false, data: results, message: 'Leituras.' });
				}
			});
	// 	}
	// });
});
// route: post leitura
app.post('/leituras', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.insertLeitura(req, function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					return res.status(status.CREATED).send({ error: false, data: results, message: 'New leitura has been created successfully.' });
				}
			});
	// 	}
	// });
});
// route: update leitura
app.put('/leituras/:id_leitura', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.updateLeitura(req, function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					return res.status(status.CREATED).send({ error: false, data: results, message: 'New leitura has been modified successfully.' });
				}
			});
	// 	}
	// });
});
// route: delete leitura
app.delete('/leituras/:id_leitura', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.deleteLeitura(req, function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					return res.status(status.CREATED).send({ error: false, data: results, message: 'Leitura deleted successfully' });
				}
			});
	// 	}
	// });
});
// route: get last leitura of id_paciente
app.get('/last/leituras/:id_paciente', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.getLastLeituraByIdPaciente(req, function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					return res.status(status.OK).send({ error: false, data: results, message: 'Last Leitura of id_paciente.' });
				}
			});
	// 	}
	// });
});
// route: get all leituras of id_paciente
app.get('/pacientes/:id_paciente/leituras', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.getLeiturasByPaciente(req, function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					return res.status(status.OK).send({ error: false, data: results, message: 'Leituras of id_paciente.' });
				}
			});
	// 	}
	// });
});

// 
// CONCENTRADOR
// 
// route: get all concentradores
app.get('/concentradores', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.getConcentradores(function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					res.status(status.OK).send({ error: false, data: results, message: 'Concentradores.' });
				}
			});
	// 	}
	// });
});
// route: get one concentrador
app.get('/concentradores/:id_concentrador', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.getConcentradorById(req, function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					return res.status(status.OK).send({ error: false, data: results, message: 'Concentrador.' });
				}
			});
	// 	}
	// });
});
// route: post concentrador
app.post('/concentradores', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.insertConcentrador(req, function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					return res.status(status.CREATED).send({ error: false, data: results, message: 'New concentrador has been created successfully.' });
				}
			});
	// 	}
	// });
});
// route: update concentrador
app.put('/concentradores/:id_concentrador', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.updateConcentrador(req, function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					return res.status(status.CREATED).send({ error: false, data: results, message: 'New concentrador has been modified successfully.' });
				}
			});
	// 	}
	// });
});
// route: delete concentrador
app.delete('/concentradores/:id_concentrador', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.deleteConcentrador(req, function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					return res.status(status.CREATED).send({ error: false, data: results, message: 'Concentrador deleted successfully' });
				}
			});
	// 	}
	// });
});

// 
// SISTEMA SENSOR
// 
// route: get all sistemasSensor
app.get('/sistemasSensor', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.getSistemaSensor(function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					res.status(status.OK).send({ error: false, data: results, message: 'SistemasSensor.' });
				}
			});
	// 	}
	// });
});
// route: get one sistemaSensor
app.get('/sistemasSensor/:id_sistemaSensor', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.getSistemaSensorById(req, function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					return res.status(status.OK).send({ error: false, data: results, message: 'SistemaSensor.' });
				}
			});
	// 	}
	// });
});
// route: post sistemaSensor
app.post('/sistemasSensor', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.insertSistemaSensor(req, function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					return res.status(status.CREATED).send({ error: false, data: results, message: 'New sistemaSensor has been created successfully.' });
				}
			});
	// 	}
	// });
});
// route: update sistemaSensor
app.put('/sistemasSensor/:id_sistemaSensor', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.updateSistemaSensor(req, function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					return res.status(status.CREATED).send({ error: false, data: results, message: 'New sistemaSensor has been modified successfully.' });
				}
			});
	// 	}
	// });
});
// route: delete sistemaSensor
app.delete('/sistemasSensor/:id_sistemaSensor', verifyToken, function (req, res) {
	// jwt.verify(req.token, "config.secret", (err, authData) => {
	// 	if (err) {
	// 		res.status(status.UNAUTHORIZED).send("Wrong token");
	// 	} else {
			dataHandler.deleteSistemaSensor(req, function (error, results) {
				if (error) {
					res.status(error.code).send(error.message);
				}
				else {
					return res.status(status.CREATED).send({ error: false, data: results, message: 'SistemaSensor deleted successfully' });
				}
			});
	// 	}
	// });
});

// FORMAT OF TOKEN
// Authorization: Bearer <access_token>

// Verify Token
function verifyToken(req, res, next) {
	// Get auth header value
	// const bearerHeader = req.headers['authorization'];
	// // Check if bearer is undefined
	// if (typeof bearerHeader !== 'undefined') {
	// 	// Split at the space
	// 	const bearer = bearerHeader.split(' ');
	// 	// Get token from array
	// 	const bearerToken = bearer[1];
	// 	// Set the token
	// 	req.token = bearerToken;
	// 	// Next middleware
		next();
	// } else {
	// 	// Forbidden
	// 	res.status(status.UNAUTHORIZED).send("No authorization");
	// }
}