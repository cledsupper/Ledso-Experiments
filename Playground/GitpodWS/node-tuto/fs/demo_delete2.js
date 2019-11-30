var fs = require('fs');

fs.unlink('tmp/mynewfile2.txt', function (err) {
    if (err) throw err;
    console.log('File deleted!');
});
