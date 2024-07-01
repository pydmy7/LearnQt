if (DEFINED qt6rootdir)
    set(Qt6_DIR "${qt6rootdir}/lib/cmake/Qt6")
    set(Qt6GuiTools_DIR "${qt6rootdir}/lib/cmake/Qt6GuiTools")

    find_package(Qt6 COMPONENTS Core Widgets REQUIRED)
else()
    message("usage: cmake -S . -B build -G Ninja -D qt6rootdir=/usr/bin/xxx")
endif()
