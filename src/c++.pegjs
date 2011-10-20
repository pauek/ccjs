
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

Identifier = 
   name:([_A-Za-z] [_A-Za-z0-9]*) {
      return new ast.Identifier({ id: name[0] + name[1].join('') });
   }

DecimalIntegerLiteral = 
   "0" { 
      return new ast.IntegerLiteral({ lit: 0 }); 
   } / 
   sign:"-"? head:NonZeroDigit tail:DecimalDigits? { 
      return new ast.IntegerLiteral({ lit: parseInt(sign + head + tail) });
   }

DecimalDigits
  = digits:DecimalDigit+ { return digits.join(""); }

DecimalDigit = [0-9]
NonZeroDigit = [1-9]

Literal = 
   StringLiteral /
   DecimalIntegerLiteral

StringLiteral "string" = 
   '"' literal:StringCharacters? '"' {
      return new ast.StringLiteral({ lit: literal });
   }

StringCharacters = 
   chars:StringCharacter+ { 
      return chars.join(""); 
   }

StringCharacter = 
   !('"' / "\\" / LineTerminator) char_:SourceCharacter { return char_; } / 
   "\\" sequence:EscapeSequence { return sequence; } / 
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

LineTerminatorSequence "end of line" = "\n" / "\r\n" / "\r"

Type = name:("int" / "string" / "char" / "float" / "void") {
     return new ast.Type({ name: name });
   }

PrimaryExpression =
   Literal /
   ReferenceExpression

ReferenceExpression =
   ArrayReference /
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
  operator:UnaryOperator __ expression:UnaryExpression {
     return new ast.UnaryExpression({ 
        operator: operator, 
        right: right 
     });
  }

UnaryOperator = "++" / "--" / "+" / "-" / "~" / "!"


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
   AdditiveExpression

AssignmentOperator = "+=" / "*=" / "/=" / "-=" / "=" 

LogicalANDExpression =
   head:ComparisonExpression tail:(__ "&&" __ ComparisonExpression)+ {
      var result = [head];
      for (var i = 0; i < tail.length; i++) {
         result.push(tail[i][3]);
      }
      return new ast.LogicalANDExpression({}, result);
   }

LogicalORExpression =
   head:LogicalANDExpression tail:(__ "||" __ LogicalANDExpression)+ {
      var result = [head];
      for (var i = 0; i < tail.length; i++) {
         result.push(tail[i][3]);
      }
      return new ast.LogicalORExpression({}, result);
   }

Condition =
   LogicalANDExpression /
   LogicalORExpression /
   ComparisonExpression

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

Expression = 
   AssignmentExpression

VariableReference =
   name:Identifier { return new ast.VariableReference({ name: name }); }

ArrayReference =
   name:Identifier _ "[" _ index:Expression _ "]" {
      return new ast.ArrayReference({ name: name, index: index });
   }

FormalParameter =
   type:Type _ name:Identifier {
      return new ast.FormalParameter({ type: type, name: name });
   }

FormalParameterList =
   head:FormalParameter tail:(__ "," __ FormalParameter)* {
      var result = [head];
      for (var i = 0; i < tail.length; i++) {
         result.push(tail[i][3]);
      }
      return result;
   }

VariableDeclaration =
   name:Identifier value:(__ "=" __ Expression)? {
      var result = { name: name };
      if (typeof value[3] != 'undefined') {
         result.value = value[3];
      }
      return new ast.VariableDeclaration(result);
   }

VariableDeclarationList =
   head:VariableDeclaration tail:(__ "," __ VariableDeclaration)* {
      var result = [head];
      for (var i = 0; i < tail.length; i++) {
         result.push(tail[i][3]);
      }
      return result;
   }

VariableDeclarationStatement =
   type:Type __ lst:VariableDeclarationList __ ";" {
      return new ast.VariableDeclarationStatement({ type: type }, lst);
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

VectorDeclaration =
   name:Identifier params:(__ ActualParameterList)? {
      var result = { name: name };
      if (params[1] !== undefined) {
         result.params = params[1];
      }
      return new ast.VectorDeclaration(result);
   }

VectorDeclarationList =
   head:VectorDeclaration tail:(__ "," __ VectorDeclaration)* {
      var result = [head];
      for (var i = 0; i < tail.length; i++) {
         result.push(tail[i][3]);
      }
      return result;
   }                     

VectorType =
   "vector" _ "<" _ subtype:Type _ ">" {
      return new ast.VectorType({ subtype: subtype });
   }

VectorDeclarationStatement =
   type:VectorType __ lst:VectorDeclarationList __ ";" {
      return new ast.VectorDeclarationStatement({ type: type }, lst);
   }

OutputStatement =
   "cout" elems:(__ "<<" __ Expression)* __ ";" {
      var elements = [];
      for (var i = 0; i < elems.length; i++) {
         elements.push(elems[i][3]);
      }
      return new ast.OutputStatement({ head: "cout" }, elements);
   }

InputStatement =
   "cin" elems:(__ ">>" __ ReferenceExpression)* __ ";" {
      var elements = [];
      for (var i = 0; i < elems.length; i++) {
         elements.push(elems[i][3]);
      }
      return new ast.InputStatement({ head: "cin" }, elements);
   }

Statement =
   VectorDeclarationStatement /
   VariableDeclarationStatement /
	IfElseIfStatement /
	IfElseStatement /
   IfStatement /
   WhileStatement /
   ForStatement /
   InputStatement /
   AssignmentStatement /
   OutputStatement /
   FunctionCall

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

ForStatement =
   "for" __ "(" __ 
   init:AssignmentExpression __ ";" __ 
   cond:Condition __ ";" __ 
   incr:AssignmentExpression __ ")" __ 
   body:StatementBlock {
      return new ast.ForStatement({ init: init, cond: cond, incr: incr }, body);
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

StatementList =
   head:Statement tail:(__ Statement)* {
      var result = [head];
      for (var i = 0; i < tail.length; i++) {
         result.push(tail[i][1]);
      }
      return result;
   }

StatementBlock =
   "{" __ lst:StatementList __ "}" {
      return lst;
   } /
   stmt:Statement {
      return [stmt];
   }

FunctionCall =
   name:Identifier __ args:ActualParameterList __ ";" {
      return new ast.FunctionCall({ name: name, args: args });
   }

FunctionDef =
   type:Type _ name:Identifier __ 
   "(" __ params:FormalParameterList? __ ")" __ 
   body:StatementBlock {
      return new ast.FunctionDef({ 
         type: type, 
         name: name, 
         params: params 
      }, body);
   }

IncludeDirective "include" =
  "#include" _ [<"] file:[a-z]* [>"] {
     return new ast.IncludeDirective({ file: file.join('') });
  }

UsingDirective "using" =
  "using" __ "namespace" __ ns:Identifier __ ";" {
    return new ast.UsingDirective({ namespace: ns });
  }

ProgramPart =
  IncludeDirective /
  UsingDirective /
  FunctionDef /
  Comment

Program = 
   head:ProgramPart tail:(__ ProgramPart)* {
      var parts = [head];
      for (var i = 0; i < tail.length; i++) {
         parts.push(tail[i][1]);
      }  
      return new ast.Program({}, parts);
   }
