# CMakeList.txt: проект CMake для hexbox; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.20)

# Enable Hot Reload for MSVC compilers if supported.

#if (POLICY CMP0141)
#  cmake_policy(SET CMP0141 NEW)
#  cmake_policy(SET CMP0079 NEW)
#  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
#endif()

#project ("hexbox")
#set(PROJECT_NAME hexbox)
#project (${PROJECT_NAME})
project(kursov-m-a-22-02)
# Добавьте источник в исполняемый файл этого проекта.
set(CMAKE_CXX_STANDARD 20)
#add_executable (hexbox  "hexbox.h" "hb_test.cpp")
add_subdirectory(prj.codeforces)
add_subdirectory(prj.cw)
#if (CMAKE_VERSION VERSION_GREATER 3.12)
#  set_property(TARGET hexbox PROPERTY CXX_STANDARD 20)
#endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
