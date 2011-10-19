
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
      out.w(this.type + " " + this.name.id);
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
   Identifier: function (out) {
      out.w(this.id);
   },
   OutputStatement: function (out) {
      out.w(this.head);
      this.nextMethod(out);
      out.p(";");
   },
   OutputElement: function (out) {
      out.w(" << ");
      this.expr.prettyPrint(out);
   },
   StringLiteral: function (out) {
      out.w('"' + this.lit + '"');
   },
   VariableReference: function (out) {
      out.w(this.name.id);
   },
});

