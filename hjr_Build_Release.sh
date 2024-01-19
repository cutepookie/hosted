#!/bin/bash
rm -rdf ./build

publish_root=$HOME/Desktop/package

xcodebuild -target ProjectMB_HJR -configuration Release clean
./ipa-build ./ -c Release -o ${publish_root} -t ProjectMB_HJR -n
