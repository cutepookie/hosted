#!/bin/bash
svn update
rm -rdf ./build/*
publish_root=/Users/crimoon/Documents/project/app_client/app_client
xcodebuild -target ProjectTK -configuration Distribution clean
./ipa-build ./ -c Distribution -o ${publish_root} -t ProjectTK -n

tar -zcvf ${publish_root}$(date +"%Y%m%d%H%M")_ProjectTK.app.dSYM.tar.gz ./build/Distribution-iphoneos/ProjectTK.app.dSYM
#svn add ${publish_root}*.ipa
#svn add ${publish_root}*.gz
#svn commit ${publish_root} -m "$(date +"%Y%m%d%H%M")"
