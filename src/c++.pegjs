
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

Literal = 
   StringLiteral /
   IntegerLiteral

IntegerLiteral =
   num:[0-9] { 
      return new ast.IntegerLiteral({ lit: parseInt(num) }); 
   }

DecimalDigit
  = [0-9]

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

Expression =
   Literal /
   ArrayReference /
   VariableReference

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

Type = name:("int" / "char" / "float" / "void") {
     return new ast.Type({ name: name });
   }

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
   name:Identifier value:(__ "=" __ Literal)? {
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

OutputElement = 
   e:Expression {
      return new ast.OutputElement({ expr: e });
   }

OutputStatement =
   "cout" elems:(__ "<<" __ OutputElement)* ";" {
      var elements = [];
      for (var i in elems) {
         elements.push(elems[i][3]);
      }
      return new ast.OutputStatement({ head: "cout" }, elements);
   }

Statement =
   VectorDeclarationStatement /
   VariableDeclarationStatement /
   FunctionCall /
   OutputStatement

StatementList =
   head:Statement tail:(__ Statement)* {
      var result = [head];
      for (var i = 0; i < tail.length; i++) {
         result.push(tail[i][1]);
      }
      return result;
   }

FunctionCall =
   name:Identifier __ args:ActualParameterList __ ";" {
      return new ast.FunctionCall({ name: name, args: args });
   }


FunctionBody =
   StatementList

FunctionDef =
   type:Type _ name:Identifier 
   "(" __ params:FormalParameterList? __ ")" __
   "{" __ body:FunctionBody? __ "}" {
      return new ast.FunctionDef({ type: type, name: name, params: params }, body);
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
