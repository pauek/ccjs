
var ast = ast || {};
var util = require('util');

/* Model of inheritance */

ast.__inherit__ = (function() {
   var F = function (typename) {
      this.typename = typename;
   };
   return function (typename, Child, Parent) {
      F.prototype = Parent.prototype;
      Child.prototype = new F(typename);
      Child.uber = Parent.prototype;
      Child.prototype.constructor = Child;
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
            return visitor[method].call(visitor, this);
         } 
      }
   },
   visit: function (visitor) {
      return this.__accept__('visit', visitor);
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

   "CharLiteral",
   "IntegerLiteral",
   "FloatLiteral",
   "StringLiteral",

   "Identifier",
   "FunctionDefinition", 
   "CallStatement",
   "MethodCall",
   "ActualParameterList",
   "FormalParameter",
   "FormalParameterList",
   "Program", 

   "VariableReference",
   "ArrayReference",
   "MemberAccess",

   "Type", 
   "VectorType",

   "ArrayTypedefDeclaration",
   "StructDeclaration",
   "ArrayDeclaration",
   "VariableDeclaration",
   "VariableDeclarationStatement",
   "VectorConstructor",
   "VectorCopyConstructor",
   "VectorDeclarationStatement",

   "PostfixExpression",
   "UnaryExpression",
   "AssignmentExpression",
   "LogicalANDExpression",
   "LogicalORExpression",
   "ComparisonExpression",
   "CallExpression",

   "AssignmentStatement",
   "InputStatement",
   "OutputStatement",
   "OutputElement",
	"ConditionalBlock",
	"IfStatement",
	"IfElseStatement",
	"IfElseIfStatement",
	"WhileStatement",
	"ForStatement", 
   "SwitchCase",
   "SwitchStatement",
   "ReturnStatement",
   "Block",
   "BinaryExpression",

];
for (var i in nodeTypes) { 
   ast.makeNodeType(nodeTypes[i]); 
}

/* Declare a Method on all AST Classes */

ast.declareMethod = function (name, aspect) {
   // distribute methods to prototypes by name
   for (var typename in aspect) {
      var method = aspect[typename];
      if (typename in ast) {
         var type = ast[typename];
         var uber = type.uber;
         type.prototype[name] = method;
         // permit calling "super" methods with "this.nextMethod(...)"
         if (uber !== undefined && name in uber) {
            type.prototype[name] = (function (name, method) {
                return function () {
                   var tmp = this.nextMethod;
                   if (name in uber) {
                      this.nextMethod = uber[name];
                   }
                   var ret = method.apply(this, arguments);
                   this.nextMethod = tmp;
                   return ret;
                }
            })(name, method);
         }
      } else {
         console.log("Warning: type '" + typename + "' not in AST");
      }
   }
}

// printState

var PrintState = function () {
   this._indented = false;
   this._indent = 0;
   this.output = "";
}

PrintState.prototype = {
   _maybe_indent: function () {
      if (!this._indented) {
         this._indented = true;
         for (var i = 0; i < this._indent; i++) {
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
      this._indented = false;
   },
   i: function (n) { 
      this._indent += n*3; 
   }
};

// printTree

ast.declareMethod("printTree", {
   Node: function (out) {
      out.w(this.typename);
      var nodeprops = [], otherprops = [];
		for (var prop in this) {
			if (this.hasOwnProperty(prop) && prop != "__children__") {
				if (this[prop] instanceof ast.Node || this[prop] instanceof Array) {
               nodeprops.push(prop);
				} else {
               otherprops.push(prop);
            }
			}
		}
      // Non-Node properties
      if (otherprops.length > 0) {
         out.w("{ ");
         for (var i = 0; i < otherprops.length; i++) {
            var prop = otherprops[i];
            if (i != 0) {
               out.w(", ");
            }
            out.w(prop + ": " + this[prop]);
         }
         out.w(" }");
      }
      // Node properties
		out.i(+2);
      for (var i = 0; i < nodeprops.length; i++) {
         var prop = nodeprops[i];
         if (this[prop] instanceof Array) {
				out.p();
				out.w(prop + ":");
            var property = this[prop];
				for (var j = 0; j < property.length; j++) {
					if (property[j] instanceof ast.Node) {
						property[j].printTree(out);
					}
				}
         } else {
            out.p();
			   out.w(prop + ":");
			   out.i(+1);
			   this[prop].printTree(out);
			   out.i(-1);
         }
      }
      // Children
		out.i(-1);
      if (this.isGroup()) {
         this.forEachChild(function (child) {
				out.p();
            child.printTree(out);
         });
      }
		out.i(-1);
   },
});

// nodeCount

ast.declareMethod("nodeCount", {
   Node: function () {
      var count = 1;
      if (this.isGroup()) {
         this.forEachChild(function (child) {
            count += child.nodeCount();
         });
      }
      return count;
   }
});

