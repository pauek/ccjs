
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
   } else if (a == '--rewrite') {
      opts.rewrite = true;
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
      tree.walk(ast.showTree);
   } else if ('rewrite' in opts) {
      var R = new ast.Rewriter();
      tree.walk(R);
      console.log(R.output);
   } else {
      console.log("<Here there would be the output of the program...>");
   }
});

