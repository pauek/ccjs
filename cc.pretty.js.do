SRC_FILES="src/header.js src/ast.js src/prettyprinter.js src/interpreter.js src/parser.js src/footer.js"
redo-ifchange $SRC_FILES
cat $SRC_FILES > $3
