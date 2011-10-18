#!/usr/bin/env node

var fs = require("fs");
var childProcess = require("child_process");

var TEST_FILES = fs.readdirSync("test").filter(function (file) {
  return /\.cc$/.test(file);
});

function returnStdOut(error, stdout, stderr) {
   _callback(stdout);
}

function realOutput(sourceFile, _callback) {
   childProcess.exec("g++ " + sourceFile, function () {
      childProcess.exec("a.out", returnStdOut);
   });
}

function interpretedOutput(sourceFile, _callback) {
   childProcess.exec("./cc.js " + sourceFile, returnStdOut);
}

for (var i in TEST_FILES) {
   var file = TEST_FILES[i];
}