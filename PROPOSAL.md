# Final Project Proposal

## Group Members:

Anthony Chen, Shaurya Sen, Amber Shen

# Intentions:

SongGuessr: A live multiplayer game where players guess the song that is playing.

# High level description & User Interface:

Players connect to a host server. They initially wait in a lobby. When the game starts, the host plays a randomized song. Players type their guesses in the terminal, with a 1s cooldown. Players can see other players' guesses. When a player guesses a song correctly, the server will notify everyone. After each song, player scores are displayed in everyone's terminals.

# Technical Details:

## Class topics that will be used

**How you will be using the topics covered in class in the project.**

- Allocating Memory: Store information about songs, guesses, and other game data.
- Working With Files: Work with mp3 files for the songs. Read and write player scores.
- Processes (fork, exec etc.): Have multiple clients connect to a host sever.
- Sockets: Handle communication between clients and server.

**What algorithms and/or data structures you will be using, and how.**

- Array/LinkedList: store songs, track players
- Structs
  - Player: id, name, score
  - Song: name, artist
- Random: shuffle songs, pick a song wthout repetition

# Intended pacing:

| Day | Date    | Task                                                                                     | Assigned        |
| --- | ------- | ---------------------------------------------------------------------------------------- | --------------- |
| 1   | 1/4/24  | Set up project (makefile, files, methods), create branches                               | All             |
| 2   | 1/5/24  | Get user input for guess, with 1s cooldown between guesses _(no server)_                 | Amber           |
|     | 1/5/24  | Pick a song from a list randomly, without repetition                                     | Shaurya         |
|     | 1/5/24  | Create forking network server with sockets                                               | Anthony         |
| 3   | 1/8/24  | Check guesses & award points for the correct answer _(no server)_                        | Amber           |
|     | 1/8/24  | Play a song from an MP3 file _(no server)_                                               | Shaurya         |
|     | 1/8/24  | Listen for input from all players, display messages to everyone                          | Anthony         |
| 4   | 1/9/24  | Create a leaderboard keeping track of player scores                                      | Amber           |
|     | 1/9/24  | Implement player join procedure _(prompt for name, display message)_                     | Anthony         |
|     | 1/9/24  | Play a random 15s snippet of a song _(no server)_                                        | Shaurya         |
| 5   | 1/10/24 | Implement game control _(introduce song, check guesses, update score, send leaderboard)_ | Amber & Anthony |
|     | 1/10/24 | Play snippets of shuffled songs continuously until end of playlist                       | Shaurya         |
| 6   | 1/11/24 | Play songs and move on after a correct guess                                             | Shaurya         |
| 7   | 1/12/24 | Bug squashes                                                                             | All             |
| 8   | 1/15/24 | Finishing touches                                                                        | All             |

**Possible add-ons**

- Display number of letters with underscores
- Players vote to skip song
- Guesses can have typos (typo tolerance)
- Songs wll be played on every player's computer rather than just the host's
- Host can add songs to the game queue
- Host can change more game settings
