#include <stdio.h>
#include <stdlib.h>

struct solution{
  char letter;
  int guessed;
  struct solution* next;
};

void printMan(int errors){
  printf("Errors: %d\n", errors );
  switch(errors){
    case 7: puts("      -----");
    case 6: puts("      |/ °");
    case 5: puts("      | ^W^ ");
    case 4: puts("      | / \\\n      |");
    case 3: puts("    -----");
    case 2: puts("   /     \\ \n  /       \\");
    case 1: puts("===============");
  }
}

// makes lower chars to bigger ones, so that I can compare them more easily
char biggerChar(char toLower){
  if(toLower >='a')
    return toLower-32;
}

//reads solution and saves it in a solution-struct
struct solution* makeStruct(void){
  printf("Which word should be the solution?\n");

  // make struct
  struct solution* beginning = (struct solution*) malloc(sizeof(struct solution));
  struct solution* current = (struct solution*) malloc(sizeof(struct solution));
  struct solution* nextL;
  current->letter = getchar();
  current->next = NULL;
  current->guessed = 0;
  beginning = current;
  char In = biggerChar(getchar());
  while(In>= 'A'){
    nextL = (struct solution*) malloc(sizeof(struct solution));
    nextL->letter = In;
    nextL->next = NULL;
    nextL-> guessed = 0;
    current->next = nextL;
    current = nextL;
    In = biggerChar(getchar());
  }

  system("clear");
  return beginning;
}

//needed to print the solution if not guessed right
void printStruct(struct solution* current){
  if(current == NULL){
    puts("");
    return;
  }
  else{
    printf("%c",current->letter);
    printStruct(current->next);
  }
}

//looks, if the guessed char is in the solution
int charIn(char guess, struct solution* current){
  if(current== NULL)
    return 0;
  if(guess == current->letter){
    current->guessed = 1;
    return charIn(guess,current->next)+1;
  }
  if(guess!= current->letter)
    return charIn(guess, current->next);
}

// looks, if word is now completly guessed
int wordGuessed(struct solution* current){
  if(current == NULL) return 1;
  if(current->guessed == 1) return wordGuessed(current->next);
  return 0;
}


void printGuessedLetters(struct solution* current){
  system("clear");
  if(current == NULL){
    puts("");
    return;
  }
  if(current->guessed == 1)
    printf("%c ", current->letter);
  else
    printf("_ ");
  printGuessedLetters(current->next);
}

void printLatestGuessedLetters(int guessedLetters[]){
  printf("Guessed Letters: ");
  for(int i = 0; i<26; i++){
    if(guessedLetters[i] == 1) printf("%c, ",i+65);
  }
  puts("");
}

int main(void){
  system("clear");
  int errors = 0;
  int guessedLetters[26];
  struct solution* solutionStruct  = makeStruct();
  char guess;

  while(errors<7){
    printf("Which letter?\n");
    guess = biggerChar(getchar());
    if(guess <'A')
      guess = biggerChar(getchar());
    guessedLetters[guess-65] = 1;
    printf("Guess: %c\n", guess);
    if(charIn(guess, solutionStruct)==0)
      errors++;
    printGuessedLetters(solutionStruct);
    if(wordGuessed(solutionStruct) == 1)
      break;
    printMan(errors);
    printLatestGuessedLetters(guessedLetters);
  }

  if(errors<7){
    puts("Congratulations!");
  }
  else{
    printf("You've lost! The word would've been ");
    printStruct(solutionStruct);
  }
  return 0;
}
