addExecutable(test)
target_link_libraries(test PRIVATE Qt5::Core Qt5::Widgets)
copyDll(test)
