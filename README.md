# Hey-thats-my-fish
    GAME DESCRIPTION
Hey’ that my Fish! game is a 2-4 player game in which the players first choose a color of penguins and then
take turns moving one of his/her penguins in a straight line as far as he/she wishes, as long as there is a continuous line of
vacant hexagons between the penguin's starting and destination hexagons. The hexagons have 1-3 points and will be
collected when the player's penguin moves out from it. The objective of the game is to collect the most points in the game
to win.

Overview/description of the overall structure of the program:
To start the project, I first created a gameboard by using malloc to store each pointer in each of the 36 spots. 
I then asigned the 8 directions for the pointer and its coresponding data.
There is a separate Record struct to store the score of the player and the AI
Beginning the game, the game board is printed and the player is assigned in the right lower corner while the AI is assigned in the left upper corner. 
They both initialize with 0 point.
The program asks for the player to type in their move and check whether the move is valid by calling legalMove().
If it is not valid, the program will ask the player to type in again until the move is valid.
Then the AI will move and both of the player and ai's score are recorded.
The game continues until both player and Ai is out of move by checking isOutOfMove().

Using pointers to construct the board:
I constructed the board by using malloc. Each position of it stores a data in the board and each pointer points to 8 other pointers showing its 8 directions. Each position can be find by using the indices from malloc. 
Position up is index-6; position down is index+6; position left is index-1; position right is index+1; position up left is index+1;
position up right is index-5; position down left is index+5; and position down right is index+7. 
If some position is outside of the gameboard, assign the pointer pointing to NULL.

Implementing the AI 
Implementation of the AI: The AI is designed to look for a maximum point of each path, compare them, and move. 
First, it will check whether each position is NULL and taken or not. 
If it is not, keep going that path until the pointer points to NULL and get the maximum point of each path. 
There is another pointer called maxPtr and it points to the place that has maximum point.
Check the maximun point in 8 different directions. 
The path with greatest point will have maxPtr point to it and the AI will 
be moving in that direction with that certain steps to get the maximum point.
