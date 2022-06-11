
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Grid {
      char* aiDirection;
      char data;
      struct Grid * up;
      struct Grid * down;
      struct Grid * left;
      struct Grid * right;
      struct Grid * upLeft;
      struct Grid * upRight;
      struct Grid * downLeft;
      struct Grid * downRight;
};

//This structure records the score of the game
struct Record{
    int score;
};

//This structure make a gameboard and connect each ptr to each other using malloc and pointers
//Return a pointer pointing to the first address of the grid
struct Grid* makeBoard(){
    struct Grid* ptr;
    ptr = malloc(36*sizeof(struct Grid));
    //Assign data for each ptr
    for(int i = 0; i < 36; i++){
        (ptr+i)->data = 1;
        if((i>=7&&i<=10)||(i>=13&&i<=16)||(i>=19&&i<=22)||(i>=25&&i<=28)){
            (ptr+i)->data = 2;
        }
        if(i==14||i==15||i==20||i==21){
            (ptr+i)->data = 3;
        }
    }

    //Assign position for each ptr
    for(int i = 0; i < 36; i++){
        (ptr+i)->up = &ptr[i-6];
        (ptr+i)->down = &ptr[i+6];
        (ptr+i)->left = &ptr[i-1];
        (ptr+i)->right = &ptr[i+1];
        (ptr+i)->upLeft = &ptr[i-7];
        (ptr+i)->upRight = &ptr[i-5];
        (ptr+i)->downLeft = &ptr[i+5];
        (ptr+i)->downRight = &ptr[i+7];

        if(i < 6){
          (ptr+i)->up = NULL;
          (ptr+i)->upLeft = NULL;
          (ptr+i)->upRight = NULL;
        }

        if(i % 6 == 0){
          (ptr+i)->left = NULL;
          (ptr+i)->downLeft = NULL;
          (ptr+i)->upLeft = NULL;
        }

        if(i==5||i==11|i==17|i==23|i==29|i==35){
          (ptr+i)->right = NULL;
          (ptr+i)->downRight = NULL;
          (ptr+i)->upRight = NULL;
        }

        if(i >= 30){
          (ptr+i)->down = NULL;
          (ptr+i)->downLeft = NULL;
          (ptr+i)->downRight = NULL;
        }
    }

    return ptr;
};


//This function checks if the move that the user input is valid or not
int legalMove(char* direction, int number, struct Grid* ptr){
    struct Grid* newP = ptr;
    if(strcasecmp(direction,"up")==0){
        for(int i = 0; i<number; i++){
            if(newP->up==NULL){
                return 0;
            }
            if((newP->up->data=='.')||(newP->up->data=='A')){
                return 0;
            }
            newP = newP->up;
        }
        return 1;
    }
    else if(strcasecmp(direction,"down")==0){
        for(int i = 0; i<number; i++){
            if(newP->down==NULL){
                return 0;
            }
            if((newP->down->data=='.')||(newP->down->data=='A')){
                return 0;
            }
            newP = newP->down;
        }
        return 1;
    }
    else if(strcasecmp(direction,"left")==0){
        for(int i = 0; i<number; i++){
            if(newP->left==NULL){
                return 0;
            }
            if((newP->left->data=='.')||(newP->left->data=='A')){
                return 0;
            }
            newP = newP->left;
        }
        return 1;
    }
    else if(strcasecmp(direction,"right")==0){
        for(int i = 0; i<number; i++){
            if(newP->right==NULL){
                return 0;
            }
            if((newP->right->data=='.')||(newP->right->data=='A')){
                return 0;
            }
            newP = newP->right;
        }
        return 1;
    }
    else if(strcasecmp(direction,"upleft")==0){
        for(int i = 0; i<number; i++){
            if(newP->upLeft==NULL){
                return 0;
            }
            if((newP->upLeft->data=='.')||(newP->upLeft->data=='A')){
                return 0;
            }
            newP = newP->upLeft;
        }
        return 1;
    }
    else if(strcasecmp(direction,"upright")==0){
        for(int i = 0; i<number; i++){
            if(newP->upRight==NULL){
                return 0;
            }
            if((newP->upRight->data=='.')||(newP->upRight->data=='A')){
                return 0;
            }
            newP = newP->upRight;
        }
        return 1;
    }
    else if(strcasecmp(direction,"downLeft")==0){
        for(int i = 0; i<number; i++){
            if(newP->downLeft==NULL){
                return 0;
            }
            if((newP->downLeft->data=='.')||(newP->downLeft->data=='A')){
                return 0;
            }
            newP = newP->downLeft;
        }
        return 1;
    }
    else if(strcasecmp(direction,"downright")==0){
        for(int i = 0; i<number; i++){
            if((newP->downRight==NULL)||(newP->downRight->data=='A')){
                return 0;
            }
            if(newP->downRight->data=='.'){
                return 0;
            }
            newP = newP->downRight;
        }
        return 1;
    }

    return 0;
}

