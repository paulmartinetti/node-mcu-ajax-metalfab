// load up the express framework and body-parser helper
const express = require('express');

// create an instance of express to serve our end points
const app = express();

// we'll load up node's built in file system helper library here
// (we'll be using this later to serve our JSON files
const fs = require('fs');
const { Script } = require('vm');

// configure our express instance with some body-parser settings
// including handling JSON data
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(express.static('public'));

// this is where we'll handle our various routes from
const routes = require('./routes/routes.js')(app, fs);

Script.js;

//finally, launch our server on port 3001.
const server = app.listen(3001, () => {
    console.log('listening on port %s...', server.address().port);
});

// socket for esp32 to fetch projet data
var net = require('net');
var serverN = net.createServer(function(socket) {
	fs.readFile("./data/projet.json", 'utf-8', (err, data) => {
		if (err) {
			throw err;
		}
		socket.write(JSON.stringify(data));
		socket.pipe(socket);
	});
	socket.on('end', () => {
		console.log('client disconnected');
	  });
});
serverN.on('error', (err) => {
	throw err;
  });
//serverN.listen(1337, '10.0.0.250');
//console.log('socket listening on port...',1337);
serverN.listen(1337, () => {
	console.log('server bound at port 1337');
  });