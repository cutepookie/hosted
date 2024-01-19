#!/bin/bash
publish_root=$HOME/Desktop/package
rm -rdf ./build/*

xcodebuild -target ProjectMB_TBT -configuration Release clean
./ipa-build ./ -c Release -o ${publish_root} -t ProjectMB_TBT -n
