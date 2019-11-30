var fs = require('fs');

fs.writeFile('tmp/mynewfile3.txt', 'Content replaced successfully!', function (err) {
    if (err) throw err;
    console.log('Saved!');
}); 
