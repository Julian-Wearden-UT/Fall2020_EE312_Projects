final: go_fish player deck card
	g++ -o gofish go_fish.o player.o deck.o card.o
go_fish: 
	g++ -std=c++11 -O0 -g -Wall -Werror -o go_fish.o -c go_fish.cpp
player:
	g++ -std=c++11 -O0 -g -Wall -Werror -o player.o -c player.cpp
deck:
	g++ -std=c++11 -O0 -g -Wall -Werror -o deck.o -c deck.cpp
card:
	g++ -std=c++11 -O0 -g -Wall -Werror -o card.o -c card.cpp
