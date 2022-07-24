CFLAGS = -g -Wshadow -std=c++11 -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept  -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused -Wold-style-cast -Wformat-nonliteral -Wpointer-arith -Winline -Wwrite-strings -Wno-unused-parameter -Wfloat-equal -fsanitize=undefined -fsanitize=unreachable -fsanitize=leak -fsanitize=enum -fsanitize=builtin -fsanitize=shift-exponent -fsanitize=pointer-compare -fsanitize=pointer-subtract -fsanitize=address -Werror

OBJECTS = obj/main.o obj/Construction.o obj/drawers.o obj/Geoapp.o obj/geo.o obj/geoImpl.o obj/geoWorld.o obj/Input.o obj/inputSFML.o obj/keyStates.o

bin/app: $(OBJECTS)
	g++ $(OBJECTS) -o bin/app -lsfml-window -lsfml-system -lsfml-graphics $(CFLAGS)

obj/main.o: main.cpp source/Geoapp.h source/geo.h source/inputSFML.h \
 source/Input.h source/Construction.h source/shapeManager.h \
 source/drawers.h source/uiOptions.h source/conditionTracker.h \
 source/geoWorld.h source/marks.h | obj
	g++ main.cpp -o obj/main.o -c $(CFLAGS)

obj/Construction.o: source/Construction.cpp source/Construction.h \
 source/geo.h source/shapeManager.h | obj
	g++ source/Construction.cpp -o obj/Construction.o -c $(CFLAGS)

obj/drawers.o: source/drawers.cpp source/drawers.h source/geo.h | obj
	g++ source/drawers.cpp -o obj/drawers.o -c $(CFLAGS)

obj/Geoapp.o: source/Geoapp.cpp source/Geoapp.h source/geo.h \
 source/inputSFML.h source/Input.h source/Construction.h \
 source/shapeManager.h source/drawers.h source/uiOptions.h \
 source/conditionTracker.h source/geoWorld.h source/marks.h \
 source/keyStates.h | obj
	g++ source/Geoapp.cpp -o obj/Geoapp.o -c $(CFLAGS)

obj/geo.o: source/geo.cpp source/geo.h | obj
	g++ source/geo.cpp -o obj/geo.o -c $(CFLAGS)

obj/geoImpl.o: source/geoImpl.cpp source/geoImpl.h source/geo.h | obj
	g++ source/geoImpl.cpp -o obj/geoImpl.o -c $(CFLAGS)

obj/geoWorld.o: source/geoWorld.cpp source/geoWorld.h source/drawers.h \
 source/geo.h source/uiOptions.h source/conditionTracker.h \
 source/Construction.h source/shapeManager.h | obj
	g++ source/geoWorld.cpp -o obj/geoWorld.o -c $(CFLAGS)

obj/Input.o: source/Input.cpp source/Input.h | obj
	g++ source/Input.cpp -o obj/Input.o -c $(CFLAGS)

obj/inputSFML.o: source/inputSFML.cpp source/inputSFML.h source/Input.h | obj
	g++ source/inputSFML.cpp -o obj/inputSFML.o -c $(CFLAGS)

obj/keyStates.o: source/keyStates.cpp source/keyStates.h source/Geoapp.h \
 source/geo.h source/inputSFML.h source/Input.h source/Construction.h \
 source/shapeManager.h source/drawers.h source/uiOptions.h \
 source/conditionTracker.h source/geoWorld.h source/marks.h | obj
	g++ source/keyStates.cpp -o obj/keyStates.o -c $(CFLAGS)

obj:
	mkdir obj

clean:
	rm -r obj