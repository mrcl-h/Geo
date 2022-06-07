CFLAGS = -g -Wshadow -std=c++11 -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept  -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused -Wold-style-cast -Wformat-nonliteral -Wpointer-arith -Winline -Wwrite-strings -Wno-unused-parameter -Wfloat-equal -fsanitize=undefined -fsanitize=unreachable -fsanitize=leak -fsanitize=enum -fsanitize=builtin -fsanitize=shift-exponent -fsanitize=pointer-compare -fsanitize=pointer-subtract -fsanitize=address -Werror


OBJECTS = obj/main.o obj/construction.o obj/geoapp.o obj/geo.o obj/input.o obj/geoImpl.o obj/inputSFML.o 
bin/app: $(OBJECTS)
	g++ $(OBJECTS) -o bin/app -lsfml-window -lsfml-system -lsfml-graphics $(CFLAGS)

obj/main.o: main.cpp source/Geoapp.cpp source/Geoapp.h source/Construction.h source/geo.h source/Input.h source/vectorHolder.h
	g++ main.cpp -o obj/main.o -c $(CFLAGS)

obj/construction.o: source/Construction.cpp source/Construction.h source/geo.h source/vectorHolder.h
	g++ source/Construction.cpp -o obj/construction.o -c $(CFLAGS)

obj/geoapp.o: source/Geoapp.cpp source/Geoapp.h source/Construction.h source/geo.h source/vectorHolder.h source/Input.h source/inputSFML.h
	g++ source/Geoapp.cpp -o obj/geoapp.o -c $(CFLAGS)

obj/inputSFML.o: source/inputSFML.cpp source/inputSFML.h source/Input.h
	g++ source/inputSFML.cpp -o obj/inputSFML.o -c $(CFLAGS)

obj/geo.o: source/geo.cpp source/geo.h source/vectorHolder.h
	g++ source/geo.cpp -o obj/geo.o -c $(CFLAGS)

obj/geoImpl.o: source/geoImpl.cpp source/geoImpl.h source/geo.h source/vectorHolder.h
	g++ source/geoImpl.cpp -o obj/geoImpl.o -c $(CFLAGS)

obj/input.o: source/Input.cpp source/Input.h
	g++ source/Input.cpp -o obj/input.o -c $(CFLAGS)

clean:
	rm $(OBJECTS)
