compile: _host _player

_host: host.o game.o music.o networking.o utils.o
	@gcc -o host host.o game.o music.o networking.o utils.o -lncurses
_player: player.o networking.o utils.o
	@gcc -o player player.o networking.o utils.o -lncurses

game.o: src/game.c include/game.h include/imports.h include/music.h include/utils.h
	@gcc -mshstk -c src/game.c 
host.o: src/host.c include/game.h include/imports.h include/music.h include/utils.h
	@gcc -mshstk -c src/host.c
music.o: src/music.c include/music.h include/imports.h
	@gcc -mshstk -c src/music.c
networking.o: src/networking.c include/game.h include/imports.h include/music.h include/utils.h
	@gcc -mshstk -c src/networking.c
player.o: src/player.c include/game.h include/imports.h include/music.h include/utils.h
	@gcc -mshstk -c src/player.c
utils.o: src/utils.c include/utils.h include/imports.h
	@gcc -mshstk -c src/utils.c

host:_host
	@./host
player: _player
	@./player $(ARGS)

clean:
	@rm -f *.o game host player
