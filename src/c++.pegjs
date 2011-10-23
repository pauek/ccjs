
start = 
   __ program:Program __ { return program; }

WhiteSpace = [ \t\f]
LineTerminator = [\n\r]
LineTerminatorSeq = "\n" / "\r\n" / "\r"
SourceCharacter = .

__ =
   (WhiteSpace / LineTerminatorSeq / Comment)*

_ =
   (WhiteSpace / MultiLineCommentOneLine / SingleLineComment)*

MultiLineComment =
   "/*" (!"*/" SourceCharacter)* "*/"

MultiLineCommentOneLine = 
   "/*" (!("*/" / LineTerminator) SourceCharacter)* "*/"

SingleLineComment =
   "//" (!LineTerminator SourceCharacter)*

Comment =
   MultiLineComment /
   SingleLineComment

IdentifierPart = 
   IdentifierStart

IdentifierStart = [_A-Za-z]
IdentifierRest  = [_A-Za-z0-9]

Operator = "--" / "++" / "()" / "[]" / "." / "->" /
   "+" / "-" / "!" / "~" / "*" / "new" /
   ".*" / "->*" / 
   "*" / "%" / "/" /
   "<<" / ">>" /
   "<" / ">" / "<=" / ">=" /
   "==" / "!=" / "&" / "|" / "^" / "&&" / "||" / "=" /
   "+=" / "-=" / "*=" / "/=" / "%=" / ">>=" / "<<=" / "&=" / "^=" / "|=" / 
   ","

OperatorName = 
   "operator" __ op:Operator {
      return "operator" + op;
   }

FullIdentifier = 
   start:IdentifierStart rest:IdentifierRest* {
      return start + rest.join('');
   }

Identifier = 
   prefix:(FullIdentifier __ "::" __)* name:(OperatorName / FullIdentifier) {
      var id = { id: name };
      if (prefix !== "") { 
         id.prefix = [];
         for (var i in prefix) { 
            id.prefix.push(prefix[i][0]); 
         }
      }
      return new ast.Identifier(id);
   }

DecimalIntegerLiteral = 
   "0" { return 0; } /
   sign:"-"? head:NonZeroDigit tail:DecimalDigits? { 
      return parseInt(sign + head + tail);
   }

DecimalDigits
  = digits:DecimalDigit+ { return digits.join(""); }

DecimalDigit = [0-9]
NonZeroDigit = [1-9]

SignedInteger = 
   sign:[-+]? digits:DecimalDigits {
      return sign + digits;
   }

FloatLiteral = 
   before:DecimalIntegerLiteral "." after:DecimalDigits? exponent:ExponentPart? {
      return parseFloat(before + "." + after + exponent);
   } /
   "." after:DecimalDigits? exponent:ExponentPart? {
      return parseFloat("." + after + exponent);
   } /
   before:DecimalIntegerLiteral exponent:ExponentPart? {
      return parseFloat(before + exponent);
   }

ExponentPart =
   indicator:[eE] integer:SignedInteger {
      return indicatr + integer;
   }

Literal = 
   lit:FloatLiteral {
      return new ast.FloatLiteral({ lit: lit });
   } /
   lit:DecimalIntegerLiteral {
      return new ast.IntegerLiteral({ lit: lit }); 
   } /
   CharLiteral /
   StringLiteral

CharLiteral =
   "'" lit:QuotedCharacter "'" {
      return new ast.CharLiteral({ lit: lit });
   }

StringLiteral = 
   '"' chars:StringCharacter* '"' {
      return new ast.StringLiteral({ lit: chars.join("") });
   }

QuotedCharacter = 
   !('"' / "\\" / LineTerminator) char_:SourceCharacter { return char_; } / 
   "\\" sequence:EscapeSequence { return sequence; }

StringCharacter = 
   QuotedCharacter /
   LineContinuation

EscapeSequence = 
   CharacterEscapeSequence / 
   "0" !DecimalDigit { return "\0"; }

