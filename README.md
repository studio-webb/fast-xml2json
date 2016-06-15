Node Module that converts XML to JSON using C++


## Package support all version of node.js v0.10.x, v0.12.x , v4.x , v5.x, v6.x


## Install

Install fast-xml2json package  
```

	npm install --save fast-xml2json

```

## Use Async Convertor xml files to json files

```js
var xml2json = require('xml2json');

xml2json.convertToFile(xmlFilePath, jsonFilePath, callback);
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
		
		xml2json.convertToFile(xmlFile, fileJson, function (err) {
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

## Use Async Convertor xml files to json string

```js
var xml2json = require('xml2json');

xml2json.convertToJson(xmlFilePath, callback);
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
	count = 0,
	filesArr;

filesArr = fs.readdirSync(xmlFilesPath);
if(filesArr.length > 0) {
	
	async.eachSeries(filesArr, function (xmlFile, callback) {
		if(path.extname(xmlFile) != '.xml' ) return callback();
		
		xmlFile = path.join(xmlFilesPath, xmlFile);
		
		xml2json.convertToJson(xmlFile, function (err, result) {
			console.log(++count + ': ' + xmlFile);
			console.log(result.toString());
			callback();
		});
	}, function (err) {
		// do something
	});
} else {
	console.log('Directory ' + xmlFilesPath + ' doesn\'t have xml files' );
}
```
