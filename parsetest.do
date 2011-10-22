redo-ifchange cc.js

output=$(mktemp output.XXXXX) || exit 1
for f in $(find ./tests -name "*.cc"); do
   ./cc.js --parsetest $f
done
