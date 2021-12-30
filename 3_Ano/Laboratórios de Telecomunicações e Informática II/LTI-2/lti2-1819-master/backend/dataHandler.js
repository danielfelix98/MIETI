const mysql = require('mysql');
const jwt = require('jsonwebtoken');
const bcrypt = require('bcryptjs');
const status = require('http-status');

var pool = mysql.createPool({
	connectionLimit: 10,
	host: 'localhost',
	user: 'root',
	database: 'servicoCentral'
});

module.exports = {
	// 
	// AREAS
	// 
	getAreas: function (callback) {
		pool.query('SELECT * FROM area', function (error, results) {
			if (error) {
				let err = { code: status.INTERNAL_SERVER_ERROR, message: error };
				return callback(err, null);
			}
			else {
				return callback(null, results);
			}
		});
	},
	getAreaById: function (req, callback) {
		let query = "SELECT * FROM area WHERE id_area = ?";
		let table = [req.params.id_area];
		query = mysql.format(query, table);
		pool.query(query, function (error, results) {
			if (error) {
				err = { code: status.INTERNAL_SERVER_ERROR, message: error };
				return callback(err, null);
			}
			else {
				if (results.length > 0)
					return callback(null, results);
				else {
					let err = { code: status.NOT_FOUND, message: "Area doesn't exist" };
					return callback(err, null);
				}
			}
		});
	},
	insertArea: function (req, callback) {
		if (!req.body.nome_area) {
			let err = { code: status.BAD_REQUEST, message: "Please provide Area" };
			return callback(err, null);
		} else {
			let query = "call inserir_area(?)";
			let table = [req.body.nome_area];
			query = mysql.format(query, table);
			pool.query(query, function (errorInsert, resultsInsert) {
				if (errorInsert) {
					err = { code: status.INTERNAL_SERVER_ERROR, message: errorInsert };
					return callback(err, null);
				}
				else {
					return callback(null, resultsInsert);
				}
			});
		}
	},
	updateArea: function (req, callback) {
		if (!req.body.nome_area) {
			let err = { code: status.BAD_REQUEST, message: "Please provide Area" };
			return callback(err, null);
		} else {
			let query = "UPDATE area SET nome_area = ? WHERE id_area = ?";
			let table = [req.body.nome_area, req.params.id_area];
			query = mysql.format(query, table);
			pool.query(query, function (error, results) {
				if (error) {
					err = { code: status.INTERNAL_SERVER_ERROR, message: error };
					return callback(err, null);
				}
				else {
					if (results.affectedRows > 0)
						return callback(null, results);
					else {
						err = { code: status.NOT_FOUND, message: "Area doesn't exist" };
						return callback(err, null);
					}
				}
			});
		}
	},
	deleteArea: function (req, callback) {
		let query = "DELETE from area WHERE id_area = ?";
		let table = [req.params.id_area];
		query = mysql.format(query, table);
		pool.query(query, function (error, results) {
			if (error) {
				err = { code: status.INTERNAL_SERVER_ERROR, message: error };
				return callback(err, null);
			}
			else {
				if (results.affectedRows > 0)
					return callback(null, results);
				else {
					err = { code: status.NOT_FOUND, message: "Area doesn't exist" };
					return callback(err, null);
				}
			}
		});
	},

	//
	// TIPOS DE UTILIZADORES
	// 
	getTiposUtilizador: function (callback) {
		pool.query('SELECT * FROM tipoUtilizador', function (error, results) {
			if (error) {
				let err = { code: status.INTERNAL_SERVER_ERROR, message: error };
				return callback(err, null);
			}
			else {
				return callback(null, results);
			}
		});
	},
	getTiposUtilizadorById: function (req, callback) {
		let query = "SELECT * FROM tipoUtilizador WHERE id_tipoUtilizador = ?";
		let table = [req.params.id_tipoUtilizador];
		query = mysql.format(query, table);
		pool.query(query, function (error, results) {
			if (error) {
				err = { code: status.INTERNAL_SERVER_ERROR, message: error };
				return callback(err, null);
			}
			else {
				if (results.length > 0)
					return callback(null, results);
				else {
					let err = { code: status.NOT_FOUND, message: "TipoUtilizador doesn't exist" };
					return callback(err, null);
				}
			}
		});
	},
	insertTiposUtilizador: function (req, callback) {
		if (!req.body.tipo) {
			let err = { code: status.BAD_REQUEST, message: "Please provide tipoUtilizador" };
			return callback(err, null);
		} else {
			let query = "call inserir_tipoUtilizador(?)";
			let table = [req.body.tipo];
			query = mysql.format(query, table);
			pool.query(query, function (errorInsert, resultsInsert) {
				if (errorInsert) {
					err = { code: status.INTERNAL_SERVER_ERROR, message: errorInsert };
					return callback(err, null);
				}
				else {
					return callback(null, resultsInsert);
				}
			});
		}
	},
	updateTiposUtilizador: function (req, callback) {
		if (!req.body.tipo) {
			let err = { code: status.BAD_REQUEST, message: "Please provide tipoUtilizador" };
			return callback(err, null);
		} else {
			let query = "UPDATE tipoUtilizador SET tipo = ? WHERE id_tipoUtilizador = ?";
			let table = [req.body.tipo, req.params.id_tipoUtilizador];
			query = mysql.format(query, table);
			pool.query(query, function (error, results) {
				if (error) {
					err = { code: status.INTERNAL_SERVER_ERROR, message: error };
					return callback(err, null);
				}
				else {
					if (results.affectedRows > 0)
						return callback(null, results);
					else {
						err = { code: status.NOT_FOUND, message: "TipoUtilizador doesn't exist" };
						return callback(err, null);
					}
				}
			});
		}
	},
	deleteTiposUtilizador: function (req, callback) {
		let query = "DELETE from tipoUtilizador WHERE id_tipoUtilizador = ?";
		let table = [req.params.id_tipoUtilizador];
		query = mysql.format(query, table);
		pool.query(query, function (error, results) {
			if (error) {
				err = { code: status.INTERNAL_SERVER_ERROR, message: error };
				return callback(err, null);
			}
			else {
				if (results.affectedRows > 0)
					return callback(null, results);
				else {
					err = { code: status.NOT_FOUND, message: "TipoUtilizador doesn't exist" };
					return callback(err, null);
				}
			}
		});
	},

	// 
	// PACIENTES
	// 
	getPacientes: function (callback) {
		pool.query('SELECT * FROM paciente', function (error, results) {
			if (error) {
				let err = { code: status.INTERNAL_SERVER_ERROR, message: error };
				return callback(err, null);
			}
			else {
				return callback(null, results);
			}
		});
	},
	getPacienteById: function (req, callback) {
		let query = "SELECT * FROM paciente WHERE id_paciente = ?";
		let table = [req.params.id_paciente];
		query = mysql.format(query, table);
		pool.query(query, function (error, results) {
			if (error) {
				err = { code: status.INTERNAL_SERVER_ERROR, message: error };
				return callback(err, null);
			}
			else {
				if (results.length > 0)
					return callback(null, results);
				else {
					let err = { code: status.NOT_FOUND, message: "Paciente doesn't exist" };
					return callback(err, null);
				}
			}
		});
	},
	insertPaciente: function (req, callback) {
		if (!req.body.nome_paciente || !req.body.morada || !req.body.nif || !req.body.obs_medicas || !req.body.telefone || !req.body.id_area) {
			let err = { code: status.BAD_REQUEST, message: "Please provide paciente" };
			return callback(err, null);
		} else {
			let query = "call inserir_paciente(?,?,?,?,?,?)";
			let table = [req.body.nome_paciente, req.body.morada, req.body.nif, req.body.obs_medicas, req.body.telefone, req.body.id_area];
			query = mysql.format(query, table);
			pool.query(query, function (errorInsert, resultsInsert) {
				if (errorInsert) {
					err = { code: status.INTERNAL_SERVER_ERROR, message: errorInsert };
					return callback(err, null);
				}
				else {
					return callback(null, resultsInsert);
				}
			});
		}
	},
	updatePaciente: function (req, callback) {
		if (!req.body.nome_paciente || !req.body.morada || !req.body.nif || !req.body.obs_medicas || !req.body.telefone || !req.body.id_area) {
			let err = { code: status.BAD_REQUEST, message: "Please provide paciente" };
			return callback(err, null);
		} else {
			let query = "UPDATE paciente SET nome_paciente=?,morada=?,nif=?,obs_medicas=?,telefone=?,id_area=? WHERE id_paciente = ?";
			let table = [req.body.nome_paciente, req.body.morada, req.body.nif, req.body.obs_medicas, req.body.telefone, req.body.id_area, req.params.id_paciente];
			query = mysql.format(query, table);
			pool.query(query, function (error, results) {
				if (error) {
					err = { code: status.INTERNAL_SERVER_ERROR, message: error };
					return callback(err, null);
				}
				else {
					if (results.affectedRows > 0)
						return callback(null, results);
					else {
						err = { code: status.NOT_FOUND, message: "Paciente doesn't exist" };
						return callback(err, null);
					}
				}
			});
		}
	},
	deletePaciente: function (req, callback) {
		let query = "DELETE from paciente WHERE id_paciente = ?";
		let table = [req.params.id_paciente];
		query = mysql.format(query, table);
		pool.query(query, function (error, results) {
			if (error) {
				err = { code: status.INTERNAL_SERVER_ERROR, message: error };
				return callback(err, null);
			}
			else {
				if (results.affectedRows > 0)
					return callback(null, results);
				else {
					err = { code: status.NOT_FOUND, message: "Paciente doesn't exist" };
					return callback(err, null);
				}
			}
		});
	},
	getInfoPacientes: function (callback) {
		pool.query('select p.*, a.nome_area from paciente p, area a where a.id_area=p.id_area group by p.id_paciente', function (error, results) {
			if (error) {
				let err = { code: status.INTERNAL_SERVER_ERROR, message: error };
				return callback(err, null);
			}
			else {
				return callback(null, results);
			}
		});
	},
	getPacienteInfoByArea: function (req, callback) {
		let query = "call obter_pacientesEstadoPorArea(?)";
		let table = [req.params.id_area];
		query = mysql.format(query, table);
		pool.query(query, function (error, results) {
			if (error) {
				err = { code: status.INTERNAL_SERVER_ERROR, message: error };
				return callback(err, null);
			}
			else {
				if (results.length > 0)
					return callback(null, results[0]);
				else {
					let err = { code: status.NOT_FOUND, message: "Area doesn't exist" };
					return callback(err, null);
				}
			}
		});
	},

	// 
	// LEITURAS
	// 
	getLeituras: function (callback) {
		pool.query('SELECT * FROM leitura', function (error, results) {
			if (error) {
				let err = { code: status.INTERNAL_SERVER_ERROR, message: error };
				return callback(err, null);
			}
			else {
				return callback(null, results);
			}
		});
	},
	getLeituraById: function (req, callback) {
		let query = "SELECT * FROM leitura WHERE id_leitura = ?";
		let table = [req.params.id_leitura];
		query = mysql.format(query, table);
		pool.query(query, function (error, results) {
			if (error) {
				err = { code: status.INTERNAL_SERVER_ERROR, message: error };
				return callback(err, null);
			}
			else {
				if (results.length > 0)
					return callback(null, results);
				else {
					let err = { code: status.NOT_FOUND, message: "Leitura doesn't exist" };
					return callback(err, null);
				}
			}
		});
	},
	insertLeitura: function (req, callback) {
		if (!req.body.estado_fisico || !req.body.id_paciente) {
			let err = { code: status.BAD_REQUEST, message: "Please provide Leitura" };
			return callback(err, null);
		} else {
			let query = "call inserir_leitura(?,?)";
			let table = [req.body.estado_fisico, req.body.id_paciente];
			query = mysql.format(query, table);
			pool.query(query, function (errorInsert, resultsInsert) {
				if (errorInsert) {
					err = { code: status.INTERNAL_SERVER_ERROR, message: errorInsert };
					return callback(err, null);
				}
				else {
					return callback(null, resultsInsert);
				}
			});
		}
	},
	updateLeitura: function (req, callback) {
		if (!req.body.estado_fisico || !req.body.id_paciente) {
			let err = { code: status.BAD_REQUEST, message: "Please provide Leitura" };
			return callback(err, null);
		} else {
			let query = "UPDATE leitura SET estado_fisico=?,id_paciente=? WHERE id_leitura = ?";
			let table = [req.body.estado_fisico, req.body.id_paciente, req.params.id_leitura];
			query = mysql.format(query, table);
			pool.query(query, function (error, results) {
				if (error) {
					err = { code: status.INTERNAL_SERVER_ERROR, message: error };
					return callback(err, null);
				}
				else {
					if (results.affectedRows > 0)
						return callback(null, results);
					else {
						err = { code: status.NOT_FOUND, message: "Leitura doesn't exist" };
						return callback(err, null);
					}
				}
			});
		}
	},
	deleteLeitura: function (req, callback) {
		let query = "DELETE from leitura WHERE id_leitura = ?";
		let table = [req.params.id_leitura];
		query = mysql.format(query, table);
		pool.query(query, function (error, results) {
			if (error) {
				err = { code: status.INTERNAL_SERVER_ERROR, message: error };
				return callback(err, null);
			}
			else {
				if (results.affectedRows > 0)
					return callback(null, results);
				else {
					err = { code: status.NOT_FOUND, message: "Leitura doesn't exist" };
					return callback(err, null);
				}
			}
		});
	},
	getLastLeituraByIdPaciente: function (req, callback) {
		let query = "SELECT * FROM leitura WHERE id_paciente = ? order by ts desc limit 1";
		let table = [req.params.id_paciente];
		query = mysql.format(query, table);
		pool.query(query, function (error, results) {
			if (error) {
				err = { code: status.INTERNAL_SERVER_ERROR, message: error };
				return callback(err, null);
			}
			else {
				if (results.length > 0)
					return callback(null, results);
				else {
					let err = { code: status.NOT_FOUND, message: "Paciente doesn't exist" };
					return callback(err, null);
				}
			}
		});
	},
	getLeiturasByPaciente: function (req, callback) {
		let query = "SELECT * FROM leitura WHERE id_paciente = ?";
		let table = [req.params.id_paciente];
		query = mysql.format(query, table);
		pool.query(query, function (error, results) {
			if (error) {
				err = { code: status.INTERNAL_SERVER_ERROR, message: error };
				return callback(err, null);
			}
			else {
				if (results.length > 0)
					return callback(null, results);
				else {
					let err = { code: status.NOT_FOUND, message: "Leituras de paciente doesn't exist" };
					return callback(err, null);
				}
			}
		});
	},

	// 
	// CONCENTRADOR
	// 
	getConcentradores: function (callback) {
		pool.query('SELECT * FROM concentrador', function (error, results) {
			if (error) {
				let err = { code: status.INTERNAL_SERVER_ERROR, message: error };
				return callback(err, null);
			}
			else {
				return callback(null, results);
			}
		});
	},
	getConcentradorById: function (req, callback) {
		let query = "SELECT * FROM concentrador WHERE id_concentrador = ?";
		let table = [req.params.id_leitura];
		query = mysql.format(query, table);
		pool.query(query, function (error, results) {
			if (error) {
				err = { code: status.INTERNAL_SERVER_ERROR, message: error };
				return callback(err, null);
			}
			else {
				if (results.length > 0)
					return callback(null, results);
				else {
					let err = { code: status.NOT_FOUND, message: "Concentrador doesn't exist" };
					return callback(err, null);
				}
			}
		});
	},
	insertConcentrador: function (req, callback) {
		if (!req.body.nome) {
			let err = { code: status.BAD_REQUEST, message: "Please provide Concentrador" };
			return callback(err, null);
		} else {
			let query = "call inserir_concentrador(?)";
			let table = [req.body.nome];
			query = mysql.format(query, table);
			pool.query(query, function (errorInsert, resultsInsert) {
				if (errorInsert) {
					err = { code: status.INTERNAL_SERVER_ERROR, message: errorInsert };
					return callback(err, null);
				}
				else {
					return callback(null, resultsInsert);
				}
			});
		}
	},
	updateConcentrador: function (req, callback) {
		if (!req.body.nome) {
			let err = { code: status.BAD_REQUEST, message: "Please provide Concentrador" };
			return callback(err, null);
		} else {
			let query = "UPDATE concentrador SET nome=? WHERE id_concentrador = ?";
			let table = [req.body.nome, req.params.id_concentrador];
			query = mysql.format(query, table);
			pool.query(query, function (error, results) {
				if (error) {
					err = { code: status.INTERNAL_SERVER_ERROR, message: error };
					return callback(err, null);
				}
				else {
					if (results.affectedRows > 0)
						return callback(null, results);
					else {
						err = { code: status.NOT_FOUND, message: "Concentrador doesn't exist" };
						return callback(err, null);
					}
				}
			});
		}
	},
	deleteConcentrador: function (req, callback) {
		let query = "DELETE from concentrador WHERE id_concentrador = ?";
		let table = [req.params.id_concentrador];
		query = mysql.format(query, table);
		pool.query(query, function (error, results) {
			if (error) {
				err = { code: status.INTERNAL_SERVER_ERROR, message: error };
				return callback(err, null);
			}
			else {
				if (results.affectedRows > 0)
					return callback(null, results);
				else {
					err = { code: status.NOT_FOUND, message: "Concentrador doesn't exist" };
					return callback(err, null);
				}
			}
		});
	},

	// 
	// SISTEMA SENSOR
	// 
	getSistemaSensor: function (callback) {
		pool.query('SELECT * FROM sistemaSensor', function (error, results) {
			if (error) {
				let err = { code: status.INTERNAL_SERVER_ERROR, message: error };
				return callback(err, null);
			}
			else {
				return callback(null, results);
			}
		});
	},
	getSistemaSensorById: function (req, callback) {
		let query = "SELECT * FROM sistemaSensor WHERE id_sistemaSensor = ?";
		let table = [req.params.id_sistemaSensor];
		query = mysql.format(query, table);
		pool.query(query, function (error, results) {
			if (error) {
				err = { code: status.INTERNAL_SERVER_ERROR, message: error };
				return callback(err, null);
			}
			else {
				if (results.length > 0)
					return callback(null, results);
				else {
					let err = { code: status.NOT_FOUND, message: "SistemaSensor doesn't exist" };
					return callback(err, null);
				}
			}
		});
	},
	insertSistemaSensor: function (req, callback) {
		if (!req.body.sensorSimulado || !req.body.id_paciente || !req.body.id_concentrador) {
			let err = { code: status.BAD_REQUEST, message: "Please provide SistemaSensor" };
			return callback(err, null);
		} else {
			let query = "call inserir_sistemaSensor(?,?,?)";
			let table = [req.body.sensorSimulado, req.body.id_paciente, req.body.id_concentrador];
			query = mysql.format(query, table);
			pool.query(query, function (errorInsert, resultsInsert) {
				if (errorInsert) {
					err = { code: status.INTERNAL_SERVER_ERROR, message: errorInsert };
					return callback(err, null);
				}
				else {
					return callback(null, resultsInsert);
				}
			});
		}
	},
	updateSistemaSensor: function (req, callback) {
		if (!req.body.sensorSimulado || !req.body.id_paciente || !req.body.id_concentrador) {
			let err = { code: status.BAD_REQUEST, message: "Please provide SistemaSensor" };
			return callback(err, null);
		} else {
			let query = "UPDATE sistemaSensor SET sensorSimulado=?,id_paciente=?,id_concentrador=? WHERE id_sistemaSensor = ?";
			let table = [req.body.sensorSimulado, req.body.id_paciente, req.body.id_concentrador, req.params.id_sistemaSensor];
			query = mysql.format(query, table);
			pool.query(query, function (error, results) {
				if (error) {
					err = { code: status.INTERNAL_SERVER_ERROR, message: error };
					return callback(err, null);
				}
				else {
					if (results.affectedRows > 0)
						return callback(null, results);
					else {
						err = { code: status.NOT_FOUND, message: "SistemaSensor doesn't exist" };
						return callback(err, null);
					}
				}
			});
		}
	},
	deleteSistemaSensor: function (req, callback) {
		let query = "DELETE from sistemaSensor WHERE id_sistemaSensor = ?";
		let table = [req.params.id_sistemaSensor];
		query = mysql.format(query, table);
		pool.query(query, function (error, results) {
			if (error) {
				err = { code: status.INTERNAL_SERVER_ERROR, message: error };
				return callback(err, null);
			}
			else {
				if (results.affectedRows > 0)
					return callback(null, results);
				else {
					err = { code: status.NOT_FOUND, message: "SistemaSensor doesn't exist" };
					return callback(err, null);
				}
			}
		});
	},

	// 
	// REGISTER, LOGIN E UTILIZADORES
	// 
	register: function (req, callback) {
		if (!req.body.username || !req.body.morada || !req.body.mail || !req.body.password || !req.body.id_tipoUtilizador) {
			let err = { code: status.BAD_REQUEST, message: "Please provide User" };
			return callback(err, null);
		} else {
			//verificar se email já existe
			let query = "select * from utilizador where mail = ?";
			let table = [req.body.email];
			query = mysql.format(query, table);
			pool.query(query, function (errorMail, resultsMail) {
				if (errorMail) {
					err = { code: status.INTERNAL_SERVER_ERROR, message: errorMail };
					return callback(err, null);
				}
				else {
					if (resultsMail.length > 0) {
						//mail já existe, não é possivel registar
						err = { code: status.BAD_REQUEST, message: "Mail already exists" };
						return callback(err, null);
					} else {
						let hashedPassword = bcrypt.hashSync(req.body.password, 8);
						//mail não existe, pode fazer insert
						let query = "call inserir_utilizador(?,?,?,?,?)";
						let table = [req.body.username, req.body.morada, req.body.mail, hashedPassword, req.body.id_tipoUtilizador];
						query = mysql.format(query, table);
						pool.query(query, function (error, results) {
							if (error) {
								err = { code: status.INTERNAL_SERVER_ERROR, message: error };
								return callback(err, null);
							}
							else {
								//create token
								var token = jwt.sign({ id: results.insertId }, "config.secret", {
									expiresIn: 86400 // expires in 24 hours
								});
								results.token = token;
								results.auth = true;
								console.log(JSON.stringify(results));
								return callback(null, results);
							}
						});
					}
				}
			});
		}
	},
	login: function (req, callback) {
		if (!req.body.password || !req.body.mail) {
			let err = { code: status.BAD_REQUEST, message: "Please provide utilizador" };
			return callback(err, null);
		} else {
			let query = "select * from utilizador where mail = ?";
			let table = [req.body.mail];
			query = mysql.format(query, table);
			pool.query(query, function (error, results) {
				if (error) {
					err = { code: status.INTERNAL_SERVER_ERROR, message: error };
					return callback(err, null);
				}
				else {
					if (results.length > 0) {
						//check password
						console.log(JSON.stringify(req.body) + " \n" + JSON.stringify(results));
						var passwordIsValid = bcrypt.compareSync(req.body.password, results[0].password);
						if (!passwordIsValid) {
							err = { code: status.UNAUTHORIZED, message: "Wrong password" };
							return callback(err, null);
						}
						var token = jwt.sign({ id: results.id_user }, "config.secret", {
							expiresIn: 86400 // expires in 24 hours
						});
						results[0].token = token;
						results[0].auth = true;
						console.log(JSON.stringify(results));
						return callback(null, results[0]);
					} else {
						let err = { code: status.NOT_FOUND, message: "Utilizador doesn't exist" };
						return callback(err, null);
					}
				}
			});
		}
	},
	updateUtilizador: function (req, callback) {
		if (!req.body.username || !req.body.morada || !req.body.mail || !req.body.password || !req.body.id_tipoUtilizador) {
			let err = { code: status.BAD_REQUEST, message: "Please provide utilizador" };
			return callback(err, null);
		} else {
			let query = "UPDATE utilizador SET username=?, morada=?, mail=?, password=?, id_tipoUtilizador=? WHERE id_utilizador = ?";
			let hashedPassword = bcrypt.hashSync(req.body.password, 8);
			let table = [req.body.username, req.body.morada, req.body.mail, hashedPassword, req.body.id_tipoUtilizador, req.params.id_utilizador];
			query = mysql.format(query, table);
			pool.query(query, function (error, results) {
				if (error) {
					err = { code: status.INTERNAL_SERVER_ERROR, message: error };
					return callback(err, null);
				}
				else {
					if (results.affectedRows > 0)
						return callback(null, results);
					else {
						err = { code: status.NOT_FOUND, message: "Utilizador doesn't exist" };
						return callback(err, null);
					}
				}
			});
		}
	},
	deleteUtilizador: function (req, callback) {
		let query = "DELETE from utilizador WHERE id_utilizador = ?";
		let table = [req.params.id_utilizador];
		query = mysql.format(query, table);
		pool.query(query, function (error, results) {
			if (error) {
				err = { code: status.INTERNAL_SERVER_ERROR, message: error };
				return callback(err, null);
			}
			else {
				if (results.affectedRows > 0)
					return callback(null, results);
				else {
					err = { code: status.NOT_FOUND, message: "Utilizador doesn't exist" };
					return callback(err, null);
				}
			}
		});
	},
	getUtilizadores: function (callback) {
		pool.query('SELECT id_utilizador,username,morada,mail,id_tipoUtilizador FROM utilizador', function (error, results) {
			if (error) {
				let err = { code: status.INTERNAL_SERVER_ERROR, message: error };
				return callback(err, null);
			}
			else {
				return callback(null, results);
			}
		});
	},
	getUtilizadoresById: function (req, callback) {
		let query = "SELECT id_utilizador,username,morada,mail,id_tipoUtilizador FROM utilizador WHERE id_utilizador = ?";
		let table = [req.params.id_utilizador];
		query = mysql.format(query, table);
		pool.query(query, function (error, results) {
			if (error) {
				err = { code: status.INTERNAL_SERVER_ERROR, message: error };
				return callback(err, null);
			}
			else {
				if (results.length > 0)
					return callback(null, results);
				else {
					let err = { code: status.NOT_FOUND, message: "Utilizador doesn't exist" };
					return callback(err, null);
				}
			}
		});
	}
}