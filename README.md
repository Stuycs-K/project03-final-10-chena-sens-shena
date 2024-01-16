[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/SQs7pKlr)
# SongGuessr

### ASA (Angle-Side-Angle)

Anthony Chen, Shaurya Sen, Amber Shen
       
### Project Description:
SongGuessr is a live multiplayer music guessing game. Players will gain points every round by correctly guessing the playing song before time is up!

Players connect to a host server. They initially wait in a lobby. When the game starts, the host plays a randomized song. Players type their guesses with no spaces in the terminal. Players can see other players' guesses. When a player guesses a song correctly, they will gain points. After each song, player scores are displayed in everyone's terminals.

### Instructions:
How to Play As Player: 
1. Clone github repo
2. run `sudo apt get install ncurses`
3. run `make server` ARGS={HOST_IP}
5. Listen to the song and type in your guesses!

How to Play as Host:
1. Clone github repo
4. run `ifconfig` and provide ip to players
5. run `sudo apt get install ncurses`
6. run `sudo apt install mpg123`
7. run these commands for audio if on WSL
       1. `sudo apt install pulseaudio`
       2. `pulseaudio --start`
       3. `mpg123 -a pulse your_file.mp3`
8. run `make host`

### Bugs:
1. Guesses only work with no spaces
2. Song doesn't play until after 15 s + client update event
3. Chat doesn't persist during each round
4. Players can spam guess the right answer and rack up points until round ends
