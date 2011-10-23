redo-ifchange cc.js
find ./tests -name "*.cc" | xargs parallel ./cc.js --parsetest --

