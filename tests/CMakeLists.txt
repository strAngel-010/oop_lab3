find_package(Catch2 2 REQUIRED)

# создание исполняемого файла для программы тестирования
add_executable(tests testing.cpp)

# подключение библиотек circle и Catch2 к тесту
target_link_libraries(tests apartment cottage flat room table address living Catch2::Catch2)
add_compile_options(-fprofile-arcs -ftest-coverage)
link_libraries(gcov)