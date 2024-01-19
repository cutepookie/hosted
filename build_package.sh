#!/bin/sh

./build_native.sh

cp -R ./bak/assets/* ./assets

ant release


cp ./bin/ProjectPKQ-release.apk ./projectpkq-`date '+%Y%m%d%H%M'`.apk