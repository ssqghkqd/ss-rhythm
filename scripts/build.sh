#!/bin/sh

cd $WORKPATH/engine
../scripts/configure.sh
time cmake --build --preset=$(cat ./.preset)