CharacterEscapeSequence = 
  SingleEscapeCharacter / 
  NonEscapeCharacter

SingleEscapeCharacter = 
  char_:['"\\bfnrtv] {
      return char_
        .replace("b", "\b")
        .replace("f", "\f")
        .replace("n", "\n")
        .replace("r", "\r")
        .replace("t", "\t")
        .replace("v", "\x0B") // IE does not recognize "\v".
    }

NonEscapeCharacter = 
   (!EscapeCharacter / LineTerminator) char_:SourceCharacter { 
      return char_; 
   }

EscapeCharacter = 
   SingleEscapeCharacter / 
   DecimalDigit

LineContinuation
  = "\\" sequence:LineTerminatorSequence { return sequence; }

LineTerminatorSequence = "\n" / "\r\n" / "\r"

BasicTypeName = "bool" / "int" / "string" / "char" / "float" / "double" / "void"

BasicType = type:BasicTypeName !IdentifierPart { return type; }

Type = 
   konst:("const" __)? name:(
      IteratorType /
      BasicType / 
      ContainerType /
      id:Identifier { return id.id; }
   ) 
   ref:(__ "&")?
   ptr:(__ "*")?
   !(__ ":" / __ "(") {
     return new ast.Type({ 
        name: name, 
        konst: (konst !== ""),
        ref: (ref !== ""),
        pointer: (ptr !== ""),
     });
   }

ArrayTypedefDeclaration = 
   "typedef" __ type:Type __ decl:ArrayDeclarationNoInit ";" {
      return new ast.ArrayTypedefDeclaration({ 
         type: type, 
         name: decl.name, 
         size: decl.size 
      });
   }

StructDeclaration =
   "struct" __ name:Identifier __ "{" __
      first:VariableDeclarationStatement 
      rest:(__ VariableDeclarationStatement)* __
   "}" __ ";" {
      var fields = [first];
      for (var i = 0; i < rest.length; i++) {
         fields.push(rest[i][1]);
      }
      return new ast.StructDeclaration({ name: name }, fields);
   }

PrimaryExpression =
   MethodCallExpression /
   NewCallExpression /
   CallExpression /
   Literal /
   ReferenceExpression /
   ConditionalExpression /
   "(" __ expr:Expression __ ")" { return expr; }

ReferenceExpression =
   AccessExpression /
   VariableReference 

PostfixExpression = 
   left:ReferenceExpression _ operator:PostfixOperator {
      return new ast.PostfixExpression({
        left:     left,
        operator: operator,
      });
    } / 
    PrimaryExpression

PostfixOperator = "++" / "--"

UnaryExpression = 
  PostfixExpression / 
  operator:UnaryOperator __ right:UnaryExpression {
     return new ast.UnaryExpression({ 
        operator: operator, 
        right: right 
     });
  }

UnaryOperator = "++" / "--" / "+" / "-" / "~" / "!" / "*"

MultiplicativeOperator
  = operator:("*" / "/" / "%") !"=" { return operator; }

MultiplicativeExpression =
   head:UnaryExpression
   tail:(__ MultiplicativeOperator __ PrimaryExpression)* {
      var result = head;
      for (var i = 0; i < tail.length; i++) {
         result = new ast.BinaryExpression({
            left:     result,
            operator: tail[i][1],
            right:    tail[i][3],
         });
      }
      return result;
   } /
   PrimaryExpression

AdditiveOperator = 
  "+" !("+" / "=") { return "+"; } / 
  "-" !("-" / "=") { return "-"; }

AdditiveExpression =
   head:MultiplicativeExpression
   tail:(__ AdditiveOperator __ MultiplicativeExpression)* {
      var result = head;
      for (var i = 0; i < tail.length; i++) {
         result = new ast.BinaryExpression({
            left:     result,
            operator: tail[i][1],
            right:    tail[i][3],
         });
      }
      return result;
   } /
   MultiplicativeExpression

ComparisonOperator = "==" / "!=" / "<=" / ">=" / ">" / "<"

