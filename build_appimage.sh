#!/bin/bash
set -e

# building
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build

# setting up
rm -rf AppDir
mkdir -p AppDir/usr/bin
mkdir -p AppDir/usr/share/applications
mkdir -p AppDir/usr/share/icons/hicolor/scalable/apps

mkdir -p AppDir/usr/share/icons/hicolor/16x16/apps
mkdir -p AppDir/usr/share/icons/hicolor/22x22/apps
mkdir -p AppDir/usr/share/icons/hicolor/24x24/apps
mkdir -p AppDir/usr/share/icons/hicolor/32x32/apps
mkdir -p AppDir/usr/share/icons/hicolor/48x48/apps
mkdir -p AppDir/usr/share/icons/hicolor/64x64/apps
mkdir -p AppDir/usr/share/icons/hicolor/128x128/apps
mkdir -p AppDir/usr/share/icons/hicolor/256x256/apps
mkdir -p AppDir/usr/share/icons/hicolor/512x512/apps

# copying assets
cp build/bytepurge AppDir/usr/bin/
cp assets/bytepurge.desktop AppDir/usr/share/applications/ # .desktop file MUST go into usr/share/applications
cp assets/bytepurge.desktop AppDir/bytepurge.desktop # ALSO copy it to the root (linuxdeploy expects it there)

cp assets/icons/bytepurge-256.png AppDir/bytepurge.png
cp assets/icons/bytepurge-16.png AppDir/usr/share/icons/hicolor/16x16/apps/bytepurge.png
cp assets/icons/bytepurge-22.png AppDir/usr/share/icons/hicolor/22x22/apps/bytepurge.png
cp assets/icons/bytepurge-24.png AppDir/usr/share/icons/hicolor/24x24/apps/bytepurge.png
cp assets/icons/bytepurge-32.png AppDir/usr/share/icons/hicolor/32x32/apps/bytepurge.png
cp assets/icons/bytepurge-48.png AppDir/usr/share/icons/hicolor/48x48/apps/bytepurge.png
cp assets/icons/bytepurge-64.png AppDir/usr/share/icons/hicolor/64x64/apps/bytepurge.png
cp assets/icons/bytepurge-128.png AppDir/usr/share/icons/hicolor/128x128/apps/bytepurge.png
cp assets/icons/bytepurge-256.png AppDir/usr/share/icons/hicolor/256x256/apps/bytepurge.png
cp assets/icons/bytepurge-512.png AppDir/usr/share/icons/hicolor/512x512/apps/bytepurge.png

# installing linuxdeploy
if [ ! -f "linuxdeploy-x86_64.AppImage" ]; then
    wget -c "https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage"
    chmod +x linuxdeploy-x86_64.AppImage
fi

# getting an appimage
./linuxdeploy-x86_64.AppImage --appimage-extract-and-run --appdir AppDir --output appimage

# renaming appimage
mv Byte_Purge*.AppImage bytepurge-x86_64.AppImage || true

echo "AppImage created: bytepurge-x86_64.AppImage"