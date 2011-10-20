
ast.declareMethod("prettyPrint", {
   Node: function (out) {
      if (this.isGroup()) {
         this.forEachChild(function (child) {
            child.prettyPrint(out);
         });
      } else {
         out.w("?" + this.typename + "?");
      }
   },
   Program: function (out) {
      out.p();
      this.nextMethod(out);
   },
   IncludeDirective: function (out) {
      out.p("#include <" + this.file + ">");
   },
   UsingDirective: function (out) {
      out.p("using namespace " + this.namespace.id + ";");
   },
   FunctionDef: function (out) {
      out.p();
      this.type.prettyPrint(out);
      out.w(" " + this.name.id);
      out.w("(");
      for (var i = 0; i < this.params.length; i++) {
         this.params[i].prettyPrint(out);
      }
      out.p(") {");
      out.i(+1);
      this.nextMethod(out);
      out.i(-1);
      out.p("}");
   },
   FormalParameter: function (out) {
      this.type.prettyPrint(out);
      out.w(" " + this.name.id);
   },
   Identifier: function (out) {
      out.w(this.id);
   },
   OutputStatement: function (out) {
      out.w(this.head);
      this.forEachChild(function (child) {
         out.w(" << ");
         child.prettyPrint(out);
      });
      out.p(";");
   },
   InputStatement: function (out) {
      out.w(this.head);
      this.forEachChild(function (child) {
         out.w(" >> ");
         child.prettyPrint(out);
      });
      out.p(";");
   },
   AssignmentStatement: function (out) {
      this.expr.prettyPrint(out);
      out.p(";");
   },
   AssignmentExpression: function (out) {
      this.lvalue.prettyPrint(out);
      out.w(" " + this.operator + " ");
      this.rvalue.prettyPrint(out);
   },
   WhileStatement: function (out) {
      out.w("while (");
      this.cond.prettyPrint(out);
      out.p(") {");
      out.i(+1);
      this.nextMethod(out);
      out.i(-1);
      out.p("}");
   },
   IfStatement: function (out) {
      out.w("if (");
      this.cond.prettyPrint(out);
      out.p(") {");
      out.i(+1);
      this.nextMethod(out);
      out.i(-1);
      out.p("}");
   },
	IfElseStatement: function (out) {
		var prBlock = function (block) {
			out.p("{"); 
			out.i(+1);
			for (var i = 0; i < block.length; i++) {
				block[i].prettyPrint(out);
			}
			out.i(-1); 
			out.w("}");
		}
		out.w("if (");
		this.cond.prettyPrint(out);
		out.w(") ");
		prBlock(this.then);
		out.w(" else ");
		prBlock(this.elze);
		out.p();
	},
   ForStatement: function (out) {
      out.w("for (");
      this.init.prettyPrint(out);
      out.w("; ");
      this.cond.prettyPrint(out);
      out.w("; ");
      this.incr.prettyPrint(out);
      out.p(") {");
      out.i(+1);
      this.nextMethod(out);
      out.i(-1);
      out.p("}");
   },
   PostfixExpression: function (out) {
      this.left.prettyPrint(out);
      out.w(this.operator);
   },
   BinaryExpression: function (out) {
      this.left.prettyPrint(out);
      out.w(" " + this.operator + " ");
      this.right.prettyPrint(out);
   },
   ActualParameterList: function (out) {
      out.w("(");
      var i = 0
      this.forEachChild(function (child) {
         if (i != 0) out.w(", ");
         child.prettyPrint(out);
         i++;
      });
      out.w(")");
   },
   OutputElement: function (out) {
      out.w(" << ");
      this.expr.prettyPrint(out);
   },
   IntegerLiteral: function (out) {
      out.w('' + this.lit);
   },
   StringLiteral: function (out) {
      out.w('"' + this.lit + '"');
   },
   Type: function (out) {
      out.w(this.name);
   },
   VariableDeclaration: function (out) {
      out.w(this.name.id);
      if (this.value !== undefined) {
         out.w(" ");
         this.value.prettyPrint(out);
      }
   },
   VariableDeclarationStatement: function (out) {
      this.type.prettyPrint(out);
      out.w(" ");
      var i = 0;
      this.forEachChild(function (child) {
         if (i != 0) out.w(", ");
         child.prettyPrint(out);
         i++;
      });
      out.p(";");
   },
   VariableReference: function (out) {
      out.w(this.name.id);
   },
   VectorType: function (out) {
      out.w('vector<');
      this.subtype.prettyPrint(out);
      out.w('>');
   },
   VectorDeclaration: function (out) {
      out.w(this.name.id);
      if (this.params !== undefined) {
         this.params.prettyPrint(out);
      }
   },
   VectorDeclarationStatement: function (out) {
      this.type.prettyPrint(out);
      out.w(' ');
      var i = 0;
      this.forEachChild(function (child) {
         if (i != 0) { out.w(", "); }
         child.prettyPrint(out);
         i++;
      });
      out.p(";");
   },
   ArrayReference: function (out) {
      out.w(this.name.id + "[");
      this.index.prettyPrint(out);
      out.w("]");
   },
   FunctionCall: function (out) {
      out.w(this.name.id);
      this.args.prettyPrint(out);
      out.p(";");
   },
});