ComparisonExpression =
   left:AdditiveExpression __ 
   operator:ComparisonOperator __ 
   right:AdditiveExpression {
      return new ast.BinaryExpression({ 
         left: left, 
         operator: operator, 
         right: right 
      });
   } /
   InputExpression /
   AdditiveExpression

AssignmentOperator = "+=" / "*=" / "/=" / "-=" / "%=" / "=" 

LogicalANDExpression =
   head:ComparisonExpression tail:(__ "&&" __ ComparisonExpression)+ {
      var result = [head];
      for (var i = 0; i < tail.length; i++) {
         result.push(tail[i][3]);
      }
      return new ast.LogicalANDExpression({}, result);
   } /
   ComparisonExpression

LogicalORExpression =
   head:LogicalANDExpression tail:(__ "||" __ LogicalANDExpression)+ {
      var result = [head];
      for (var i = 0; i < tail.length; i++) {
         result.push(tail[i][3]);
      }
      return new ast.LogicalORExpression({}, result);
   } /
   LogicalANDExpression

Condition = 
   LogicalORExpression

AssignmentExpression =
   lvalue:ReferenceExpression __ 
   operator:AssignmentOperator __ 
   rvalue:AssignmentExpression {
      return new ast.AssignmentExpression({ 
         lvalue:   lvalue, 
         operator: operator, 
         rvalue:   rvalue 
      });
   } /
   Condition

CommaExpression =
   first:AssignmentExpression rest:(__ "," __ AssignmentExpression)+ {
      var result = [first];
      for (var i in rest) {
         result.push(rest[i][3]);
      }
      return new ast.CommaExpression({}, result);
   } /
   AssignmentExpression

Expression =
   AssignmentExpression

VariableReference =
   name:Identifier { 
      return new ast.VariableReference({ name: name }); 
   }

SingleAccess = 
   "." __ member:Identifier {
      return new ast.MemberAccess({ member: member });
   } /
   "[" __ index:Expression __ "]" {
      return new ast.ArrayAccess({ index: index });
   } /
   "->" __ member:Identifier {
      return new ast.PointerAccess({ member: member });
   }

AccessExpression =
   head:Identifier rest:(__ SingleAccess)+ {
      var accesses = [];
      for (var i in rest) {
         accesses.push(rest[i][1]);
      }
      return new ast.AccessExpression({ head: head }, accesses);
   }

FormalParameter =
   type:Type __ name:Identifier array:(__ ArraySizes)? {
      var param = {
         type: type, 
         name: name, 
      }
      if (array !== "") {
         param.array = array[1];
      }
      return new ast.FormalParameter(param);
   }

FormalParameterList =
   head:FormalParameter tail:(__ "," __ FormalParameter)* {
      var result = [head];
      for (var i = 0; i < tail.length; i++) {
         result.push(tail[i][3]);
      }
      return result;
   } /
   "void" { return []; }

SingleVariableDeclaration =
   name:Identifier value:(__ "=" __ Expression)? {
      var result = { name: name };
      if (typeof value[3] != 'undefined') {
         result.value = value[3];
      }
      return new ast.SingleVariableDeclaration(result);
   }

ArrayInitialization = 
   "{" __ first:Expression rest:(__ "," __ Expression)* __ "}" {
      var result = [first];
      for (var i = 0; i < rest.length; i++) {
         result.push(rest[i][3]);
      }
      return result;
   }

ArraySizes =
   "[" __ size1:(Expression __)? "]" othersizes:(__ "[" __ Expression __ "]")* {
      var sizes = [(size1 !== "" ? size1 : null)];
      for (var i in othersizes) {
         sizes.push(othersizes[i][3]);
      }
      return sizes;
   }

ArrayDeclarationNoInit =
   name:Identifier __ sizes:ArraySizes {
      return { name: name, sizes: sizes };
   }

