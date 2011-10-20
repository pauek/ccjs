
function usage() {
   console.log("usage: cc.js <input-file>");
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
   } else if (a == '--parsetest') {
      opts.parsetest = true;
   } else {
      opts.ccfile = a;
   }
}

if (!('ccfile' in opts)) {
   usage();
}

fs.readFile(opts.ccfile, 'utf-8', function (err, data) {
   if ('ast' in opts) {
      var tree = cc.parse(data);
      var P = new PrintState();
      try {
         tree.printTree(P);
         console.log(P.output);
         console.log(tree.nodeCount());
      } catch (e) {
         console.log(P.output);
         console.log(e.message);
      }
   } else if ('prettyprint' in opts) {
      var tree = cc.parse(data);
      var P = new PrintState();
      tree.prettyPrint(P);
      console.log(P.output);
   } else if ('parsetest' in opts) {
      process.stdout.write(opts.ccfile);
      var tree;
      try {
         tree = cc.parse(data);
         process.stdout.write(": parse ok\n");
      } catch (e) {
         process.stdout.write(": parse failed\n");
      }
   } else {
      var tree = cc.parse(data);
   }
});

