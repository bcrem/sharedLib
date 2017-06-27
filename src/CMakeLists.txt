include_directories ("${PROJECT_SOURCE_DIR}/lib")

add_executable(libTest main.cpp)
target_link_libraries (libTest dl)