ArrayDeclaration =
   decl:ArrayDeclarationNoInit init:(__ "=" __ ArrayInitialization)? {
      var result = { name: decl.name, size: decl.size };
      if (init != "") {
         result.init = init[3];
      }
      return new ast.ArrayDeclaration(result);
   }

NewCallExpression =
   "new" __ call:ConstructorCall {
      return new ast.NewCallExpression({ klass: call.name, args: call.args });
   } /
   "new" __ klass:Identifier {
      return new ast.NewCallExpression({ klass: klass });
   }

ConstructorCall =
   name:Identifier __ args:ActualParameterList {
      return new ast.ConstructorCall({ name: name, args: args });
   }

OneVariableDeclaration =
   ArrayDeclaration /
   ConstructorCall /
   SingleVariableDeclaration

VariableDeclarationList =
   head:OneVariableDeclaration tail:(__ "," __ OneVariableDeclaration)* {
      var result = [head];
      for (var i = 0; i < tail.length; i++) {
         result.push(tail[i][3]);
      }
      return result;
   }

VariableDeclaration =
   type:Type __ lst:VariableDeclarationList {
      return new ast.VariableDeclaration({ type: type }, lst);
   }

VariableDeclarationStatement =
   decl:VariableDeclaration __ ";" {
      return new ast.VariableDeclarationStatement({ decl: decl });
   }

ExpressionList = 
  head:Expression tail:(__ "," __ Expression)* {
     var result = [head];
     for (var i = 0; i < tail.length; i++) {
        result.push(tail[i][3]);
     }  
     return result;
  }

ActualParameterList =
  "(" __ lst:ExpressionList? __ ")" {
     return new ast.ActualParameterList({}, lst);
  }

VectorType =
   ("std" __ "::" __)? 
   "vector" __ "<" __ subtype:Type __ ">" {
      return new ast.VectorType({ 
         subtype: subtype, 
      });
   }

ListType =
   ("std" __ "::" __)? 
   "list" __ "<" __ subtype:Type __ ">" {
      return new ast.ListType({ 
         subtype: subtype, 
      });
   }

MapType =
   ("std" __ "::" __)? 
   "map" __ "<" __ key:Type __ "," __ value:Type __ ">" {
      return new ast.MapType({
         key: key,
         value: value,
      });
   }

ContainerType = 
   VectorType /
   ListType /
   MapType

IteratorType =
   container:(
     ContainerType /
     "string" { 
        return new ast.Type({ name: "string" }); 
     }
   ) __ "::" __ 
   konst:("const_")? reverse:("reverse_")? "iterator" {
      return new ast.IteratorType({ 
         container: container,
         konst: (konst !== ""),
         reverse: (reverse !== ""),
      });
   }

OutputStatement =
   head:Identifier elems:(__ "<<" __ Expression)* __ ";" {
      var elements = [];
      for (var i = 0; i < elems.length; i++) {
         elements.push(elems[i][3]);
      }
      return new ast.OutputStatement({ head: head }, elements);
   }

InputExpression =
   head:Identifier elems:(__ ">>" __ ReferenceExpression)+ {
      var elements = [];
      for (var i = 0; i < elems.length; i++) {
         elements.push(elems[i][3]);
      }
      return new ast.InputExpression({ head: head }, elements);
   }

ExpressionStatement =
   expr:CommaExpression __ ";" {
      return new ast.ExpressionStatement({ head: expr.head }, expr.children());
   }

DeclarationStatement =
   VariableDeclarationStatement

Statement =
   DeclarationStatement /
   ReturnStatement /
   SwitchStatement /
	IfElseIfStatement /
	IfElseStatement /
   IfStatement /
   WhileStatement /
   ForStatement /
   CallStatement /
   AssignmentStatement /
   ExpressionStatement /
   OutputStatement

AssignmentStatement = 
   expr:AssignmentExpression __ ";" {
      return new ast.AssignmentStatement({ expr: expr });
   }

ParenthesizedCondition =
   "(" __ cond:Condition __ ")" {
	   return cond;
   }

