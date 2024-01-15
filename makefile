compile: _host _player _game

_game: game.o music.o utils.o
	@gcc -o game game.o music.o utils.o
_host: host.o music.o networking.o utils.o
	@gcc -o host host.o music.o networking.o utils.o
_player: player.o networking.o utils.o
	@gcc -o player player.o networking.o utils.o

game.o: src/game.c include/game.h include/imports.h include/music.h include/utils.h
	@gcc -c src/game.c
host.o: src/host.c include/game.h include/imports.h include/music.h include/utils.h
	@gcc -c src/host.c
networking.o: src/networking.c include/game.h include/imports.h include/music.h include/utils.h
	@gcc -c src/networking.c
player.o: src/player.c include/game.h include/imports.h include/music.h include/utils.h
	@gcc -c src/player.c

utils.o: src/utils.c include/utils.h include/imports.h
	@gcc -c src/utils.c
music.o: src/music.c include/music.h include/imports.h
	@gcc -c src/music.c

game: _game
	@./game
host:_host
	@./host
player: _player
	@./player

clean:
	@rm -f *.o game host player
