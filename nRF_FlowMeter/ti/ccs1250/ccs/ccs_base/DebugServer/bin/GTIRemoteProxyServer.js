/*jslint node: true */
"use strict";

var net = require("net");
var spawn = require("child_process").spawn;

function handleError(e) {
	console.log(e);
}

var server = net.createServer(function(socket) {

	var lp;

	function stdoutHandler(data) {
		try {
			var buffer = new Buffer(2);
			buffer.writeUInt16LE(parseInt(data, 10), 0);
			socket.write(buffer);
			socket.pipe(socket);
			lp.stdout.removeListener("data", stdoutHandler);
		} catch (e) {
			handleError(e);
		}
	}

	try {
		socket.on("error", handleError);
		lp = spawn("./GTIRemoteProxyServer", [], {
			cwd: __dirname,
			detached: true
		});

		lp.stdout.on("data", stdoutHandler);
		lp.stderr.on("data", handleError);
		lp.stderr.on("error", handleError);
	} catch (e) {
		handleError(e);
	}
});

var port = process.argv[2] || 7710;
server.listen(port);