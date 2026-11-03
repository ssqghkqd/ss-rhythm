#!/bin/sh

cd $WORKPATH/engine
../scripts/build.sh
lldb /tmp/build/$PJ_NAME/$(cat .preset)/$PJ_NAME
