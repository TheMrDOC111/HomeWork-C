project(strategies)
set(SOURCES
		human.cpp
		computer.cpp
		computer_interface.cpp computer2.cpp)
set(HEADERS
		human.h
		computer.h
		computer2.h
		interface.h
		computer_interface.h)

include_directories(../)

add_library(strategies ${SOURCES} ${HEADERS})
