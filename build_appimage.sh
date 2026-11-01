#!/bin/bash
set -e

# building
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build

# setting up
rm -rf AppDir
mkdir -p AppDir/usr/bin
mkdir -p AppDir/usr/share/applications
mkdir -p AppDir/usr/share/icons/hicolor/256x256/apps

rsvg-convert -w 256 -h 256 assets/cache-cleaner.svg -o cache-cleaner.png

# copying assets
cp build/cache-cleaner AppDir/usr/bin/
cp assets/cache-cleaner.desktop AppDir/cache-cleaner.desktop
cp assets/cache-cleaner.png AppDir/cache-cleaner.png
cp assets/cache-cleaner.png AppDir/usr/share/icons/hicolor/256x256/apps/cache-cleaner.png

# installing linuxdeploy
if [ ! -f "linuxdeploy-x86_64.AppImage" ]; then
    wget -c "https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage"
    chmod +x linuxdeploy-x86_64.AppImage
fi

# getting an appimage
./linuxdeploy-x86_64.AppImage --appimage-extract-and-run --appdir AppDir --output appimage

# renaming appimage
mv Cache_Cleaner*.AppImage cache-cleaner-x86_64.AppImage || true

echo "AppImage created: cache-cleaner-x86_64.AppImage"