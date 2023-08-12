# 57 Pipes - A two-player string manipulation game

### Compilation & Rules
Compile the game by running `make` in the _assignment2_ directory.

Begin the game by running `player1` followed by `player2` on separate terminal instances.

Once both programs are running simultaneously `player1` will be asked to write a string. The string must follow these rules:
- Consists of only 5's and 7's
  - Contains at least two 5's
  - Contains at least two 7's 
- The length of the string is between 4 - 16 characters 

For example, entering the string `5577755575555` will result in:
```
[0]55
[1]777
[2]555
[3]7
[4]5555
```
Each player will be required to remove an index, or chunk, of the string. Each index is made up of the given 5's or 7's. 

### Tips & Strategy
How to win: send your opponent an empty string.

Here are some interesting concepts to use for strategy:

**Minimum edits** - Since the player decides whether they want to remove _all_ or _some_ characters in any given index, it can be said that the **least** amount of edits that can happen during a game is equal to the amount of _indices_ available. Therefore, the minimum amount of edits. 
  - A player who only utilizes this strategy will remove an index completely regardless of how many characters are in it
  - This can be risky as it reduces the amount of turns both players have and may prevent you from seeing through moves
    - If played right you can surprise your opponent

**Maximum edits** - Once again, because the player decides how many characters they want to remove, it can be said that the **most** amount of edits that can happen during a game is equal to the amount of _characters_ available.
  - A player who utilizies this strategy will remove one character from the index regardless of how many characters are in it
  - This can be rewarding as it increases the amount of turns possible giving you more time to set up your future turns
    - If your opponent catches on they may take advantage of your slow playing

These concepts are helpful to develop a strategy during gameplay. A skilled player will utilize both concepts.

In general, try to keep the amount of **minimum edits** you have an _odd_ number. In this case, both the **minimum** and **maximum edits** are _odd_. For example:
```
[0]5
[1]7
[2]5
```
There are an _odd_ amount of indices each with only 1 character to remove. If you were to remove index `[0]` this would leave your opponent with only two **minimum edits** possible (which is an even amount) neither of them making a difference as the final index will be left for you to remove. This will result in you winning the game. In some ways, receiving the string above is sorta like being in check in Chess.

Also consider the effects of combining elements from two different indices:
```
[0]555
[1]7
[2]55
[3]77
[4]5
[5]7777
[6]55
```
Combining `[3]` and `[5]` by removing `[4]` will result in your opponent having an _odd_ amount of **minimum edits**. This can leave you at a disadvantage if you continue to have an even amount of **minimum edits**.

### Bugs & Development
TODO LIST:
- Garbage collection?

Known bugs:
- Entering more than 16 characters as `player1` causes strange behavior
- After entering invalid input you may need to hit enter more than once for it
  to register your new input