WhileStatement =
   "while" __ cond:ParenthesizedCondition __ body:StatementBlock {
      return new ast.WhileStatement({ cond: cond }, body);
   }

ForInitialization =
   VariableDeclaration /
   AssignmentExpression

ForStatement =
   "for" __ "(" __ 
   init:(ForInitialization __)? ";" __ 
   cond:Condition __ ";" __ 
   incr:(CommaExpression __)? ")" __ 
   body:StatementBlock {
      var result = { cond: cond };
      if (init !== "") result.init = init[0];
      if (incr !== "") result.incr = incr[0];
      return new ast.ForStatement(result, body);
   }


IfStatement =
   "if" __ cond:ParenthesizedCondition __ body:StatementBlock {
      return new ast.IfStatement({ cond: cond }, body);
   }

IfElseStatement =
   "if" __ cond:ParenthesizedCondition __ then:StatementBlock __ 
	"else" __ elze:StatementBlock {
	   return new ast.IfElseStatement({ cond: cond, then: then, elze: elze });
   }

NoParensConditionalExpression =
   cond:Condition __ "?" __ 
   then:Expression __ ":" __ 
   elze:Expression {
      return new ast.ConditionalExpression({ 
         cond: cond, 
         then: then, 
         elze: elze 
      });
   }

ConditionalExpression =
   "(" __ expr:NoParensConditionalExpression __ ")" {
     return expr;
   }

ConditionalBlock =
   cond:ParenthesizedCondition __ body:StatementBlock {
	   return new ast.ConditionalBlock({ cond: cond  }, body);
   }

IfElseIfStatement =
   "if" __ first:ConditionalBlock
   rest:(__ "else" __ "if" __ ConditionalBlock)+
	last:(__ "else" __ StatementBlock)? {
	   var blocks = [first];
		for (var i = 0; i < rest.length; i++) {
		   blocks.push(rest[i][5]);
      }
		if (last !== undefined) {
		   blocks.push(new ast.ConditionalBlock({}, last[3]));
      }
		return new ast.IfElseIfStatement({}, blocks);
   }

SwitchCase =
   "case" __ expr:Expression __ ":" body:(__ StatementList)? {
      return new ast.SwitchCase({ expr: expr }, body[1]);
   } /
   "default" __ ":" __ body:StatementList {
      return new ast.SwitchCase({}, body);
   }

SwitchStatement =
   "switch" __ "(" __ expr:Expression __ ")" __ "{"
   _cases:(__ SwitchCase)+ __ 
   "}" {
      var cases = [];
      for (var i = 0; i < _cases.length; i++) {
         cases.push(_cases[i][1]);
      }
      return new ast.SwitchStatement({ expr: expr }, cases);
   }

StatementBlock =
   "{" lst:(__ lst:StatementList)? __ "}" {
      return (lst !== "" ? lst[1] : []);
   } /
   stmt:Statement {
      return [stmt];
   }

AloneStatementBlock =
   block:StatementBlock {
      return new ast.AloneStatementBlock({}, block);
   }

StatementList =
   head:(Statement / AloneStatementBlock) 
   tail:(__ (Statement / AloneStatementBlock))* {
      var result = [head];
      for (var i = 0; i < tail.length; i++) {
         result.push(tail[i][1]);
      }
      return result;
   }

MethodCallExpression =
   access:AccessExpression __ args:ActualParameterList {
      return new ast.MethodCall({ access: access, args: args });
   }

CallExpression = 
   name:Identifier __ args:ActualParameterList {
      return new ast.CallExpression({ name: name, args: args });
   }

CallStatement =
   call:(CallExpression / MethodCallExpression) __ ";" {
      return new ast.CallStatement({ call: call });
   }

ReturnStatement =
   "return" __ expr:(NoParensConditionalExpression / Expression) __ ";" {
      return new ast.ReturnStatement({ expr: expr });
   }