//This function checks if there is still path to go
int isOutOfMove(struct Grid *ptr){
    if((ptr->up==NULL)&&(ptr->down==NULL)&&(ptr->left==NULL)&&(ptr->right==NULL)&&(ptr->upLeft==NULL)
    &&(ptr->upRight==NULL)&&(ptr->downLeft==NULL)&&(ptr->downRight==NULL)){
        return 1;
    }
    return 0;
}

//This function move the player penguin as they desire
struct Grid* move(struct Grid *curPtr,char*direction, int number, int* playerScore,char name){
    struct Grid * ptr = curPtr;
    ptr->data = '.';
    for(int i = 0; i<number; i++){
        if(strcasecmp(direction,"up")==0){
            ptr = ptr->up;
        }
        else if(strcasecmp(direction,"down")==0){
            ptr = ptr->down;
        }
        else if(strcasecmp(direction,"left")==0){
            ptr = ptr->left;
        }
        else if(strcasecmp(direction,"right")==0){
            ptr = ptr->right;
        }
        else if(strcasecmp(direction,"upLeft")==0){
            ptr = ptr->upLeft;
        }
        else if(strcasecmp(direction,"upRight")==0){
            ptr = ptr->upRight;
        }
        else if(strcasecmp(direction,"downLeft")==0){
            ptr = ptr->downLeft;
        }
        else {
            ptr = ptr->downRight;
        }
    }
    (*playerScore) = (*playerScore)+(int)(ptr->data);
    if(name=='P'){
      ptr->data = 'P';
    }
    else{
      ptr->data = 'A';
    }
    return ptr;

}

int aiNumMove(struct Grid *aiPtr) {
  char* maxDir;
  int maxMove = 0;
  struct Grid *prev = aiPtr;
  int i = 0;
  int numMove = 0;
  while(prev->up != NULL){
    i++;
    if(prev->up->data != 'P' && prev->up->data != '.'){
      if(prev->up->data > maxMove){
        maxMove = prev->up->data;
        numMove = i;
        maxDir = "up";
      }
      prev = prev->up;
    }
    else{
      break;
    }
    if(prev->up == NULL){
      break;
    }
  }

  i = 0;
  prev = aiPtr;
  while(prev->down != NULL){
    i++;
    if(prev->down->data != 'P' && prev->down->data != '.'){
      if(prev->down->data > maxMove){
        maxMove = prev->down->data;
        numMove = i;
        maxDir = "down";
      }
      prev = prev->down;
    }
    else{
      break;
    }
    if(prev->down == NULL){
      break;
    }
  }

  i = 0;
  prev = aiPtr;
  while(prev->left != NULL){
    i++;
    if(prev->left->data != 'P' && prev->left->data != '.'){
      if(prev->left->data > maxMove){
        maxMove = prev->left->data;
        numMove = i;
        maxDir = "left";
      }
      prev = prev->left;
    }
    else{
      break;
    }
    if(prev->left == NULL){
      break;
    }
  }

  i = 0;
  prev = aiPtr;
  while(prev->right != NULL){
    i++;
    if(prev->right->data != 'P' && prev->right->data != '.'){
      if(prev->right->data > maxMove){
        maxMove = prev->right->data;
        numMove = i;
        maxDir = "right";
      }
      prev = prev->right;
    }
    else{
      break;
    }
    if(prev->right == NULL){
      break;
    }
  }

  i = 0;
  prev = aiPtr;
  while(prev->upRight != NULL){
    i++;
    if(prev->upRight->data != 'P' && prev->upRight->data != '.'){
      if(prev->upRight->data > maxMove){
        maxMove = prev->upRight->data;
        numMove = i;
        maxDir = "upRight";
      }
      prev = prev->upRight;
    }
    else{
      break;
    }
    if(prev->upRight == NULL){
      break;
    }
  }

  i = 0;
  prev = aiPtr;
  while(prev->upLeft != NULL){
    i++;
    if(prev->upLeft->data != 'P' && prev->upLeft->data != '.'){
      if(prev->upLeft->data > maxMove){
        maxMove = prev->upLeft->data;
        numMove = i;
        maxDir = "upLeft";
      }
      prev = prev->upLeft;
    }
    else{
      break;
    }
    if(prev->upLeft == NULL){
      break;
    }
  }

  i = 0;
  prev = aiPtr;
  while(prev->downRight != NULL){
    i++;
    if(prev->downRight->data != 'P' && prev->downRight->data != '.'){
      if(prev->downRight->data > maxMove){
        maxMove = prev->downRight->data;
        numMove = i;
        maxDir = "downRight";
      }
      prev = prev->downRight;
    }
    else{
      break;
    }
    if(prev->downRight == NULL){
      break;
    }
  }

  i = 0;
  prev = aiPtr;
  while(prev->downLeft != NULL){
    i++;
    if(prev->downLeft->data != 'P' && prev->downLeft->data != '.'){
      if(prev->downLeft->data > maxMove){
        maxMove = prev->downLeft->data;
        numMove = i;
        maxDir = "downLeft";
      }
      prev = prev->downLeft;
    }
    else{
      break;
    }
    if(prev->downLeft == NULL){
      break;
    }
  }

  aiPtr->aiDirection = maxDir;
  return numMove;
}

