# Dev Log:

### 2024-01-02 - Setup day

| Person  | Logs                                                  | Time (min) |
| ------- | ----------------------------------------------------- | ---------- |
| Anthony | Set up project (makefile, files, methods)             | 15         |
|         | Create forking network server with sockets            | 5          |
| Amber   | Create branches                                       | 5          |
|         | Read input (guesses) from local machine with 1s delay | 20         |
| Shaurya | Update dev log                                        | 5          |
|         | Find and add MP3 Player Library to use                | 15         |
|         | Add song function headers                             | 5          |

### 2024-01-03 - Branch out

| Person  | Logs                                                                                       | Time (min) |
| ------- | ------------------------------------------------------------------------------------------ | ---------- |
| Anthony | Add print messages                                                                         | 5          |
|         | Handle multiple client connect                                                             | 30         |
| Amber   | Check if a guess is correct, award points to correct player                                | 70         |
| Shaurya | Add random int and random song functions                                                   | 40         |
|         | Work on using MPG123 and portaudio to play audio. Figure out how to use external libraries | 30         |

### 2024-01-08 - Branch progress

| Person  | Logs                                                                             | Time (min) |
| ------- | -------------------------------------------------------------------------------- | ---------- |
| Anthony | Handle multiple client read/write                                                | 30         |
| Amber   | Create a leaderboard for players that sorts every time                           | 40         |
| Shaurya | Start using different library SDL2 and try to get it working to play audio files | 30         |

### 2024-01-09 - Almost there in branches

| Person  | Logs                                                                        | Time (min) |
| ------- | --------------------------------------------------------------------------- | ---------- |
| Anthony | Use player structs and ask for player names                                 | 15         |
|         | Display messages to everyone                                                | 25         |
| Amber   | Create an update score function, restructure player list                    | 30         |
|         | Working game without multiple players or actual songs (with point awarding) | 30         |
| Shaurya | Get playing mp3 files to work                                               | 40         |

### 2024-01-10 - Tidying up

| Person  | Logs                                                                                       | Time (min) |
| ------- | ------------------------------------------------------------------------------------------ | ---------- |
| Anthony | Add colorful prints and username displays                                                  | 40         |
| Amber   | Work on debugging server disconnecting + client forever loop                               | 40         |
| Shaurya | Add music to game logic                                                                    | 30         |
|         | Refactor game logic, add shuffling continuously new songs and logic to move on after guess | 70         |

### 2024-01-11 - Fix bugs

| Person  | Logs                                                       | Time (min) |
| ------- | ---------------------------------------------------------- | ---------- |
| Anthony | Fix infinite client spam when server disconnects           | 5          |
|         | Understand game.c in preparation to merge                  | 10         |
| Amber   | Implement leaderboard/points with song guessing            | 15         |
| Shaurya | Fix shuffling not working and infinite wrong guessing bugs | 40         |

### 2024-01-12 - Begin merging

| Person  | Logs                                                   | Time (min) |
| ------- | ------------------------------------------------------ | ---------- |
| Anthony | Think about how to organize and merge game into server | 40         |
| Amber   | Think about how to organize and merge game into server | 40         |
| Shaurya | Think about how to organize and merge game into server | 40         |

## 2024-01-14 - Merge music

| Person  | Logs                    | Time (min) |
| ------- | ----------------------- | ---------- |
| Anthony | Merge music into server | 150        |
| Amber   | Merge music into server | 150        |
| Shaurya | Merge music into server | 150        |

## 2024-01-15 - Merge game

| Person  | Logs                        | Time (min) |
| ------- | --------------------------- | ---------- |
| Anthony | Merge game into server      | 0          |
|         | Use ncurses and fix display | 60         |
| Amber   | Merge game into server, working game      | 300          |
| Shaurya | Merge game into server      | 0          |

## NOTES
- the text saying a player is correct only shows up in the host's terminal; players will not know if their guess is correct
- the host can see the correct answer for the song being played 

## BUGS
- the first player's username will show up as "Host" when it's messages are sent out to everyone

