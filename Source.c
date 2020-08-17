// ******************************************
// name Bello Abarchi, Brian Singh Sundesh, Fred Zeder
//zach goes to the track
//*******************************************
#define _CRT_SECURE_NO_WARNINGS
#define PAUSE system("pause")
#define CLS system("cls")
#define FLUSH myFlush()
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#define LB 9
#define UB 1

typedef struct {
	char name[50];
	int horseNumber;
	int payout;
	int oddsLow;
	int oddsHigh;
	int timesWon;
	int timesRaced;
}HORSES;

typedef struct {
	char name[50];
	int bankBalance;
	int wallet;
	int timesWon;
	int amountWon;
}GAMBLER;

void loadHorses(HORSES array[]);
void displayHorse(HORSES horses);
void runARace(HORSES array[], int chosenHorse, double betAmount, double account);
int  horsess();
void displayWinner(HORSES horse, int chosenHorse, double betAmount, double account);
void checking(double* account);
void bankMenu(double balance);
void myFlush();
char getChoice();
double placeBet(double* account, HORSES horse[]);
void savedGame(HORSES horse[], double account, int i);
int main() {
	double account = 0, betAmount = 0;
	HORSES horse[9];
	loadHorses(horse);
	int i = 0;
	int chosenHorse = 0;
	char choice;
	int hhorse[9];
	int h = 0;
	double acccount = 0;
	FILE *ptr;
	srand((unsigned)time(NULL));

	do {
		choice = getChoice();
		switch (choice) {
		case 'A'://Continue
			if (ptr = fopen("savedGame.bin", "rb")) { // open highscoresTopTen.bin 
				if (ptr == NULL) {
					printf("\nError! Could not open file!\n\n");
					PAUSE;
					exit(-1);
				}
				// read highscores from bin file
				fread(&account, sizeof(double), 1, ptr);
				fread(horse, sizeof(HORSES), 9, ptr);
				fread(horse[i].timesRaced, sizeof(HORSES), i, ptr);
				fread(horse[i].timesWon, sizeof(HORSES), i, ptr);
				fclose(ptr);			
				printf("GAME LOADED!!!");
			}
			PAUSE;
			break;
		case 'B':
			checking(&account);
			PAUSE;
			break;
		case 'C'://race
			betAmount = placeBet(&account, horse);
			chosenHorse = horsess();
			runARace(horse, chosenHorse, betAmount, account);
			PAUSE;
			break;

		case 'R'://reset

			break;

		case 'Q':
			savedGame(horse, account, 9);
			printf("quit\n");

			PAUSE;

			break;

		default:

			printf("Invalid selection!\n");

			PAUSE;

			break;

		}

	} while (choice != 'Q');

	PAUSE;
} //End Main

void loadHorses(HORSES array[]) {
	int i = 0;
	strcpy(array[i].name, "Prickly Pete");
	array[i].horseNumber = 1;
	array[i].payout = 2;
	array[i].oddsLow = 1;
	array[i].oddsHigh = 40;
	array[i].timesWon = 0;
	array[i].timesRaced = 0;
	i++; //Horse 1

	strcpy(array[i].name, "Whatever you Name It");
	array[i].horseNumber = 2;
	array[i].payout = 5;
	array[i].oddsLow = 41;
	array[i].oddsHigh = 50;
	array[i].timesWon = 0;
	array[i].timesRaced = 0;
	i++; //Horse 2

	strcpy(array[i].name, "Valencia");
	array[i].horseNumber = 3;
	array[i].payout = 10;
	array[i].oddsLow = 51;
	array[i].oddsHigh = 59;
	array[i].timesWon = 0;
	array[i].timesRaced = 0;
	i++; //Horse 3

	strcpy(array[i].name, "Dennis");
	array[i].horseNumber = 4;
	array[i].payout = 15;
	array[i].oddsLow = 60;
	array[i].oddsHigh = 65;
	array[i].timesWon = 0;
	array[i].timesRaced = 0;
	i++; //Horse 4

	strcpy(array[i].name, "Steve");
	array[i].horseNumber = 5;
	array[i].payout = 50;
	array[i].oddsLow = 66;
	array[i].oddsHigh = 66;
	array[i].timesWon = 0;
	array[i].timesRaced = 0;
	i++; //Horse 5

	strcpy(array[i].name, "Donald Trump");
	array[i].horseNumber = 6;
	array[i].payout = 20;
	array[i].oddsLow = 67;
	array[i].oddsHigh = 70;
	array[i].timesWon = 0;
	array[i].timesRaced = 0;
	i++; //Horse 6

	strcpy(array[i].name, "Horse");
	array[i].horseNumber = 7;
	array[i].payout = 10;
	array[i].oddsLow = 71;
	array[i].oddsHigh = 78;
	array[i].timesWon = 0;
	array[i].timesRaced = 0;
	i++; //Horse 7

	strcpy(array[i].name, "Zach");
	array[i].horseNumber = 8;
	array[i].payout = 5;
	array[i].oddsLow = 79;
	array[i].oddsHigh = 88;
	array[i].timesWon = 0;
	array[i].timesRaced = 0;
	i++; //Horse 8

	strcpy(array[i].name, "John");
	array[i].horseNumber = 9;
	array[i].payout = 3;
	array[i].oddsLow = 89;
	array[i].oddsHigh = 100;
	array[i].timesWon = 0;
	array[i].timesRaced = 0;
	i++;//Horse 9

} //End loadHorses