int main(void) {

struct Record playerRecord;
struct Record aiRecord;
struct Grid* player;
struct Grid* ptr = makeBoard();
printf("data of position ptr-35 is %d\n", (ptr-35)->data);
struct Grid* ai = (ptr-35);

playerRecord.score = 0;
aiRecord.score = 0;
int playerIndex = 35;
int aiIndex = 0;
player = &ptr[playerIndex]; //assign position to the player
ai = &ptr[aiIndex]; //assign position to the ai;
ptr[playerIndex].data = 'P';
ptr[aiIndex].data = 'A';

printf("\nHEY, THAT'S MY FISH!\n");
printf("Type your move in \"DIRECTION NUMBER\" format!\n(UP, DOWN, LEFT, RIGHT, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT)\nExample: \"UP 3\" will move the Penguin up 3 tiles\n");

for(int i = 0; i < 36; i++){
  if((i)%6 == 0){
      printf("\n");
  }
  if(ptr[i].data == 'P'||(ptr+i)->data == 'A'){
      printf("%c ",(ptr+i)->data);
  }
  else
      printf("%i ",(ptr+i)->data);
  }
printf("\n");

size_t size = 32;
char* buffer = (char*)malloc(size*sizeof(char));
if(buffer == NULL){
  perror("Unable to allocate buffer");
  exit(1);
}
char* direction = (char*)malloc(size*sizeof(char));
int number;
printf("Enter your move: ");
getline(&buffer,&size,stdin);
sscanf(buffer,"%s %d",direction,&number); //get the input from player
printf("\n");

//if both player is not out of move then coninue playing
while(isOutOfMove(player)==0 || isOutOfMove(ai)==0){
//if the move is invalid, tell user to type again
    while(legalMove(direction,number,player)==0){
        printf("Invalid input! Please try again.\nEnter your move: ");
        getline(&buffer,&size,stdin);
        sscanf(buffer,"%s %d",direction,&number);
        printf("\n");
    }
    //while the user type in a valid move, move P and print out the board game
    while (legalMove(direction,number,player)==1)
    {
        //let player go first
        if(isOutOfMove(player)==0){
            player = move(player,direction,number,&playerRecord.score,'P');
        }
        //let AI go after
        if(isOutOfMove(ai)==0){
          int num = aiNumMove(ai);
          ai = move(ai,ai->aiDirection,num,&aiRecord.score,'A');
            // ai = AImove(ai,&aiRecord.score);
            //move(struct Grid *curPtr,char*direction, int number, int* playerScore)
        }
        //print out the game board
        for(int i = 0; i < 36; i++){
        if((i)%6 == 0){
            printf("\n");
        }
        if(ptr[i].data == 'P'||ptr[i].data == 'A'||ptr[i].data == '.'){
            printf("%c ",ptr[i].data);
        }
        else
            printf("%i ",ptr[i].data);
        }
        printf("\n");

        printf("AI's score: %i\n",aiRecord.score);
        printf("Your score: %i\n",playerRecord.score);
        if(isOutOfMove(player)==0){
        printf("Enter your move: ");
        getline(&buffer,&size,stdin);
        sscanf(buffer,"%s %d",direction,&number);
        }
        if(isOutOfMove(player)==1 && isOutOfMove(ai)==0){
          while(isOutOfMove(ai)==0){
            for(int i = 0; i < 36; i++){
            if((i)%6 == 0){
                printf("\n");
            }
            if(ptr[i].data == 'P'||ptr[i].data == 'A'||ptr[i].data == '.'){
                printf("%c ",ptr[i].data);
            }
            else
                printf("%i ",ptr[i].data);
            }
            printf("\n");

            printf("AI's score: %i\n",aiRecord.score);
            printf("Your score: %i\n",playerRecord.score);
          }
        }
        if(isOutOfMove(player)==1 && isOutOfMove(ai)==1){
          break;
        }
    }
}
//print out the results of the game:
printf("Player's points: %i\n",playerRecord.score);
printf("AI's points: %i\n",aiRecord.score);
if(playerRecord.score>aiRecord.score){
    printf("Player Wins!");
}
else if(playerRecord.score<aiRecord.score){
    printf("AI Wins!");
}
else printf("Draw");
    return 0;
}
