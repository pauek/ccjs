
var ast = ast || {};
var util = require('util');

/* Model of inheritance */

ast.__inherit__ = (function() {
   var F = function (typename) {
      this.typename = typename;
   };
   return function (typename, C, P) {
      F.prototype = P.prototype;
      C.prototype = new F(typename);
      C.uber = P.prototype;
      C.prototype.constructor = C;
   }
})();

/* Node type */

ast.Node = function () {};

ast.Node.prototype = {
   typename: "Node",
   isGroup: function () {
      return this.hasOwnProperty('__children__');
   },
   forEachChild: function (fn) {
      for (var i in this.__children__) {
         fn(this.__children__[i]);
      }
   },
   __accept__: function (prefix, visitor) {
      var types = [this.typename, 'Node'];
      for (var i in types) {
         var method = prefix + types[i];
         if (method in visitor) {
            visitor[method].call(visitor, this);
            return;
         } 
      }
   },
   visit: function (visitor) {
      this.__accept__('visit', visitor);
   },
   walk: function (walker) {
      this.__accept__('enter', walker);
      this.forEachChild(function (obj) {
         obj.walk(walker);
      });
      this.__accept__('depart', walker);
   }
};

/* Construct node types */

ast.makeNodeType = function (typename) {
   var NewType = function (obj, children) {
      for (var prop in obj) {
         if (obj.hasOwnProperty(prop)) {
	         this[prop] = obj[prop];
         }
      }
      if (children) {
         this.__children__ = children;
      }
   }
   ast.__inherit__(typename, NewType, ast.Node);
   ast[typename] = NewType;
}

/* Create Types */

var nodeTypes = [
   "IncludeDirective", 
	"UsingDirective", 
   "Identifier",
   "FunctionDef", 
   "Program", 
   "VariableReference",
   "VariableDeclaration",
   "VariableDeclarationStatement",
   "InputStatement",
   "OutputStatement",
   "OutputElement",
	"ForStmt", 
	"WhileStmt",
   "Block",
   "BinaryExpression",
   "StringLiteral",
];
for (var i in nodeTypes) { 
   ast.makeNodeType(nodeTypes[i]); 
}

/* Visitors */

// showTree

ast.showTree = {
   indent: 0,
   group: false,

   log: function (msg) {
      var _indent = "";
      for (var i = 0; i < this.indent; i++) {
         _indent += " ";
      }
      console.log(_indent + msg);
   },
   enterNode: function(obj) {
      this.log(obj.typename);
      if (obj.isGroup()) this.indent += 3;
   },
   departNode: function (obj) {
      if (obj.isGroup()) this.indent -= 3;
   }
}

// nodeCount

ast.nodeCount = function () {
   this.count = 0;
}

ast.nodeCount.prototype = {
   visitNode: function(obj) {
      this.count++;
   }
}

// Rewriter

ast.Rewriter = function () {
   this.indented = false;
   this.indent = 0;
   this.output = "";
}

ast.Rewriter.prototype = {
   _maybe_indent: function () {
      if (!this.indented) {
         this.indented = true;
         for (var i = 0; i < this.indent; i++) {
            this.output += ' ';
         }
      }
   },
   w: function (str) {
      this._maybe_indent();
      this.output += str;
   },
   p: function(str) {
      this._maybe_indent();
      if (str) this.output += str;
      this.output += '\n';
      this.indented = false;
   },
   walk: function (node) {
      if (node) node.walk(this);
   },

   enterIncludeDirective: function (obj) {
      this.p("#include <" + obj.file + ">");
   },
   enterUsingDirective: function (obj) {
      this.p("using namespace " + obj.namespace.id + ";");
   },
   enterFunctionDef: function (obj) {
      this.p();
      this.w(obj.type + ' ' + obj.name.id);
      this.w('(');
      this.walk(obj.params);
      this.p(') {');
      this.indent += 3;
   },
   departFunctionDef: function (obj) {
      this.indent -= 3;
      this.p('}');
   },
   enterIdentifier: function (obj) {
      this.w(obj.id);
   },
   enterOutputStatement: function (obj) {
      this.w(obj.head);
   },
   departOutputStatement: function (obj) {
      this.p(';');
   },
   enterOutputElement: function (obj) {
      this.w(' << ');
      this.walk(obj.expr);
   },
   enterStringLiteral: function (obj) {
      this.w('"' + obj.lit + '"');
   },
   enterVariableReference: function (obj) {
      this.w(obj.name.id);
   },
}

/* Export */

module.exports = ast;

