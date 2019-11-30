var fs = require('fs');

fs.rename('tmp/mynewfile1.txt', 'tmp/myrenamedfile.txt', function (err) {
    if (err) throw err;
    console.log('File Renamed!');
});
