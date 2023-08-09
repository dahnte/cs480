<<<<<<< HEAD
# 57 PIPES (Assignment 2)

### Compilation
To compile the game you need to run these two commands:
=======
# ASSIGNMENT 2 - A GAME OF PIPES

Run these two commands in the _assignment2_ file:
>>>>>>> e35b48c55502ee3d53ad00780a9ba25d4d831618

`gcc player1.c stringGame.c -o player1 -std=c99`

`gcc player2.c stringGame.c -o player2 -std=c99`

<<<<<<< HEAD
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
=======
Run _player1_ first and then _player2_ on a separate terminal.
>>>>>>> e35b48c55502ee3d53ad00780a9ba25d4d831618

TODO LIST:
- Makefile

Known bugs:
<<<<<<< HEAD
- Entering more than 16 characters as `player1` causes strange behavior
- Entering more than 1 character during editting as either player also causes strange behavior
- After entering invalid input you may need to hit enter more than once for it
  to register your new input
=======
- Entering more than 16 characters as _player1_ causes strange behavior
- Entering more than 1 character during editting as either player also causes strange behavior
>>>>>>> e35b48c55502ee3d53ad00780a9ba25d4d831618
