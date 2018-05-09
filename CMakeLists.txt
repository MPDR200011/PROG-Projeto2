cmake_minimum_required(VERSION 3.10)
project(PROG___Projeto_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(cwcreator cwcreator/main.cpp cwcreator/Dictionary.cpp cwcreator/Dictionary.h cwcreator/Board.cpp cwcreator/Board.h cwcreator/wordUtils.cpp cwcreator/wordUtils.h cwcreator/cwcreator.cpp cwcreator/cwcreator.h cwcreator/coloredTextWindows.cpp cwcreator/coloredTextWindows.h cwcreator/coloredTextLinux.cpp cwcreator/coloredTextLinux.h)
add_executable(cwplayer cwplayer/main.cpp cwplayer/Dictionary.cpp cwplayer/Dictionary.h cwplayer/Board.cpp cwplayer/Board.h cwplayer/wordUtils.cpp cwplayer/wordUtils.h cwplayer/coloredTextLinux.cpp cwplayer/coloredTextLinux.h cwplayer/coloredTextWindows.cpp cwplayer/coloredTextWindows.h)