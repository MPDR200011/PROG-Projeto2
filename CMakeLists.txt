cmake_minimum_required(VERSION 3.10)
project(PROG___Projeto_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(cwcreator cwcreator/main.cpp cwcreator/Dictionary.cpp cwcreator/Dictionary.h cwcreator/Board.cpp cwcreator/Board.h cwcreator/wordUtils.cpp cwcreator/wordUtils.h)