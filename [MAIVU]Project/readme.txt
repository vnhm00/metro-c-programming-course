My battleship program is a game for a single player with a computer.
The project.c is the source code in MCUXpresso.
I also attachted computer.c to simulate the computer function. It runs till all of ship are sunk.





Improvement: 

- I was able to code a program for a player with a computer, not the player plays him or herself.

- The grid initialization will ensure randomly located ships
  and ensure there won't be ships located next to each other (at least 1 square away).

- The user input is checked.

- The computer, besides fire shots at random coordinates, can sink a player ship if one part of the ship is hit. 
  To be specific, if a ship is hit, the computer then picks randomly 1 out of 4 directions to shot. 
  If it missed, the computer picks another direction. And if for example, the middle of the ship is hit,
  after the computer hits that ship in one direction, it will return in the opposite direction.



Missing points:

- The user input is only checked whether that coordinate is already hit or the coordinate is out of the grid range. 
  The program doesn't check if a character is entered.

- If there aren't any ships is hitting, the computer player doesn't choose the coordinate wisely.
  The coordinate will be chosen randomly as long as that coordinate hasn't been hit.

- The program is quite slow to run.

- As I planned at the beginning, a player can shot 5 hits at a turn to speed up the time.

- The computer turn function can be better. I wish I have more time to fix this.

