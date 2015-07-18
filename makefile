all:
	g++ -O3 -fPIC -shared -o example.so example.cc $(shell pkg-config --cflags --libs april-ann)
