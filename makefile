%: %.cpp Trie.h Clarg.cpp
	g++ -g ./$@.cpp ./Clarg.cpp -std=c++17 -o $@