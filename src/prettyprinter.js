
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
   Identifier: function (out) {
      out.w(this.id);
   },
   OutputStatement: function (out) {
      out.w(this.head);
      this.nextMethod(out);
      out.p(";");
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
});

