# 57 PIPES (Assignment 2)

### Compilation
To compile the game you need to run these two commands:
`gcc player1.c stringGame.c -o player1 -std=c99`

`gcc player2.c stringGame.c -o player2 -std=c99`

To start playing first run `player1` and then `player2` on a separate terminal

### Game Rules
Once both programs are running simultaneously, `player1` will be asked to write
a string. The string must follow these rules:
- Contains no other characters besides 5 and 7
- Contains at least two 5's
- Contains at least two 7's 
- The length of the string is between 4 - 16 characters 

Some examples of a valid starting string:
`5757`
`5775575775575575`

### Strategy
The goal is 

TODO LIST:
- Makefile

Known bugs:
- Entering more than 16 characters as `player1` causes strange behavior
- Entering more than 1 character during editting as either player also causes strange behavior
- After entering invalid input you may need to hit enter more than once for it
  to register your new input
