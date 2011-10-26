{
        
function collect(head, tail, n) {
   var k = (n === undefined ? 0 : n);
   var result = [];
   if (head !== null) {
      result.push(head);
   }
   for (var i in tail) {
      result.push(tail[i][k]);
   }
   return result;
}

function inspect(prefix, obj) {
   var msg = "";
   if (prefix !== undefined) { 
      msg = prefix + ": ";
   }
   msg += util.inspect(obj, false, null);
   console.log(msg);
}

}

start = 
   __ program:Program __ { return program; }


/************ WhiteSpace and Comments ************/

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


/************ Keywords and Operators ************/

KeyWord = 
   "and" / "and_eq" / "alignas" / "alignof" / "asm" / "auto" / 
   "bitand" / "bitor" / "bool" / "break" / "case" / "catch" / "char" / 
   "char16_t" / "char32_t" / "class" / "compl" / "const" / "constexpr" / 
   "const_cast" / "continue" / "decltype" / "default" / "delete" / "double" / 
   "dynamic_cast" / "else" / "enum" / "explicit" / "export" / "extern" / 
   "false" / "float" / "for" / "friend" / "goto" / "if" / "inline" / "int" / 
   "long" / "mutable" / "namespace" / "new" / "noexcept" / "not" / "not_eq" /
   "nullptr" / "operator" / "or" / "or_eq" / "private" / "protected" / "public" / 
   "register" / "reinterpret_cast" / "return" / "short" / "signed" / "sizeof" / 
   "static" / "static_assert" / "static_cast" / "struct" / "switch" / "template" / 
   "this" / "thread_local" / "throw" / "true" / "try" / "typedef" / "typeid" / 
   "typename" / "union" / "unsigned" / "using" / "virtual" / "void" / "volatile" / 
   "wchar_t" / "while" / "xor" / "xor_eq"

Operator = "+=" / "-=" / "*=" / "/=" / "%=" / ">>=" / "<<=" / "&=" / "^=" / "|=" / 
   "+" / "-" / "!" / "~" / "*" / "new" /
   ".*" / "->*" / 
   "*" / "%" / "/" /
   "<<" / ">>" /
   "<" / ">" / "<=" / ">=" /
   "==" / "!=" / "&" / "|" / "^" / "&&" / "||" / "=" /
   "," / "--" / "++" / "()" / "[]" / "." / "->" /


/************ Literals ************/

DecimalDigits
  = digits:DecimalDigit+ { return digits.join(""); }

DecimalDigit = [0-9]
NonZeroDigit = [1-9]

SignedInteger = 
   sign:[-+]? digits:DecimalDigits {
      return sign + digits;
   }

