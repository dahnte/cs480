# 57 Pipes - A two-player string manipulation game


### Compilation
Compile the game by running `make` in the _assignment2_ directory.

Begin the game by running `player1` followed by `player2` on separate terminal instances.

### Rules & Strategy
Once both programs are running simultaneously `player1` will be asked to write a string. The string must follow these rules:
- Consists of only 5's and 7's
  - Contains at least two 5's
  - Contains at least two 7's 
- The length of the string is between 4 - 16 characters 

To win you must be the player to make the final edit and remove the last bit of the string.
- During gameplay try to maintain an odd amount of indicies
- Try to break up indicies with only 1 character in them by removing the index
  between them

### Bugs & Development
TODO LIST:
- Garbage collection?

Known bugs:
- Entering more than 16 characters as `player1` causes strange behavior
- After entering invalid input you may need to hit enter more than once for it
  to register your new input
