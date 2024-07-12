if (DEFINED qt5rootdir)
    set(Qt5_DIR "${qt5rootdir}/lib/cmake/Qt5")
    set(Qt5GuiTools_DIR "${qt5rootdir}/lib/cmake/Qt5GuiTools")

    find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
else()
    message("usage: cmake -S . -B build -G Ninja -D qt5rootdir=D:/Library/Qt/5.15.2/msvc2019_64")
endif()