DecimalIntegerLiteral = 
   "0" { return 0; } /
   sign:"-"? head:NonZeroDigit tail:DecimalDigits? { 
      return parseInt(sign + head + tail);
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
   lit:BooleanLiteral {
      return new ast.BooleanLiteral({ lit: lit });
   } /
   CharLiteral /
   StringLiteral

BooleanLiteral = "true" / "false"

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


/************ Identifiers ************/

IdentifierStart = [_A-Za-z]
IdentifierRest  = [_A-Za-z0-9]

FullIdentifier = 
   !(KeyWord (WhiteSpace / LineTerminatorSeq / Comment))
   start:IdentifierStart rest:IdentifierRest* {
      return start + rest.join('');
   }

OperatorName = 
   "operator" __ op:Operator {
      return "operator" + op;
   }

Identifier = 
   prefix:(FullIdentifier __ "::" __)* name:(OperatorName / FullIdentifier) {
      var id = { id: name };
      if (prefix !== "") { 
         id.prefix = collect(null, prefix, 0);
      }
      return new ast.Identifier(id);
   }

/***************** Types ******************/

BasicTypeName = "bool" / "int" / "string" / "long" / "char" / "float" / "double" / "void"

BasicType = type:BasicTypeName !IdentifierStart { return type; }

Type = 
   ztatic:("static" __)?
   konst:("const" __)? 
   name:(
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
        ztatic: (ztatic !== ""),
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

PairType =
   ("std" __ "::" __)? 
   "pair" __ "<" __ first:Type __ "," __ second:Type __ ">" {
      return new ast.PairType({
         first: first,
         second: second,
      });
   }

MapType =
   ("std" __ "::" __)? 
   multi:("multi")? "map" __ "<" __ key:Type __ "," __ value:Type __ ">" {
      return new ast.MapType({
         key: key,
         value: value,
         multimap: (multi !== ""),
      });
   }

ContainerType = 
   VectorType /
   ListType /
   PairType /
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


/******************** Expressions ********************/

PrimaryExpression =
   ConversionExpression /
   NewExpression /
   ReferenceExpression /
   ConditionalExpression /
   Literal /
   "(" __ expr:Expression __ ")" { return expr; }

ConversionExpression =
   type:Type __ "(" __ expr:PrimaryExpression __ ")" {
      return new ast.ConversionExpression({ type: type, expr: expr });
   }

ReferenceExpression =
   AccessExpression

DirectReferenceExpression =
   CallExpression /
   VariableReference /
   "(" __ expr:Expression __ ")" { return expr; }

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

UnaryOperator = "++" / "--" / "+" / "-" / "~" / "!" / "*" / "&"

MultiplicativeOperator
  = operator:("*" / "/" / "%") !"=" { return operator; }

MultiplicativeExpression =
   head:UnaryExpression
   tail:(__ MultiplicativeOperator __ PrimaryExpression)* {
      var result = head;
      for (var i in tail) {
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
      for (var i in tail) {
         result = new ast.BinaryExpression({
            left:     result,
            operator: tail[i][1],
            right:    tail[i][3],
         });
      }
      return result;
   } /
   MultiplicativeExpression

RelationalOperator = "<=" / ">=" / ">" / "<"

RelationalExpression =
   left:AdditiveExpression __ 
   operator:RelationalOperator __ 
   right:AdditiveExpression {
      return new ast.BinaryExpression({ 
         left: left, 
         operator: operator, 
         right: right 
      });
   } /
   InputExpression /
   AdditiveExpression

EqualityOperator = "==" / "!="

EqualityExpression =
   left:RelationalExpression __ 
   operator:EqualityOperator __ 
   right:RelationalExpression {
      return new ast.BinaryExpression({ 
         left: left, 
         operator: operator, 
         right: right 
      });
   } /
   RelationalExpression

BitwiseANDExpression =
   head:EqualityExpression tail:(__ "&" __ EqualityExpression)+ {
      return new ast.BitwiseANDExpression({}, collect(head, tail, 3));
   } /
   EqualityExpression

BitwiseExclusiveORExpression =
   head:BitwiseANDExpression tail:(__ "&" __ BitwiseANDExpression)+ {
      return new ast.BitwiseExclusiveORExpression({}, collect(head, tail, 3));
   } /
   BitwiseANDExpression

BitwiseORExpression =
   head:BitwiseExclusiveORExpression tail:(__ "&" __ BitwiseExclusiveORExpression)+ {
      return new ast.BitwiseORExpression({}, collect(head, tail, 3));
   } /
   BitwiseExclusiveORExpression

LogicalANDExpression =
   head:BitwiseORExpression tail:(__ ("and" / "&&") __ BitwiseORExpression)+ {
      return new ast.LogicalANDExpression({}, collect(head, tail, 3));
   } /
   BitwiseORExpression

LogicalORExpression =
   head:LogicalANDExpression tail:(__ ("or" / "||") __ LogicalANDExpression)+ {
      return new ast.LogicalORExpression({}, collect(head, tail, 3));
   } /
   LogicalANDExpression

Condition = 
   LogicalORExpression

AssignmentOperator = "+=" / "*=" / "/=" / "-=" / "%=" / "=" 

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
      return new ast.CommaExpression({}, collect(first, rest, 3));
   } /
   AssignmentExpression

Expression =
   CommaExpression

VariableReference =
   name:Identifier { 
      return new ast.VariableReference({ name: name }); 
   }

SingleAccess = 
   "[" __ index:Expression __ "]" {
      return new ast.ArrayAccess({ index: index });
   } /
   "." __ id:Identifier args:(__ ActualParameterList)? {
      if (args !== "") {
         return new ast.MethodCall({ method: id, args: args });
      } else {
         return new ast.MemberAccess({ member: id });
      }
   } /
   "->" __ id:Identifier args:(__ ActualParameterList)? {
      if (args !== "") {
         return new ast.PtrMethodCall({ method: id, args: args });
      } else {
         return new ast.PtrMemberAccess({ member: id });
      }
   }

AccessExpression =
   head:DirectReferenceExpression rest:(__ SingleAccess)* {
      var curr = head;
      for (var i in rest) {
         var next = rest[i][1];
         next.obj = curr;
         curr = next;
      }
      return curr;
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
      return collect(head, tail, 3);
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
      return collect(first, rest, 3);
   }

ArraySizes =
   "[" __ size1:(Expression __)? "]" othersizes:(__ "[" __ Expression __ "]")* {
      return collect(size1 !== "" ? size1 : undefined, othersizes, 3);
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

NewExpression =
   "new" __ call:ConstructorCall {
      return new ast.NewExpression({ klass: call.name, args: call.args });
   } /
   "new" __ klass:Identifier {
      return new ast.NewExpression({ klass: klass });
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
      return collect(head, tail, 3);
   }

VariableDeclaration =
   type:Type __ lst:VariableDeclarationList {
      return new ast.VariableDeclaration({ type: type }, lst);
   }

ExpressionList = 
  head:Expression tail:(__ "," __ Expression)* {
     return collect(head, tail, 3);
  }

ActualParameterList =
  "(" __ lst:ExpressionList? __ ")" {
     return new ast.ActualParameterList({}, lst);
  }


InputExpression =
   head:Identifier elems:(__ ">>" __ ReferenceExpression)+ {
      return new ast.InputExpression({ head: head }, collect(null, elems, 3));
   }


/*************** Statements ***************/

Statement =
   DeleteStatement /
   ReturnStatement /
   SwitchStatement /
	IfElseIfStatement /
	IfElseStatement /
   IfStatement /
   WhileStatement /
   ForStatement /
   DeclarationStatement /
   ExpressionStatement /
   OutputStatement

VariableDeclarationStatement =
   decl:VariableDeclaration __ ";" {
      return new ast.VariableDeclarationStatement({ decl: decl });
   }

OutputStatement =
   head:Identifier elems:(__ "<<" __ Expression)* __ ";" {
      return new ast.OutputStatement({ head: head }, collect(null, elems, 3));
   }

ExpressionStatement =
   expr:Expression __ ";" {
      return new ast.ExpressionStatement({ expr: expr });
   }

DeclarationStatement =
   VariableDeclarationStatement

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
	   var blocks = collect(first, rest, 5);
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
      return new ast.SwitchStatement({ expr: expr }, collect(null, _cases, 1));
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
      return collect(head, tail, 1);
   }

CallExpression = 
   name:Identifier __ args:ActualParameterList {
      return new ast.CallExpression({ name: name, args: args });
   }

ReturnStatement =
   "return" __ expr:(NoParensConditionalExpression / Expression) __ ";" {
      return new ast.ReturnStatement({ expr: expr });
   }

DeleteStatement =
   "delete" __ expr:ReferenceExpression __ ";" {
      return new ast.DeleteStatement({ expr: expr });
   }


/************** Program Parts ***************/

ProgramPart =
  IncludeDirective /
  UsingDirective /
  ClassDeclaration /
  FunctionDeclaration /
  FunctionDefinition /
  MethodDefinition /
  ArrayTypedefDeclaration /
  VariableDeclarationStatement /
  Comment

IncludeDirective =
  LocalIncludeDirective /
  SystemIncludeDirective

IncludeFileName = [_A-Za-z0-9./]*

LocalIncludeDirective =
  "#include" _ ["] file:IncludeFileName ["] {
     return new ast.IncludeDirective({ file: file.join('') });
  }

SystemIncludeDirective =
  "#include" _ [<] file:IncludeFileName [>] {
     return new ast.IncludeDirective({ system: true, file: file.join('') });
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

FunctionDeclaration =
   header:FunctionHeader __ ";" {
      return new ast.FunctionDeclaration(header);
   }

FunctionDefinition =
   inline:("inline" __)? header:FunctionHeader __ body:StatementBlock {
      header.inline = (inline !== "");
      return new ast.FunctionDefinition(header, body);
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

ClassDeclaration =
  kind:("struct" / "class") __ name:Identifier __ 
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
     if (kind == "class") {
        return new ast.ClassDeclaration(klass, members);
     } else {
        return new ast.StructDeclaration(klass, members);
     }
  }

ClassPart =
   ClassLabel /
   InlineMethod /
   MethodDeclaration /
   AttributeDeclaration

AccessMode = "public" / "private" / "protected"

ClassLabel = 
   label:AccessMode ":" { 
      return label; 
   }

InlineMethod =
   header:FunctionHeader __ konst:(__ "const")? __ body:StatementBlock  {
      header.inline = true;
      header.konst = (konst !== "");
      return new ast.MethodDefinition(header, body);
   }

MethodDeclaration =
   virtual:("virtual" __)? 
   header:(FunctionHeader / FunctionHeaderNoType) konst:(__ "const")? __ ";" {
      header.virtual = (virtual !== "");
      header.konst = (konst !== "");
      return new ast.MethodDeclaration(header);
   }   

AttributeDeclaration = 
   VariableDeclarationStatement

MethodDefinition =
   inline:("inline" __)?
   type:(Type __)?
   header:FunctionHeaderNoType __ konst:(__ "const")? __ 
   initlist:InitializationList? __
   body:StatementBlock  {
      if (type !== "") {
         header.type = type[0];
      }
      if (initlist !== "") {
         header.initlist = initlist;
      }
      header.inline = (inline !== "");
      header.konst = (konst !== "");
      return new ast.MethodDefinition(header, body);
   }

InitializationList =
   ":" init:(__ ConstructorCall)+ {
      return new ast.InitializationList({}, collect(null, init, 1));
   }


/************** Program ***************/

Program = 
   head:ProgramPart tail:(__ ProgramPart)* {
      return new ast.Program({}, collect(head, tail, 1));
   }
