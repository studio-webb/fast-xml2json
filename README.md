Node Module that converts XML to JSON using C++


## Notice: for now package support only node.js v0.10.*
### support node.js v0.12.* , v4.* , v5.* coming soon


## Install

Install fast-xml2json package  
```

	npm install --save fast-xml2json

```

## Use Async Convertor xml files to json files

```js
var xml2json = require('xml2json');

xml2json.convertFile(xmlFilePath, jsonFilePath, callback);
```

## Example to use with package async 

The source of package async is available for download from
[GitHub](http://github.com/caolan/async). 

```js
var xml2json = require('fast-xml2json');
var async = require('async');
var fs = require('fs');
var path = require('path');
var xmlFilesPath = './xmlFiles',
	jsonFilesPath = './jsonFiles',
	count = 0,
	filesArr;

filesArr = fs.readdirSync(xmlFilesPath);
if(filesArr.length > 0) {
	if(!fs.existsSync(jsonFilesPath)) fs.mkdirSync(jsonFilesPath);
	
	async.eachSeries(filesArr, function (xmlFile, callback) {
		if(path.extname(xmlFile) != '.xml' ) return callback();
		
		fileJson = path.join(jsonFilesPath, path.basename(xmlFile, '.xml') + '.json');
		xmlFile = path.join(xmlFilesPath, xmlFile);
		
		xml2json.convertFile(xmlFile, fileJson, function (err) {
			console.log(++count + ': ' + fileJson);
			callback();
		});
	}, function (err) {
		// do something
	});
} else {
	console.log('Directory ' + xmlFilesPath + ' doesn\'t have xml files' );
}
```
