set(target mainwindow)

addExecutable(${target})
target_link_libraries(${target} PRIVATE Qt5::Core Qt5::Widgets)
copyDll(${target})
