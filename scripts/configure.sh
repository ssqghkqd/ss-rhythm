#/bin/sh

cd $WORKPATH/engine/
cmake --preset=$(cat .preset)
