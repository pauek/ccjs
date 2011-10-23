
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
   FunctionDefinition: function (out) {
      out.p();
      this.type.prettyPrint(out);
      out.w(" " + this.name.id);
      out.w("(");
      if (this.params !== undefined) {
         for (var i = 0; i < this.params.length; i++) {
            if (i != 0) out.w(", ");
            this.params[i].prettyPrint(out);
         }
      }
      out.p(") {");
      out.i(+1);
      this.nextMethod(out);
      out.i(-1);
      out.p("}");
   },
   FormalParameter: function (out) {
      this.type.prettyPrint(out);
      if (this.ref) out.w("&");
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
   InputExpression: function (out) {
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
   UnaryExpression: function (out) {
      out.w(this.operator);
      this.right.prettyPrint(out);
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
	ConditionalBlock: function (out) {
		if (this.cond !== undefined) {
			out.w("if (");
			this.cond.prettyPrint(out);
			out.w(") ")
		}
		out.p("{");
		out.i(+1);
		this.nextMethod(out);
		out.i(-1);
		out.w("}");
	},
	IfElseIfStatement: function (out) {
		var i = 0;
		this.forEachChild(function (child) {
			if (i != 0) out.w(" else ");
			child.prettyPrint(out);
			i++;
		});
		out.p();
	},
   SwitchCase: function (out) {
      if (this.expr === undefined) {
         out.p("default:");
      } else {
         out.w("case ");
         this.expr.prettyPrint(out);
         out.p(":");
      }
      out.i(+1);
      this.forEachChild(function (child) {
         child.prettyPrint(out);
      });
      out.i(-1);
   },
   SwitchStatement: function (out) {
      out.w("switch (");
      this.expr.prettyPrint(out);
      out.p(") {");
      this.nextMethod(out);
      out.p("}");
   },
   ForStatement: function (out) {
      out.w("for (");
      if (this.init !== undefined) {
         this.init.prettyPrint(out);
      }
      out.w("; ");
      this.cond.prettyPrint(out);
      out.w("; ");
      if (this.incr !== undefined) {
         this.incr.prettyPrint(out);
      }
      out.p(") {");
      out.i(+1);
      this.nextMethod(out);
      out.i(-1);
      out.p("}");
   },
   ReturnStatement: function (out) {
      out.w("return ");
      this.expr.prettyPrint(out);
      out.p(";");
   },
   PostfixExpression: function (out) {
      this.left.prettyPrint(out);
      out.w(this.operator);
   },
   BinaryExpression: function (out) {
      out.w("(");
      this.left.prettyPrint(out);
      out.w(" " + this.operator + " ");
      this.right.prettyPrint(out);
      out.w(")");
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
   FloatLiteral: function (out) {
      out.w('' + this.lit);
   },
   StringLiteral: function (out) {
      out.w('"' + this.lit + '"');
   },
   CharLiteral: function (out) {
      out.w("'" + this.lit + "'");
   },
   Type: function (out) {
      if (this.konst) {
         out.w("const ");
      }
      out.w(this.name);
   },
   ArrayTypedefDeclaration: function (out) {
      out.w("typedef ");
      this.type.prettyPrint(out);
      out.w(" " + this.name.id + "[");
      this.size.prettyPrint(out);
      out.p("];");
   },
   StructDeclaration: function (out) {
      out.p();
      out.p("struct " + this.name.id + " {");
      out.i(+1);
      this.nextMethod(out);
      out.i(-1);
      out.p("};");
      
   },
   ArrayDeclaration: function (out) {
      out.w(this.name.id);
      out.w("[");
      this.size.prettyPrint(out);
      out.w("]");
      if (this.init !== undefined) {
         out.w(" = { ");
         for (var i = 0; i < this.init.length; i++) {
            if (i != 0) {
               out.w(", ");
            }
            this.init[i].prettyPrint(out);
         }
         out.w(" }");
      }
   },
   VariableDeclaration: function (out) {
      out.w(this.name.id);
      if (this.value !== undefined) {
         out.w(" = ");
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
   MemberAccess: function (out) {
      var i = 0;
      this.forEachChild(function (child) {
         if (i != 0) out.w(".");
         child.prettyPrint(out);
         i++;
      });
   },
   VariableReference: function (out) {
      out.w(this.name.id);
   },
   VectorType: function (out) {
      if (this.konst) out.w("const ");
      out.w('vector<');
      this.subtype.prettyPrint(out);
      out.w('>');
      if (this.ref) out.w("&");
   },
   VectorCopyConstructor: function (out) {
      out.w(this.name.id + " = ");
      this.init.prettyPrint(out);
   },
   VectorConstructor: function (out) {
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
   CallExpression: function (out) {
      out.w(this.name.id);
      this.args.prettyPrint(out);
   },
   CallStatement: function (out) {
      this.call.prettyPrint(out);
      out.p(";");
   },
   MethodCall: function (out) {
      out.w(this.obj.id + "." + this.method.id);
      this.args.prettyPrint(out);
   }
});