void displayHorse(HORSES horses) {
	int horse = 0;
	printf("=========================================\n");
	printf("Horse name....: %s\n", horses.name);
	printf("Horse number..: %i\n", horses.horseNumber);
	printf("Horse pays out: %i to 1\n", horses.payout);
	printf("Horse won %i time.\n", horses.timesWon);
	printf("Horse ran %i races.\n", horses.timesRaced);
	printf("=========================================\n\n");

} //End displayHorse

void runARace(HORSES array[], int chosenHorse, double betAmount, double account) {
	int horsePick;
	int i;
	int winningLocation = 0;
	 horsePick = LB + rand() % (UB - LB + 1);
	for (i = 0; i < 9; i++) {
		array[i].timesRaced++;
		if (horsePick >= array[i].oddsLow &&
			horsePick <= array[i].oddsHigh) {
			winningLocation = i;
			array[i].timesWon ++;
		} //End if loop
	} //End for loop
	displayWinner(array[winningLocation], chosenHorse, betAmount, account);
} //End runARace

void displayWinner(HORSES horse, int chosenHorse, double betAmount, double account) {
	printf("!!THE WINNER IS!!\n\n");
	displayHorse(horse);
	if (horse.horseNumber == chosenHorse) {
		printf("\n you won $%i\n", betAmount, horse.payout * 2);

	}
	else{
		printf("you lost: your sold is $%.2lf", account);
	}
} //End displayWinner
void bankMenu(double balance) {
	CLS;
	printf("===========================\n");
	printf("======== ACCOUNT MENU =====\n");
	printf("===========================\n");
	printf("Current Balance: $%.2lf\n", balance);
	printf("============================\n");
	printf("1. Deposit\n");
	printf("2. Withdraw\n");
	printf("3. Return to Main Menu\n\n");
	printf("Enter Your Selection: ");
} // end bankMenu

void checking(double* account) {
	int acctChoice = 0;
	double acct = *account;
	double amount = 0;

	do {
		acct = *account;
		bankMenu(acct);
		scanf("%i", &acctChoice);
		FLUSH;
		CLS;
		printf("Your current balance:$%.2lf\n", *account);
		switch (acctChoice) {
		case 1:// Deposit
			printf("How much do you want to add:$ ");
			scanf("%lf", &amount); FLUSH;
			*account += amount;
			printf("\n New Balance: $%.2lf\n", *account);
			PAUSE;
			break;
		case 2:// Withdraw
			printf("How much do you want to withdraw:$ ");
			scanf("%lf", &amount); FLUSH;
			if (amount >= *account) {
				printf("\nNo Money to Withdraw\n");
				*account = 0;
			}
			else {
				printf("\nYou have Withdraw: $%.2lf", amount);
				*account -= amount;
			}//end if-else statement
			break;
		}// End Switch
	} while (acctChoice != 3);
}// end checking()
double placeBet(double* account, HORSES horse[]) {
	double bet = 0;
	CLS;
	printf("Place your bet: $");
	scanf_s("%lf", &bet);
	while (bet > *account)
	{
		printf("\nBet cannot exceed $%.2lf.\n Place your bet: $", *account);
		scanf_s("%lf", &bet);
	} //end while loop
	if (bet == 0)
	{
		printf("\nYou did not place a bet. ");
		PAUSE;
		return -1;
	}//end if statement
	*account = (*account - bet);
	return bet;
}//end placeBet
int horsess() {
	int horses = 0;
	CLS;
	printf("=================\n");
	printf("Choose your horse\n");
	printf("=================\n");
	printf("Horse Payout Odds\n");
	printf("=================\n");
	printf("  1    2-1    40%%\n");
	printf("  2    5-1    10%%\n");
	printf("  3    10-1   8%%\n");
	printf("  4    15-1   6%%\n");
	printf("  5    50-1   1%%\n");
	printf("  6    20-1   4%%\n");
	printf("  7    10-1   8%%\n");
	printf("  8    5-1    10%%\n");
	printf("  9    3-1    13%%\n\n");
	printf("Enter your choice (1-9): ");
	scanf("%i", &horses);
	FLUSH;
	return horses;
}//end of horse menu
void myFlush() {
	while (getchar() != '\n');
}
void displayMenu() {
	CLS;
	system("color B5");
	printf("\t\t\t\t\t=======================================\n");
	printf("\t\t\t\t\t=======================================\n");
	printf("\t\t\t\t\t==         M A I N   M E N U         ==\n");
	printf("\t\t\t\t\t=======================================\n");
	printf("\t\t\t\t\t=======================================\n\n");
	printf("\t\t\t\t\t[A] Load game\n");
	printf("\t\t\t\t\t[B] Banking\n");
	printf("\t\t\t\t\t[C] Choose your horse and Race\n");//fix it
	printf("\t\t\t\t\t[Q] Save and Quit\n");
	printf("\t\t\t\t\t[R] reset\n");
	printf("\t\t\t\t\tEnter choice: ");
}//end displayMenu
char userChoice(){
	char result;
	displayMenu();
	scanf("%c", &result); FLUSH;
	return toupper(result);
} // end userChoice 
char getChoice(){

	char result;

	displayMenu();

	scanf("%c", &result);

	return toupper(result);

} //end getChoice
  void savedGame(HORSES horse[], double account, int i) {
  FILE *ptr;

  ptr = fopen("savedGame.bin", "wb"); // create savedGame.bin file
  if (ptr == NULL) {
  printf("\nError! Could not open file!\n\n");
  PAUSE;
  exit(-1);
  }
  // save highscores into the bin file
  fwrite(&account, sizeof(double), 1, ptr);
  fwrite(horse, sizeof(HORSES), i, ptr);
  fclose(ptr);

  return;
  } // end saveHighscores
	