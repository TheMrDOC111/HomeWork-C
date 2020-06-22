project(game)

set(SOURCES
		game.cpp)
set(HEADERS
		game.h
		structures.h)

include_directories(../)

add_library(game ${SOURCES} ${HEADERS})
