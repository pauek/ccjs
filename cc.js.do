redo-ifchange cc.pretty.js
(echo "#!/usr/bin/env node"; cat cc.pretty.js) > $3
chmod +x $3