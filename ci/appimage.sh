#!/bin/sh
make clean
make AppImage
./package/appimagetool-x86_64.appimage Asteroids.AppDir/ Asteroids.AppImage
