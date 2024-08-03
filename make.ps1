clear
echo "clear"

echo "`nRemove-Item -Path ./build -Recurse -Force"
Remove-Item -Path ./build -Recurse -Force

echo "`nsource: cmake -S . -B build -G Ninja -D myself=ON -D qt5rootdir=D:/Library/Qt/5.15.2/msvc2019_64"
cmake -S . -B build -G Ninja -D myself=ON -D qt5rootdir=D:/Library/Qt/5.15.2/msvc2019_64

echo "`nbuild: cmake --build build -j"
cmake --build build -j

echo "`nrun: ./build/painter/painter.exe"
./build/painter/painter.exe
