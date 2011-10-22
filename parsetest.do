redo-ifchange cc.js
for f in $(find ./tests -name "*.cc"); do
   ./cc.js --parsetest $f
done
