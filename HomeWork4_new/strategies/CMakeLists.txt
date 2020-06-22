project(strategies)
set(SOURCES
		human.cpp
		computer.cpp
		computer_interface.cpp computer_second.cpp)
set(HEADERS
		human.h
		computer.h
		interface.h
		computer_interface.h computer_second.h)

include_directories(../)

add_library(strategies ${SOURCES} ${HEADERS})
