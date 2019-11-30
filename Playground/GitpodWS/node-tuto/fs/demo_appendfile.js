var fs = require('fs');

fs.appendFile('tmp/mynewfile1.txt', 'Hello world!',
	      function (err) {
		  if (err) throw err;
		  console.log('Saved!');
	      });