FunctionHeaderNoType =
   name:Identifier __ 
   "(" __ params:FormalParameterList? __ ")" {
      var header = { name: name };
      if (params !== '') {
         header.params = params
      }
      return header;
   }

FunctionHeader =
   type:Type __ header:FunctionHeaderNoType {
      header.type = type;
      return header;
   }

FunctionDefinition =
   inline:("inline" __)? header:FunctionHeader __ body:StatementBlock {
      header.inline = (inline !== "");
      return new ast.FunctionDefinition(header, body);
   }

FunctionDeclaration =
   header:FunctionHeader __ ";" {
      return new ast.FunctionDeclaration(header);
   }

IncludeDirective =
  "#include" _ [<"] file:[_A-Za-z0-9.]* [>"] {
     return new ast.IncludeDirective({ file: file.join('') });
  }

UsingDirective =
  UsingSymbolDirective /
  UsingNamespaceDirective

UsingSymbolDirective =
   "using" __ sym:Identifier __ ";" {
      return new ast.UsingDirective({ symbol: sym });
   }

UsingNamespaceDirective =
   "using" __ "namespace" __ ns:Identifier __ ";" {
      return new ast.UsingDirective({ namespace: ns });
   }

AccessMode = "public" / "private" / "protected"

ClassLabel = 
   label:AccessMode ":" { 
      return label; 
   }

AttributeDeclaration = 
   VariableDeclarationStatement

MethodDeclaration =
   virtual:("virtual" __)? 
   header:(FunctionHeader / FunctionHeaderNoType) konst:(__ "const")? __ ";" {
      header.virtual = (virtual !== "");
      header.konst = (konst !== "");
      return new ast.MethodDeclaration(header);
   }   

InlineMethod =
   header:FunctionHeader __ konst:(__ "const")? __ body:StatementBlock  {
      header.inline = true;
      header.konst = (konst !== "");
      return new ast.MethodDefinition(header, body);
   }

ClassPart =
   ClassLabel /
   InlineMethod /
   MethodDeclaration /
   AttributeDeclaration
  
ClassDeclaration =
  "class" __ name:Identifier __ 
  base:(
     ":" __ mode:AccessMode __ name:Identifier __ { 
        return { mode: mode, name: name };
     }
  )?
  "{" parts:(__ ClassPart)* __ "}" __ ";" {
     var members = [];
     var access = "private";
     for (var i in parts) {
        if (typeof parts[i][1] === "string") {
           access = parts[i][1];
        } else {
           var member = parts[i][1];
           if (access == "private") {
              member.private = true;
           } else if (access == "protected") {
              member.protected = true;
           } else {
              member.public = true;
           }
           members.push(member);
        }
     }
     var klass = { name: name };
     if (base !== "") {
        klass.base = base;
     }
     return new ast.ClassDeclaration(klass, members);
  }

MethodInitialization =
   ":" init:(__ ConstructorCall)+ {
      var result = []
      for (var i in init) {
         result.push(init[i][1]);
      }
      return new ast.MethodInitialization({}, result);
   }

MethodDefinition =
   inline:("inline" __)?
   type:(Type __)?
   header:FunctionHeaderNoType __ konst:(__ "const")? __ 
   initialization:MethodInitialization? __
   body:StatementBlock  {
      if (type !== "") {
         header.type = type[0];
      }
      if (initialization !== "") {
         header.initialization = initialization;
      }
      header.inline = (inline !== "");
      header.konst = (konst !== "");
      return new ast.MethodDefinition(header, body);
   }

ProgramPart =
  IncludeDirective /
  UsingDirective /
  ClassDeclaration /
  MethodDefinition /
  FunctionDeclaration /
  FunctionDefinition /
  StructDeclaration /
  ArrayTypedefDeclaration /
  VariableDeclarationStatement /
  Comment

Program = 
   head:ProgramPart tail:(__ ProgramPart)* {
      var parts = [head];
      for (var i = 0; i < tail.length; i++) {
         parts.push(tail[i][1]);
      }  
      return new ast.Program({}, parts);
   }
