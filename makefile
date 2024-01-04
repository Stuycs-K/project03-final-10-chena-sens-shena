compile: _host _player

_host: host.o networking.o utils.o
	@gcc -o host host.o networking.o utils.o
_player: player.o networking.o utils.o
	@gcc -o player player.o networking.o utils.o

host.o: src/host.c include/host.h
	@gcc -c src/host.c
networking.o: src/networking.c include/networking.h
	@gcc -c src/networking.c
player.o: src/player.c include/player.h
	@gcc -c src/player.c
utils.o: src/utils.c include/utils.h
	@gcc -c src/utils.c

clean:
	@rm -f *.o host player
