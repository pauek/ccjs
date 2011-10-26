redo-ifchange cc.js
find /home/pauek/UPC/Anys/ -name "*.cpp" -print0 \
| xargs -0 parallel ./cc.js --parsetest --
