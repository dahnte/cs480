# CS480 - Linux Programming
The process of completing CS480's assignments and labs with the help of git version control!

Course Book: _Beginning Linux Programming 4th Edition (Matthew and Stones)_

All assignments have been compiled using gcc 4.8.5 20150623 (Red Hat 4.8.5-44)

### Assignment 1[https://github.com/dahnte/cs480/tree/main/assignment1]
Contains `writing_bog.c` which is a program that will transcribe any _.txt_ file and produce two different files. In this case, the Irish folk song contained in `bog_lyrics.txt` will be transcribed.

The first file, `bog_written.txt`, is simply a char-by-char rewrite of the input _.txt_ file.

The second file, `bog_written_NA.txt`, is a line-by-line rewrite that does not include non-alphabetic characters from the input _.txt_ file.

### Assignment 2[https://github.com/dahnte/cs480/tree/main/assignment2]
Contains `player1.c`, `player2.c`, `string_game.c` and `string_game.h`. In other words, the source code to _57 Pipes_, a two-player string manipulation game.

### Assignment 3[https://github.com/dahnte/cs480/tree/main/assignment3]
Contains `inchworm.c` which is a simulated inchworm holding pen using the _ncurses_ library. Each worm runs on a POSIX thread and follows a set of rules to make sure these critters stay on the screen at all times.
