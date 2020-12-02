CXXFLAGS=-ggdb -std=c++11 -Wpedantic -Wall -Wextra -Werror -Wzero-as-null-pointer-constant
main: hw8i.cpp
		g++  $(CXXFLAGS)  hw8i.cpp   -o   hw8i.bin
		g++  $(CXXFLAGS)  hw8ii.cpp   -o   hw8ii.bin
clean:
		echo ----------------removing executable program main--------------------
		/bin/rm hw8i.bin
		/bin/rm hw8ii.bin