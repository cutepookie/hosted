#!/bin/bash
rm -rdf ./build/*

publish_root=$HOME/Desktop/package

xcodebuild -target ProjectMB_KY -configuration Release clean
./ipa-build ./ -c Release -o ${publish_root} -t ProjectMB_KY -n

#tar -zcvf ${publish_root}$(date +"%Y%m%d%H%M")_ProjectTK_KY.app.dSYM.tar.gz ./build/Release-iphoneos/ProjectTK_KY.app.dSYM
#svn add ${publish_root}*.ipa
#svn add ${publish_root}*.gz
#svn commit ${publish_root} -m "$(date +"%Y%m%d%H%M")"
