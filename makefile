bin/app: obj/main.o obj/construction.o obj/geoapp.o obj/geo.o obj/input.o
	g++ obj/main.o obj/construction.o obj/geoapp.o obj/geo.o obj/input.o -o bin/app -Wall -lsfml-window -lsfml-system -lsfml-graphics

obj/main.o: main.cpp source/Geoapp.cpp source/Geoapp.h source/Construction.h source/geo.h source/Input.h
	g++ main.cpp -o obj/main.o -c -Wall

obj/construction.o: source/Construction.cpp source/Construction.h source/geo.h
	g++ source/Construction.cpp -o obj/construction.o -c -Wall 

obj/geoapp.o: source/Geoapp.cpp source/Geoapp.h source/Construction.h source/geo.h source/Input.h
	g++ source/Geoapp.cpp -o obj/geoapp.o -c -Wall

obj/geo.o: source/geo.cpp source/geo.h 
	g++ source/geo.cpp -o obj/geo.o -c -Wall

obj/input.o: source/Input.cpp source/Input.h
	g++ source/Input.cpp -o obj/input.o -c -Wall
