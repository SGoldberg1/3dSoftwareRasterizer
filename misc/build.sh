clear

engineFlags="-g -shared -fPIC -DENGINE_DEBUG=1 -Wno-writable-strings"
engineLibs=""

clang++  $engineFlags ../code/Engine.cpp -o ../build/engine.so

platformFlags="-g -rdynamic -Wno-writable-strings"
platformLibs="-lSDL2 -ldl"

clang++ $platformFlags ../code/Linux_Main.cpp -o ../build/main $platformLibs
