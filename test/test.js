#!/usr/bin/env node

var fs = require("fs");
var childProcess = require("child_process");

var FILE = process.argv[2];

function returnStdOut(_callback) {
   return function (error, stdout, stderr) {
      _callback(stdout);
   }
}

function realOutput(_callback) {
   childProcess.exec("g++ " + FILE, function (error, stdout, stderr) {
      childProcess.exec("./a.out", returnStdOut(_callback));
   });
}

function interpretedOutput(_callback) {
   childProcess.exec("./cc.js " + FILE, returnStdOut(_callback));
}

realOutput(function (rOutput) {
   interpretedOutput(function (iOutput) {
      fs.unlink("a.out");
      if (rOutput == iOutput) {
         console.log('PASS');
      } else {
         console.log('FAIL');
      }
   });
});