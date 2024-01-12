compile: _host _player _game

_game: game.o utils.o
	@gcc -o game game.o utils.o -v
_host: host.o networking.o utils.o
	@gcc -o host host.o networking.o utils.o
_player: player.o networking.o utils.o
	@gcc -o player player.o networking.o utils.o

game.o: src/game.c
	@gcc -c src/game.c
host.o: src/host.c include/networking.h
	@gcc -c src/host.c
networking.o: src/networking.c include/networking.h
	@gcc -c src/networking.c
player.o: src/player.c include/networking.h
	@gcc -c src/player.c
utils.o: src/utils.c include/utils.h
	@gcc -c src/utils.c
	

game: _game
	@./game
host:_host
	@./host
player: _player
	@./player

clean:
	@rm -f *.o game host player
