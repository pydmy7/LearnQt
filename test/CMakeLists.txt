addExecutable(test)
target_link_libraries(test PRIVATE Qt6::Core Qt6::Widgets)
copyDll(test)
