clear
echo "clear"

echo "`nRemove-Item -Path ./build -Recurse -Force"
Remove-Item -Path ./build -Recurse -Force

# user / system env
# $env:QT_QPA_PLATFORM_PLUGIN_PATH = "D:\Library\Qt\5.15.2\msvc2019_64\plugins\platforms"

echo "`nsource: cmake -S . -B build -G Ninja -D qt5rootdir=D:/Library/Qt/5.15.2/msvc2019_64"
cmake -S . -B build -G Ninja -D qt5rootdir=D:/Library/Qt/5.15.2/msvc2019_64

echo "`nbuild: cmake --build build -j"
cmake --build build -j

echo "`nrun: ./build/mainwindow/mainwindow.exe"
./build/mainwindow/mainwindow.exe
