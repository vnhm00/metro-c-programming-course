My battleship program is a game for a single player with a computer.<br>
The project.c is the source code in MCUXpresso.<br>
I also attachted computer.c to simulate the computer function. It runs till all of ship are sunk.<br>

Improvement:<br>
∘ I was able to code a program for a player with a computer, not the player plays him or herself.<br>
∘ The grid initialization will ensure randomly located ships and ensure there won't 
be ships located next to each other (at least 1 square away).<br>
∘ The user input is checked.<br>
∘ The computer, besides fire shots at random coordinates, can sink a player ship if one part of the ship is hit.<br>
To be specific, if a ship is hit, the computer then picks randomly 1 out of 4 directions to shot.<br>
If it missed, the computer picks another direction. And if for example, the middle of the ship is hit,
after the computer hits that ship in one direction, it will return in the opposite direction.<br>

Missing points:<br>
∘ The user input is only checked whether that coordinate is already hit or the coordinate is out of the grid range.
The program doesn't check if a character is entered.<br>
∘ If there aren't any ships is hitting, the computer player doesn't choose the coordinate wisely.
The coordinate will be chosen randomly as long as that coordinate hasn't been hit.<br>
∘ The program is quite slow to run in MCU.<br>
∘ As I planned at the beginning, a player can shot 5 hits at a turn to speed up the playing time.<br>
∘ The computer turn function can be better. I wish I have more time to fix this.<br>

