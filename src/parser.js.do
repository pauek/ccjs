GRAMMAR="c++.pegjs"
redo-ifchange $GRAMMAR
pegjs --export-var "cc" $GRAMMAR $3
