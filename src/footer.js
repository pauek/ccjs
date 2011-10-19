
function usage() {
   console.log("usage: cxx.js <input-file>");
   process.exit(1);
}

if (process.argv.length < 3) {
   usage();
}

var opts = {};
var args = process.argv.slice(1);
for (var i in args) {
   var a = args[i];
   if (a == '--ast') {
      opts.ast = true;
   } else if (a == '--prettyprint') {
      opts.prettyprint = true;
   } else {
      opts.ccfile = a;
   }
}

if (!('ccfile' in opts)) {
   usage();
}

fs.readFile(opts.ccfile, 'utf-8', function (err, data) {
   var tree = cc.parse(data);
   if ('ast' in opts) {
      var P = new PrintState();
      tree.printTree(P);
      console.log(P.output);
      console.log(tree.countNodes());
   } else if ('prettyprint' in opts) {
      var P = new PrintState();
      tree.prettyPrint(P);
      console.log(P.output);
   } else {
      interpret(tree);
   }
});

