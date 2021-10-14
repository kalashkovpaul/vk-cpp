sudo apt install cmake
sudo apt-get install libgtest-dev
sudo apt install gcovr
cd homework_1_5
cd src
clang-format -i -style=WebKit *.c
clang -g -I../inc -fsanitize=thread *.c
clang -g -I../inc -fsanitize=undefined *.c
clang -g -I../inc -fsanitize=memory *.c
clang -g -I../inc -fsanitize=address *.c
rm a.out
cd ../inc
clang-format -i -style=WebKit *.h
cd ..
cppcheck -q --enable=all ./src
mkdir build
cd build
cmake ..
scan-build make
valgrind --tool=memcheck --leak-check=full ./letterTest
gcovr -r ../ --html coverage --html-details