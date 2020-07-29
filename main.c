#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* Variable Declarations */
int upper = 10; /* Declares the highest value card */
int lower = 1; /* Declares the lowest value card */
int pdeck[10]; /* Declares the player's 'hand' (max 10 cards) */
int psum = 0; /* Declares the player's total */
int pplace = 0; /* Starting place of player's deck */
int ddeck[10]; /* Declares the dealer's 'hand' (max 10 cards) */
int dsum = 0; /* Declares the dealer's total */
int dplace = 0; /* Starting place of dealer's deck */
/* Function Declarations */
void givecard(char who, int times); /* p or d | any */
void displaycards(char who); /* p, h, or d */

int main(){
  while (1){ /* Makes the program continuous without having to re-run the executable */
    char input[10];
    srand(time(0)); /* Generates the random key needed for randomness */
    system("cls"); /* This command is used to clear console for better looks */
    printf("\nWelcome to Blackjack!\n==========\n\n");
    /* ==========Starting Deal (2 cards for each)========== */
    givecard('d',2);
    givecard('p',2);
    displaycards('h');
    displaycards('p');
    /* ==========PLAYER'S TURN========== */
    while (1){ /* Creates loop until break */
      printf("Hit or Stand?: ");
      scanf("%s",input);
      if (strcmp(input,"h")==0||strcmp(input,"hit")==0||strcmp(input,"Hit")==0||strcmp(input,"H")==0){ /* Hits player with a card */
        system("cls");
        printf("You Hit.\n==========\n\n");
        givecard('p',1);
        displaycards('h');
        displaycards('p');
      }
      if (strcmp(input,"s")==0||strcmp(input,"stand")==0||strcmp(input,"Stand")==0||strcmp(input,"S")==0){ /* Lets the player Stand */
        system("cls");
        printf("You Stand.\n==========\n\n");
        break;
      }
      if (psum >= 21){ /* Will break them out regardless if they bust/blackjack */
        break;
      }
    }
    if (psum > 21){ /* Result for Bust */
      system("cls");
      printf("\nYou Busted!\n==========\n\n");
    }
    else if (psum == 21){ /* Result for Blackjack */
      system("cls");
      printf("\nYou Hit Blackjack!\n==========\n\n");
    }
    /* ==========DEALER'S TURN========== */
    while (1){ /* Heck of a lot shorter without interfacing */
      if (dsum < 17){ /* Dealer stops at 17 or higher, per Blackjack standard rules */
        givecard('d',1);
      }
      if (dsum >= 17){
        break;
      }
    }
    displaycards('d'); /* Shows the player what the dealer's deck now is */
    displaycards('p');
    if (dsum > 21){ /* Result for Dealer Bust */
      printf("\nDealer Busted!\n");
    }
    else if (dsum == 21){ /* Result for Dealer Blackjack */
      printf("\nDealer Hit Blackjack!\n");
    }
    /* ==========ALL THE WIN/LOSE/TIE CHECKS | "else if"s to prevent overlap========== */
    if (psum > 21){ /* If you bust, automatic loss */
      printf("\n:( You Lose :(\n");
    }
    else if (psum == 21 && dsum == 21){ /* If both Blackjack, instant tie */
      printf("\n:| It's a Tie :|\n");
    }
    else if (dsum > 21){ /* (By this point, you can only have <=21; If dealer bust, you win */
      printf("\n:) You Win :)\n");
    }
    else if (psum > dsum){ /* If you have more than dealer, you win */
      printf("\n:) You Win :)\n");
    }
    else if (dsum > psum){ /* If you have less than dealer, you lose */
      printf("\n:( You Lose :(\n");
    }
    else if (psum == dsum){ /* If your values are equal, it's a tie */
      printf("\n:| It's a Tie :|\n");
    }
    /* ==========CONTINUE REQUEST========== */
    printf("\nContinue? (y/n): ");
    scanf("%s",input);
    if (strcmp(input,"n")==0||strcmp(input,"N")==0){ /* If no, program fully exits */
      return 0;
    }
    /* ==========RESET SEQUENCE | To bring game back to square one========== */
    memset(pdeck, 0, 10 * sizeof(pdeck[0])); /* Resets the deck array */
    psum = 0; /* Returns sum to 0 */
    pplace = 0; /* Returns place to 0 */
    memset(ddeck, 0, 10 * sizeof(ddeck[0]));
    dsum = 0;
    dplace = 0;
  }
}

/* ====================Functions==================== */

/* Adds card(s) to p/d's hand, performing Ace checks as well */
void givecard(char who, int times){ /* who: p (player) or d (dealer) | times: any int */
  int i;
  int randnum;
  if (who == 'p'){ /* Dealing to player */
    for(i=0;i<times;i++){ /* Performs the loop as many times as designated in the function call */
      randnum = (rand() % (upper -lower + 1)) + lower; /* Generate the random number */
      if (randnum == 1){ /* For if the card is an Ace */
        if (psum < 11){ /* If the total hand sum is less than 11, Ace will be 11; otherwise, it will remain a 1 */
          randnum = 11;
        }
      }
      pdeck[pplace] = randnum; /* Actually sets the card in the hand */
      psum += randnum; /* Adds card value to overall hand sum */
      pplace++; /* Increases the next place in the hand by 1 */
      if (psum > 21){ /* Ace changes for if player has busted */
        for(i=0;i<pplace;i++){ /* Checks through the whole hand for an Ace (11) */
          if (pdeck[i] == 11){ /* If busted and an 11 exists, value is reset to 1 */
            pdeck[i] = 1; /* Sets the 11 to 1 */
            psum -= 10; /* Subtracts lost value from the sum */
            if (psum < 22){ /* Stops the for loop whenever the bust is fixed */
              break;
            }
          } /* So */
        } /* Many */
      } /* Brackets */
    }
  }
  if (who == 'd'){ /* Dealing to dealer | all the rest is the same as player */
    for(i=0;i<times;i++){
      randnum = (rand() % (upper -lower + 1)) + lower;
      if (randnum == 1){
        if (psum < 11){
          randnum = 11;
        }
      }
      ddeck[dplace] = randnum;
      dsum += randnum;
      dplace++;
      if (dsum > 21){
        for(i=0;i<dplace;i++){
          if (ddeck[i] == 11){
            ddeck[i] = 1;
            dsum -= 10;
            if (dsum < 22){
              break;
            }
          }
        }
      }
    }
  }
}

/* Displays the cards of a desired hand */
void displaycards(char who){ /* who: p (player), h (hidden), d (dealer) */
  int i;
  if(who == 'p'){ /* To display Player's hand */
    printf("Your Cards:\n");
    for(i=0;i<pplace;i++){
      if(i == 0){ /* Very first card won't have the "| " to make output look good */
        printf("[%d] ",pdeck[i]);
      }
      else{
        printf("| [%d] ",pdeck[i]); /* All other cards will */
      }
    }
    printf("= %d\n\n",psum); /* Appends the sum of the cards to the end for ease of reading */
  }
  else if(who == 'h'){ /* To display the 'Hidden' hand (dealer's starter hand) */
    printf("Dealer's Cards:\n");
    printf("[X] | [%d] = ?\n\n",ddeck[1]);
  }
  else if(who == 'd'){ /* To display Dealer's hand */
    printf("Dealer's Cards:\n");
    for(i=0;i<dplace;i++){
      if(i == 0){
        printf("[%d] ",ddeck[i]);
      }
      else{
        printf("| [%d] ",ddeck[i]);
      }
    }
    printf("= %d\n\n",dsum);
  }
}

/* And that's all! C go fast! */
