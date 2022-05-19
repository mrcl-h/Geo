all:
	g++ main.cpp source/geo.cpp source/Geoapp.cpp -o app -Wall -lsfml-window -lsfml-system -lsfml-graphics
