
Environment = function (parent) {
   this.tab = {};
   this.parent = parent;
}

Environment.prototype = {
   lookup: function (name) {
      var curr = this;
      while (curr != null) {
         if (name in curr.tab) {
            return curr.tab[name];
         }
         curr = curr.parent;
      }
      return undefined;
   },
   set: function (name, value) {
      this.tab[name] = value;
   }
}

ast.EnvBuilder = function () {
   this.global_env = new Environment();
}

ast.EnvBuilder.prototype = {
   enterFunctionDef: function (obj) {
      this.global_env.set(obj.name.id, obj);
   },
   enterIncludeDirective: function (obj) {
      if (obj.file === 'iostream') {
         this.global_env.set('cout', process.stdout);
         this.global_env.set('cin', process.stdin);
         this.global_env.set('endl', '\n');
      }
   },
}

ast.Evaluator = function (env, stdin, stdout) {
   this.env = env;
   this.stdin = stdin;
   this.stdout = stdout;
}

ast.Evaluator.prototype = {
   run: function () {
      this.env.lookup('main').visit(this);
   },
   visitFunctionDef: function (obj) {
      this.env = new Environment(this.env);
      var visitor = this;
      obj.forEachChild(function (child) {
         child.visit(visitor);
      });
      this.env = this.env.parent;
      if (!('returned' in this.env)) {
         this.env.result = 0;
      }
   },
   visitOutputStatement: function (obj) {
      var self = this;
      var out = this.env.lookup(obj.head);
      obj.forEachChild(function (child) {
         var value = child.expr.visit(self);
         out.write('' + value);
      });
   },
   visitStringLiteral: function (obj) {
      return obj.lit;
   },
   visitVariableReference: function (obj) {
      var value = this.env.lookup(obj.name.id);
      if (value === undefined) {
         throw Error("undefined variable '" + obj.name.id + "'");
      } 
      return value;
   },
   visitVariableDeclarationStatement: function (obj) {
      var self = this;
      obj.forEachChild(function (vardecl) {
         self.env.set(vardecl.name.id, vardecl.value);
      });
   },
}

function interpret(program) {
   var builder = new ast.EnvBuilder();
   program.walk(builder);
   var evaluator = new ast.Evaluator(builder.global_env);
   evaluator.run();
   process.exit(evaluator.env.result);
}