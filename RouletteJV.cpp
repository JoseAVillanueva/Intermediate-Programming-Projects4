//Name: Jose Villanueva Vigil
//Course: COSC 2436
//Program set 1, REQUIRED PROGRAM (Roulette)
//References: I used the PDF covering program set 1
//=================================================================================

#include <iostream>
#include <random>
#include <string>

using namespace std;

//this is a class defined with the data type of Player, this will be used to create 
//an instance of the Player that will track the amount of money in a players balance 
class Player
{

//a private integer called MoneyAmount is defined 
private:
	int MoneyAmount;

public:

	//the Player defualt constructor is used to initalize MoneyAmount to 0
	Player()
	{
		MoneyAmount = 0;
	}

	//The Player overloaded constructor is used to initalize MoneyAmount to amount
	Player(int amount)
	{
		MoneyAmount = amount;
	}

	//the BetEarningsAdd member function is used to add money to the players MoneyAmount using amount
	void BetEarningsAdd(int amount)
	{
		MoneyAmount += amount;
	}

	//the BetEarningsSubtract member function is used to subtract money from the players MoneyAmount using amount
	void BetEarningsSubtract(int amount)
	{
		MoneyAmount -= amount;
	}

	//the setMoneyAmount member function is used to set the players MoneyAmount to amount
	void setMoneyAmount(int amount)
	{
		MoneyAmount = amount;
	}

	//the getMoneyAmount member function is used to return the players MoneyAmount 
	int getMoneyAmount()const
	{
		return MoneyAmount;
	}
};

const int ROWS = 13;
const int COLUMNS = 3;

//a 2D array of integers is defined here, this will hold the integer values
//for the roulette table
int RouletteTableNumbers[ROWS][COLUMNS] =
{
	0,0,00,
	1,2,3,
	4,5,6,
	7,8,9,
	10,11,12,
	13,14,15,
	16,17,18,
	19,20,21,
	22,23,24,
	25,26,27,
	28,29,30,
	31,32,33,
	34,35,36
};

//a 2D array of bools is defined here, this will hold bool values that will
//determine the color of the roulette number
bool RouletteTableColors[ROWS][COLUMNS] =
{
	false,false,false, //this is where the 0 and 00 are located 
	true,false,true,   //this is the beginning of the first dozen
	false,true,false,
	true,false,true,
	false,false,true,
	false,true,false,   //this is the beginning of the second dozen
	true,false,true,
	true,false,true,
	false,true,false,
	true,false,true,   //this is the beginning of the third dozen
	false,false,true,
	false,true,false,
	true,false,true
};

int BettingOption = 0;
int BettingMoney = 0;
int StartingMoney = 0;
char ProgramRun = ' ';
char GameMode = ' ';

//these are the function that will be utilized throughout the program
//their descriptions can be found towards the bottom of the program
void RouletteFunctions(int[ROWS][COLUMNS], bool[ROWS][COLUMNS], int, int, char, Player*);
bool DetermineRouletteStatus(int);
void PrintTable();
void Multiplier(const int, int, Player*);

//these are all the functions that will be used for the bets 
void SingleNumbersBet(int, int, Player*);
void AdjacentNumbersBet(int[ROWS][COLUMNS], int, int, Player*);
void RowsBet(int, int, int, Player*);
void CornerBet(int[ROWS][COLUMNS], int, int, Player*);
void TwoRowsBet(int, int, Player*);

void ColumnsBet(bool, int, int, int, Player*);
void ColorBet(bool, bool, int, int, Player*);
void DozenBet(bool, int, int, Player*);
void EvenOddBet(bool, int, int, Player*);
void LowHiBet(bool, int, int, Player*);


int main()
{
	bool BettingFlag = false;
	double MoneyCheck = 0;
	int RemainingMoney = 0;

	cout << "===================================================================================" << endl;
	cout << "IMPORTANT NOTICE" << endl << endl;
	cout << "-If you enter a (00), it will output a (0)." << endl;
	cout << "-If you enter a (0) for the computer roll in Test Mode, or the computer rolls a (0)" << endl;
	cout << "in Game Mode, and the bet made is an outside bet, it will always loose." << endl;
	cout << "(this was done to mimic roulette outside bet system where a 0 would cause you to lose) " << endl;
	cout << "===================================================================================" << endl << endl;

	//the player enters the a GameMode option here
	cout << "Enter the playing mode(G/T): ";
	cin >> GameMode;
	GameMode = toupper(GameMode);

	//the while loop will continue to loop until a valid option is made
	while (GameMode != 'G' && GameMode != 'T')
	{
		cout << "Aninvalid mode was entered, please try again.\n";
		cout << "Enter the playing mode(G/T): ";
		cin >> GameMode;
		GameMode = toupper(GameMode);
		cout << endl;
	}
	cout << endl;

	//the player enters the StartingMoney here
	cout << "Enter the starting amount of money: ";
	cin >> StartingMoney;
	cout << endl;

	cout << "Player starts with " << StartingMoney << " dollars. " << endl << endl;

	//A new pointer with the data type of Player is made here
	Player* PlayerPtr = nullptr;

	//The PlayerPtr allocates memory to create a new instance of the Player class that is initalized using StartingMoney
	PlayerPtr = new Player(StartingMoney);

	//RemainingMoney is set to StartingMoney
	RemainingMoney = StartingMoney;

	//the while loop will continue to loop until the RemainingMoney is 0 or until the player enters 'N'
	while (ProgramRun != 'N' && RemainingMoney > 0)
	{
		
		//the player enters the amount they'd like to bet here
		cout << "How much to bet (5-dollar increments): ";
		cin >> BettingMoney;

		//the while loop will contiue to loop until bettingFlag is true
		while (BettingFlag != true)
		{

			//the following equation is used to determine if the betting amount entered is divisible by 5
			MoneyCheck = static_cast<double>((BettingMoney / static_cast<double>((BettingMoney / 5))));

			//if the betting amount made is greater than the amount within the players balance, an error message will be displayed
			if (BettingMoney > PlayerPtr->getMoneyAmount())
			{
				cout << "You are betting more money than whats listed in the player's account, please try again.\n";
				cout << "How much to bet (5-dollar increments): ";
				cin >> BettingMoney;
			}

			//the following equation is used to determine if the betting amount entered is divisible by 5
			MoneyCheck = static_cast<double>((BettingMoney / static_cast<double>((BettingMoney / 5))));

			//if the betting amount is not divisble by 5, then an error is displayed 
			if (MoneyCheck != 5)
			{
				cout << "The betting amount entered can not be incremented by values of 5 dollar's, please try again.\n";
				cout << "How much to bet (5-dollar increments): ";
				cin >> BettingMoney;
			}

			//if the MoneyCheck variable is equal to 5, then the BettingFlag is set to true
			else if (MoneyCheck == 5)
			{
				BettingFlag = true;
			}
		}

		//BettingFlag is set to false and the betting amount is removed from the players amount using
		//BetEarningSubtarct() function 
		BettingFlag = false;
		PlayerPtr->BetEarningsSubtract(BettingMoney);
		cout << endl;

		cout << "1.   Single Number\n";
		cout << "2.   Adjacent Numbers\n";
		cout << "3.   Row\n";
		cout << "4.   Corner\n";
		cout << "5.   2 Rows\n";
		cout << "6.   Column\n";
		cout << "7.   Dozen\n";
		cout << "8.   Color\n";
		cout << "9.   Even/Odd\n";
		cout << "10.  Low/Hi\n" << endl;

		//the player enters a betting option here
		cout << "Enter the type of bet: ";
		cin >> BettingOption;

		//the while loop continue to loop until a valid option is made
		while (BettingOption < 0 && BettingOption > 10)
		{
			cout << "An invalid betting option was made, please try again.\n";
			cout << "Enter the type of bet: ";
			cin >> BettingOption;
		}

		//the RouletteFunction function is called, RouletteTableNumbers, RouletteTableColors,
		//BettingOption, BettingMoney, GameMode, and PlayerPtr
		RouletteFunctions(RouletteTableNumbers, RouletteTableColors,
			BettingOption, BettingMoney, GameMode, PlayerPtr);


		RemainingMoney = PlayerPtr->getMoneyAmount();

		//if RemainingMoney is equal to zero, then the lose message for runing out of money is displayed and the program ends
		if (RemainingMoney == 0)
		{
			cout << endl;
			cout << "You ran out of money, better luck next time!" << endl;
			cout << "Thanks for playing!" << endl;
			ProgramRun = 'N';
		}

		//otherwise, the player is asked if the would like to play again
		else
		{
			cout << "Player has " << PlayerPtr->getMoneyAmount() << " dollars." << endl << endl;
			cout << "Run again (Y/N): ";
			cin >> ProgramRun;
			ProgramRun = toupper(ProgramRun);
		}

		//the while loop will continue to loop until a valid option is made 
		while (ProgramRun != 'Y' && ProgramRun != 'N')
		{
			cout << "An invalid run option was made, please try again.\n";
			cout << "Run again (Y/N): ";
			cin >> ProgramRun;
			ProgramRun = toupper(ProgramRun);
			cout << endl;
		}
		cout << endl;
	}
	return 0;
}

/*-------------------------------------------------------------------------------------------

RouletteFunctions function is used to determine a random roulette number and to allow the player
to enter a roulette number, it will also determine which betting fuction to select based on the 
bet type made by the user 

-Within the parameter list, a 2D array of integer variables is passed, with its sizes
(RouletteValues is passed with ROWS and COLUMNS)
-Within the parameter list, a 2D array of bools is passed, with its sizes 
(RouletteFlags is passed with ROWS and COLUMNS)
-Within the parameter list, two integer variables are passed (BettingOpt and Money)
-Within the parameter list, a character variable is passed (mode)
-Within the parameter list, a pointer with the data type of Player is passed (Ptr)

--------------------------------------------------------------------------------------------*/

void RouletteFunctions(int RouletteValues[ROWS][COLUMNS], bool RouletteFlags[ROWS][COLUMNS],
	int BettingOpt, int Money, char mode, Player* Ptr)
{
	bool RouletteFlag = false;
	bool RoultteFlagColor = false;

	const int MinRow = 0;
	const int MaxRow = 12;
	const int MinColumn = 0;
	const int MaxColumn = 2;

	int RandomRow = 0;
	int RandomColumn = 0;
	int RandomRouletteNumber = 0;

	//a random number engine is created here, this will be used to determine a random roulette number
	random_device engine;
	uniform_int_distribution<int> RandomRowNumber(MinRow, MaxRow);
	uniform_int_distribution<int> RandomColumnNumber(MinColumn, MaxColumn);

	RandomRow = RandomRowNumber(engine);
	RandomColumn = RandomColumnNumber(engine);

	//if the mode's character is 'G', then the values generated by the random engine are used
	//to select a random number from the RouletteValues array (as well as the bool value for the 
	//RouletteFlag usinf the RouletteFlags array)
	if (mode == 'G')
	{
		RandomRouletteNumber = RouletteValues[RandomRow][RandomColumn];
		RoultteFlagColor = RouletteFlags[RandomRow][RandomColumn];

		//the DetermineRouletteStatus function is called, passing the RandomRouletteNumber
		RouletteFlag = DetermineRouletteStatus(RandomRouletteNumber);
	}

	//if the mode's character is 'T', then the user will enter a roulette Number
	else if (mode == 'T')
	{
		cout << "Enter a Roulette Number: ";
		cin >> RandomRouletteNumber;
		cout << endl;

		//the while loop will continue to loop until a valid option is made
		while (RandomRouletteNumber < 0 && RandomRouletteNumber > 36)
		{
			cout << "An invalid Roulette Number was input, try again.\n";
			cout << "Enter a Roulette Number: ";
			cin >> RandomRouletteNumber;
			cout << endl;
		}

		//the for loop is used to move through the columns of the RouletteValues array
		for (int index = 0; index < 3; index++)
		{

			//the for loop is used to move through the rows of the RouletteValues array
			for (int index2 = 0; index2 < 13; index2++)
			{

				//if the RandomRouletteNumber matches the current position of the RouletteValues array
				//the following statements are executed 
				if (RandomRouletteNumber == RouletteValues[index2][index])
				{
					//the position at which the RandomRouletteNumber are saved
					RandomRow = index2;
					RandomColumn = index;

					//the positions are used to determine if the RoultteFlag is true or false 
					RoultteFlagColor = RouletteFlags[index2][index];
				}
			}
		}

		//the DetermineRouletteStatus function is called, passing the RandomRouletteNumber
		RouletteFlag = DetermineRouletteStatus(RandomRouletteNumber);
	}

	//the following if statments are used to call a betting function, this is dependent on the bet made by the user
	if (BettingOpt == 1)
	{
		SingleNumbersBet(RandomRouletteNumber, Money, Ptr);
	}
	else if (BettingOpt == 2)
	{
		AdjacentNumbersBet(RouletteValues, RandomRouletteNumber, Money, Ptr);
	}
	else if (BettingOpt == 3)
	{
		RowsBet(RandomRouletteNumber, Money, RandomRow, Ptr);
	}
	else if (BettingOpt == 4)
	{
		CornerBet(RouletteValues, RandomRouletteNumber, Money, Ptr);
	}
	else if (BettingOpt == 5)
	{
		TwoRowsBet(RandomRouletteNumber, Money, Ptr);
	}
	else if (BettingOpt == 6)
	{
		ColumnsBet(RouletteFlag, RandomRouletteNumber, Money, RandomColumn, Ptr);
	}
	else if (BettingOpt == 7)
	{
		DozenBet(RouletteFlag, RandomRouletteNumber, Money, Ptr);
	}
	else if (BettingOpt == 8)
	{
		ColorBet(RouletteFlag, RoultteFlagColor, RandomRouletteNumber, Money, Ptr);
	}
	else if (BettingOpt == 9)
	{
		EvenOddBet(RouletteFlag, RandomRouletteNumber, Money, Ptr);
	}
	else if (BettingOpt == 10)
	{
		LowHiBet(RouletteFlag, RandomRouletteNumber, Money, Ptr);
	}
}

/*-------------------------------------------------------------------------------------------

PrintTable function is used to print/output a roulette table 

--------------------------------------------------------------------------------------------*/

void PrintTable()
{
	cout << "__________\n";
	cout << "| 0 | 00 |\n";
	cout << "__________\n";
	cout << "| 1| 2| 3|\n";
	cout << "__________\n";
	cout << "| 4| 5| 6|\n";
	cout << "__________\n";
	cout << "| 7| 8| 9|\n";
	cout << "__________\n";
	cout << "|10|11|12|\n";
	cout << "__________\n";
	cout << "|13|14|15|\n";
	cout << "__________\n";
	cout << "|16|17|18|\n";
	cout << "__________\n";
	cout << "|19|20|21|\n";
	cout << "__________\n";
	cout << "|22|23|24|\n";
	cout << "__________\n";
	cout << "|25|26|27|\n";
	cout << "__________\n";
	cout << "|28|29|30|\n";
	cout << "__________\n";
	cout << "|31|32|33|\n";
	cout << "__________\n";
	cout << "|34|35|36|\n";
	cout << "__________\n";
	cout << endl;
}

/*-------------------------------------------------------------------------------------------

SingleNumbersBet function is used to detemrine if the player has made and won/lost a
Single Number bet

-Within the parameter list, two integer variables are passed (rouletteNum, and money)
-Within the parameter list, a pointer with the data type of Player is passed (PlayerP)
--------------------------------------------------------------------------------------------*/

void SingleNumbersBet(int rouletteNum, int money, Player* PlayerP)
{
	const int WinMultiplier = 35;
	int number = 0;

	//the PrintTable function is called to print the roulette table
	PrintTable();

	//the player enters a bet here for SingleNumberBet
	cout << "Enter number to bet on(0, 00, 1 - 36) : ";
	cin >> number;
	cout << endl;

	//if an invalid option was made, the while loop will continue to loop until 
	//a valid option is made
	while (number < 0 && number > 36)
	{
		cout << "An invalid number was input, please try again.\n";
		cout << "Enter number to bet on(0, 00, 1 - 36) : ";
		cin >> number;
		cout << endl;
	}

	//if the player's bet was correct, a winning message will be displayed and the Multiplier function is called
	if (rouletteNum == number)
	{
		Multiplier(WinMultiplier, money, PlayerP);
		cout << "The computer rolled : " << rouletteNum << endl;
		cout << "You win!" << endl << endl;
	}

	//otherwise, if the players bet was incorrect, then the loosing message is displayed
	else
	{
		cout << "The computer rolled : " << rouletteNum << endl;
		cout << "You lose!" << endl << endl;
	}
}

/*-------------------------------------------------------------------------------------------

AdjacentNumbersBet function is used to detemrine if the player has made and won/lost a
adjacent numbers bet

-Within the parameter list, a 2D array of integers is passed with its sizes(rouletteVals is
pass with the sizes ROWS and COLUMNS)
-Within the parameter list, two integer variables are passed (rouletteNum, and money)
-Within the parameter list, a pointer with the data type of Player is passed (PlayerP)
--------------------------------------------------------------------------------------------*/

void AdjacentNumbersBet(int rouletteVals[ROWS][COLUMNS], int rouletteNum, int money, Player *PlayerP)
{
	const int WinMultiplier = 17;
	int counter = 0;

	//a pointer is used to allocate new memory for an array
	//of two integer variables 
	int* Iptr = nullptr;
	Iptr = new int[2];

	bool AdjacentFlag = false;

	//the while loop will continue to loop while the AdjacentFlag is false
	while (AdjacentFlag != true)
	{
		//the PrintTable function is called to print the roulette table
		PrintTable();

		//the for loop is used to move through the Iptr array and to allow
		//the player to enter two number bets for the Adjacent Numbers bet
		for (int index = 0; index < 2; index++)
		{
			cout << "Enter the " << (index + 1) << " number to bet on(0, 00, 1 - 36) : ";
			cin >> Iptr[index];
		}
		cout << endl;
		
		//the for loop is used to move through the rows of the rouletteVals array
		for (int index = 0; index < 12; index++)
		{

			//the for loop is used to move through the columns of the rouletteVals array
			for (int index2 = 0; index2 < 3; index2++)
			{

				//the for loop is used to move through the Iptr array
				for (int index3 = 0; index3 < 2; index3++)
				{

					//if the current value of Iptr[index3] is equal to the current position of the 
					//rouletteVals array, then the counter variable is incremented by (1)
					if (Iptr[index3] == rouletteVals[index][index2])
					{
						counter++;
					}

					//this else if statement follows the same logic as the previous if statement
					else if (Iptr[index3] == rouletteVals[index + 1][index2])
					{
						counter++;
					}
				}

				//the for loop is used to move through the Iptr array
				for (int index3 = 0; index3 < 2; index3++)
				{

					//the for loop is used to move through the Iptr array
					for (int index4 = 0; index4 < 2; index4++)
					{

						//the if statment is used to check if a duplicate value was input for the corner bet
						//if there is a duplicate value then the statement is executed 
						if (Iptr[index3] == Iptr[index4])
						{

							//if the duplciate value found does not match the current position of the Iptr array
							//using the first for loop, then the counter is decremented by (1)
							if (index3 != index4)
							{
								counter--;
							}
						}
					}
				}

				if (counter == 2)
				{
					AdjacentFlag = true;
				}
				counter = 0;
			}
		}

		//the following for loop follows the exact same logic as the for loop above,
		//except checks to see if the AdjacnetNumber bet is a horizontial bet
		//(the previous for loop checked for a veritcal AdjacentNumber bet)
		for (int index = 0; index < 13; index++)
		{
			for (int index2 = 0; index2 < 2; index2++)
			{
				for (int index3 = 0; index3 < 2; index3++)
				{
					if (Iptr[index3] == rouletteVals[index][index2])
					{
						counter++;
					}
					else if (Iptr[index3] == rouletteVals[index][index2 + 1])
					{
						counter++;
					}
				}

				for (int index3 = 0; index3 < 2; index3++)
				{
					for (int index4 = 0; index4 < 2; index4++)
					{
						if (Iptr[index3] == Iptr[index4])
						{
							if (index3 != index4)
							{
								counter--;
							}
						}
					}
				}

				if (counter == 2)
				{
					AdjacentFlag = true;
				}
				counter = 0;
			}
		}
		if (AdjacentFlag == false)
		{
			cout << "The inputs made for your bet were invalid, please try again." << endl << endl;
		}
	}

	//if the player's bet was correct, a winning message will be displayed and the Multiplier function is called
	if (rouletteNum == Iptr[0] || rouletteNum == Iptr[1])
	{
		cout << "The computer rolled : " << rouletteNum << endl;
		cout << "You win!" << endl << endl;
		Multiplier(WinMultiplier, money, PlayerP);
	}

	//otherwise, if the players bet was incorrect, then the loosing message is displayed
	else
	{
		cout << "The computer rolled : " << rouletteNum << endl;
		cout << "You lose!" << endl << endl;
	}

	//the memory used for the array is freed
	delete [] Iptr;
	Iptr = nullptr;
}

/*-------------------------------------------------------------------------------------------

RowsBet function is used to detemrine if the player has made and won/lost a Row bet

-Within the parameter list, three integer variables are passed (rouletteNum, money, and rowNum)
-Within the parameter list, a pointer with the data type of Player is passed (PlayerP)
--------------------------------------------------------------------------------------------*/

void RowsBet(int rouletteNum, int money, int rowNum, Player* PlayerP)
{
	const int WinMultiplier = 11;
	int Row = 0;

	//the player enters a bet here for RowsBet
	cout << "Row 1 = (1, 2, 3)\n";
	cout << "Row 2 = (4, 5, 6)\n";
	cout << "Row 3 = (7, 8, 9)\n";
	cout << "Row 4 = (10, 11, 12)\n";
	cout << "Row 5 = (13, 14, 15)\n";
	cout << "Row 6 = (16, 17, 18)\n";
	cout << "Row 7 = (19, 20, 21)\n";
	cout << "Row 8 = (22, 23, 24)\n";
	cout << "Row 9 = (25, 26, 27)\n";
	cout << "Row 10 = (28, 29, 30)\n";
	cout << "Row 11 = (31, 32, 33)\n";
	cout << "Row 12 = (34, 35, 36)\n";
	cout << endl;

	cout << "Enter Row to bet on : ";
	cin >> Row;

	//if an invalid option was made, the while loop will continue to loop until 
	//a valid option is made
	while (Row < 0 || Row > 12)
	{
		cout << "Row 1 = (1, 2, 3)\n";
		cout << "Row 2 = (4, 5, 6)\n";
		cout << "Row 3 = (7, 8, 9)\n";
		cout << "Row 4 = (10, 11, 12)\n";
		cout << "Row 5 = (13, 14, 15)\n";
		cout << "Row 6 = (16, 17, 18)\n";
		cout << "Row 7 = (19, 20, 21)\n";
		cout << "Row 8 = (22, 23, 24)\n";
		cout << "Row 9 = (25, 26, 27)\n";
		cout << "Row 10 = (28, 29, 30)\n";
		cout << "Row 11 = (31, 32, 33)\n";
		cout << "Row 12 = (34, 35, 36)\n";
		cout << endl;

		cout << "Enter Row to bet on : ";
		cin >> Row;
		cout << endl;
	}
	cout << endl;

	//if the player's bet was correct, a winning message will be displayed and the Multiplier function is called
	if (rowNum == Row)
	{
		cout << "The computer rolled : " << rouletteNum << " row " << Row << endl;
		cout << "You win!" << endl << endl;
		Multiplier(WinMultiplier, money, PlayerP);
	}

	//otherwise, if the players bet was incorrect, then the loosing message is displayed
	else
	{
		cout << "The computer rolled : " << rouletteNum << " row " << rowNum << endl;
		cout << "You lose!" << endl << endl;
	}


}

/*-------------------------------------------------------------------------------------------

CornerBet function is used to detemrine if the player has made and won/lost a Corner bet

-Within the parameter list, a 2D array of integers is passed with its sizes(rouletteVals is
pass with the sizes ROWS and COLUMNS)
-Within the parameter list, two integer variables are passed (rouletteNum, and money)
-Within the parameter list, a pointer with the data type of Player is passed (PlayerP)
--------------------------------------------------------------------------------------------*/

void CornerBet(int rouletteVals[ROWS][COLUMNS], int rouletteNum, int money, Player *PlayerP)
{
	const int WinMultiplier = 8;
	const int size = 4;
	int cornerNum = 0;
	bool cornerFlag = false;

	//a pointer is used to allocate new memory for an array
	//of four integer variables 
	int* Iptr = nullptr;
	Iptr = new int[size];

	int CornerBet = 0;

		//the while loop will continue to loop while the cornerFlag is false
		while (cornerFlag != true)
		{

			//the PrintTable function is called to print the roulette table
			PrintTable();

			//the for loop is used to move through the Iptr array and to allow
			//the player to enter four number bets for the corner bet
			for (int index = 0; index < size; index++)
			{
				cout << "Enter the number for square " << (index + 1) << " to bet on(0, 00, 1 - 36) : ";
				cin >> CornerBet;
				Iptr[index] = CornerBet;
			}

			//the for loop is used to move through the rows of the rouletteVals array
			for (int index = 0; index < 12; index++)
			{

				//the for loop is used to move through the columns of the rouletteVals array
				for (int index2 = 0; index2 < 2; index2++)
				{

					//the for loop is used to move through the Iptr array
					for (int index3 = 0; index3 < 4; index3++)
					{

						//if the current value of Iptr[index3] is equal to the current position of the 
						//rouletteVals array, then the cornerNum variable is incremented by (1)
						//(this check for the top left corner of a corner bet)
						if (Iptr[index3] == rouletteVals[index][index2])
						{
							cornerNum++;
						}

						//this else if statement follows the same logic as the previous if statement
						//(this check for the top right corner of a corner bet)
						else if (Iptr[index3] == rouletteVals[index + 1][index2])
						{
							cornerNum++;
						}

						//this else if statement follows the same logic as the previous if statement
						//(this check for the bottom left corner of a corner bet)
						else if (Iptr[index3] == rouletteVals[index][index2 + 1])
						{
							cornerNum++;
						}

						//this else if statement follows the same logic as the previous if statement
						//(this check for the bottom right corner of a corner bet)
						else if (Iptr[index3] == rouletteVals[index + 1][index2 + 1])
						{
							cornerNum++;
						}
					}
					
					//the for loop is used to move through the Iptr array
					for (int index3 = 0; index3 < 4; index3++)
					{

						//the for loop is used to move through the Iptr array
						for (int index4 = 0; index4 < 4; index4++)
						{

							//the if statment is used to check if a duplicate value was input for the corner bet
							//if there is a duplicate value then the statement is executed 
							if (Iptr[index3] == Iptr[index4])
							{

								//if the duplciate value found does not match the current position of the Iptr array
								//using the first for loop, then the cornerNum is decremented by (1)
								if (index3 != index4)
								{
									cornerNum--;
								}
							}
						}
					}

					//if cornerNum is equal to 4, then cornerFlag is set to true 
					if (cornerNum == 4)
					{
						cornerFlag = true;
					}

					//cornerNum is set to 0
					cornerNum = 0;
				}
			}

			//if cornerFlag is equal to false, then the error message is displayed, indicating that invalid input were made 
			if (cornerFlag == false)
			{
				cout << "The inputs made for your bet were invalid, please try again." << endl << endl;
			}
		}
		cout << endl;

	//if the player's bet was correct, a winning message will be displayed and the Multiplier function is called
	if (rouletteNum == Iptr[0] ||
		rouletteNum == Iptr[1] ||
		rouletteNum == Iptr[2] ||
		rouletteNum == Iptr[3])
	{
		cout << "The computer rolled : " << rouletteNum << endl;
		cout << "You win!" << endl << endl;
		Multiplier(WinMultiplier, money, PlayerP);
	}

	//otherwise, if the players bet was incorrect, then the loosing message is displayed
	else
	{
		cout << "The computer rolled : " << rouletteNum << endl;
		cout << "You lose!" << endl << endl;
	}

	//the memory used for the array is freed
	delete[] Iptr;
	Iptr = nullptr;
}

/*-------------------------------------------------------------------------------------------

TwoRowsBet function is used to detemrine if the player has made and won/lost a Two Row bet

-Within the parameter list, two integer variables are passed (rouletteNum, and money)
-Within the parameter list, a pointer with the data type of Player is passed (PlayerP)
--------------------------------------------------------------------------------------------*/

void TwoRowsBet(int rouletteNum, int money, Player *PlayerP)
{
	const int WinMultiplier = 5;
	int DoubleRow = 0;
	int min = 0;
	int max = 0;
	int roulNum = 0;

	//the player enters a bet here for TwoRowsBet
	cout << "Double Row 1 = (1, 2, 3, 4, 5, 6)\n";
	cout << "Double Row 2 = (4, 5, 6, 7, 8, 9)\n";
	cout << "Double Row 3 = (7, 8, 9, 10, 11, 12)\n";
	cout << "Double Row 4 = (10, 11, 12, 13, 14, 15)\n";
	cout << "Double Row 5 = (13, 14, 15, 16, 17, 18)\n";
	cout << "Double Row 6 = (16, 17, 18, 19, 20, 21)\n";
	cout << "Double Row 7 = (19, 20, 21, 22, 23, 24)\n";
	cout << "Double Row 8 = (22, 23, 24, 25, 26, 27)\n";
	cout << "Double Row 9 = (25, 26, 27, 28, 29, 30)\n";
	cout << "Double Row 10 = (28, 29, 30, 31, 32, 33)\n";
	cout << "Double Row 11 = (31, 32, 33, 34, 35, 36)\n";
	cout << endl;

	cout << "Enter Double row to bet on : ";
	cin >> DoubleRow;

	//if an invalid option was made, the while loop will continue to loop until 
	//a valid option is made
	while (DoubleRow < 0 || DoubleRow > 11)
	{
		cout << "An invalid option was made, please try again." << endl;
		cout << "Double Row 1 = (1, 2, 3, 4, 5, 6)\n";
		cout << "Double Row 2 = (4, 5, 6, 7, 8, 9)\n";
		cout << "Double Row 3 = (7, 8, 9, 10, 11, 12)\n";
		cout << "Double Row 4 = (10, 11, 12, 13, 14, 15)\n";
		cout << "Double Row 5 = (13, 14, 15, 16, 17, 18)\n";
		cout << "Double Row 6 = (16, 17, 18, 19, 20, 21)\n";
		cout << "Double Row 7 = (19, 20, 21, 22, 23, 24)\n";
		cout << "Double Row 8 = (22, 23, 24, 25, 26, 27)\n";
		cout << "Double Row 9 = (25, 26, 27, 28, 29, 30)\n";
		cout << "Double Row 10 = (28, 29, 30, 31, 32, 33)\n";
		cout << "Double Row 11 = (31, 32, 33, 34, 35, 36)\n";
		cout << endl;

		cout << "Enter Double row to bet on : ";
		cin >> DoubleRow;
		cout << endl;
	}
	cout << endl;

	//the for loop is used to check if the rouletteNum is between a certain range 
	for (int i = 0; i < 12; i++)
	{
		//the following math equation is used to calculate the ranges for each Two Row bet
		min = ((i * 3) - 3);
		max = ((i * 3) + 4);

		//if the rouletteNum is between the min and max range of the equation then 
		//the roulNum is set to i (indicates the type of Two Row the rouletteNum was found in)
		if (rouletteNum > min && rouletteNum < max)
		{
			roulNum = i;
		}
	}

	//the following math equation is used to calculate the ranges for each Two Row bet (using DoubleRow
	//which is the bet made by the player)
	min = ((DoubleRow * 3) - 3);
	max = ((DoubleRow * 3) + 4);

	//if the rouletteNum is between the min and max range of the equation then 
	//the roulNum is set to DoubleRow (indicates the type of Two Row the rouletteNum was found in)
	if (rouletteNum > min && rouletteNum < max)
	{
		roulNum = DoubleRow;
	}

	//if the player's bet was correct, a winning message will be displayed and the Multiplier function is called
	if (roulNum == DoubleRow)
	{
		cout << "The computer rolled : " << rouletteNum << " Double Row " << roulNum << endl;
		cout << "You win!" << endl << endl;
		Multiplier(WinMultiplier, money, PlayerP);
	}

	//otherwise, if the players bet was incorrect, then the loosing message is displayed
	else
	{
		cout << "The computer rolled : " << rouletteNum << " Double Row " << roulNum << endl;
		cout << "You lose!" << endl << endl;
	}

}

/*-------------------------------------------------------------------------------------------

ColumnsBet function is used to detemrine if the player has made and won/lost a Column bet

-Within the parameter list, a bool is passed (rouletteStatusFlag)
-Within the parameter list, three integer variables are passed (rouletteNum, money, and columnNum)
-Within the parameter list, a pointer with the data type of Player is passed (PlayerP)
--------------------------------------------------------------------------------------------*/

void ColumnsBet(bool rouletteStatusFlag, int rouletteNum, int money, int columnNum, Player* PlayerP)
{
	const int WinMultiplier = 2;
	int column = 0;

	//the columnNum is incremented by 1 to adjust for the column bet being made by the player
	columnNum++;

	//the player enters a bet here for ColumnsBet
	cout << "Column 1 = (1, 4, 7, 10, 13, 16, 19, 22, 25, 28, 31, 34)\n";
	cout << "Column 2 = (2, 5, 8, 11, 14, 17, 20, 23, 26, 29, 32, 35)\n";
	cout << "Column 3 = (3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36)\n";
	cout << endl;
	cout << "Enter Column to bet on : ";
	cin >> column;

	//if an invalid option was made, the while loop will continue to loop until 
	//a valid option is made
	while (column < 0 || column > 3)
	{
		cout << "An invalid input was made, please try again.\n";
		cout << "Column 1 = (1, 4, 7, 10, 13, 16, 19, 22, 25, 28, 31, 34)\n";
		cout << "Column 2 = (2, 5, 8, 11, 14, 17, 20, 23, 26, 29, 32, 35)\n";
		cout << "Column 3 = (3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36)\n";
		cout << endl;
		cout << "Enter Column to bet on : ";
		cin >> column;
		cout << endl;
	}
	cout << endl;

	//if the rouletteStatusFlag is ture, then the player will automatically loose their bet and the loosing message is displayed
	if (rouletteStatusFlag == 1)
	{
		cout << "The computer rolled : " << rouletteNum << endl;
		cout << "You lose!" << endl << endl;
	}

	//else if the player's bet was correct, a winning message will be displayed and the Multiplier function is called
	else if (columnNum == column)
	{
		cout << "The computer rolled : " << rouletteNum << " column " << column << endl;
		cout << "You win!" << endl << endl;
		Multiplier(WinMultiplier, money, PlayerP);
	}

	//otherwise, if the players bet was incorrect, then the loosing message is displayed
	else
	{
		cout << "The computer rolled : " << rouletteNum << " column " << columnNum << endl;
		cout << "You lose!" << endl << endl;
	}

}

/*-------------------------------------------------------------------------------------------

DozenBet function is used to detemrine if the player has made and won/lost a Dozen bet

-Within the parameter list, a bool is passed (rouletteStatusFlag)
-Within the parameter list, two integer variables are passed (rouletteNum and money)
-Within the parameter list, a pointer with the data type of Player is passed (PlayerP)
--------------------------------------------------------------------------------------------*/

void DozenBet(bool rouletteStatusFlag, int rouletteNum, int money, Player *PlayerP)
{
	const int WinMultiplier = 2;
	int dozen = 0;
	int rouletteDozen = 0;

	//the following if statments are used to check if the rouletteNumber is between a certain range for a dozen bet
	//if the rouletteNum is between 0-12, then rouletteDozen is set to 1
	if (rouletteNum > 0 && rouletteNum < 13)
	{
		rouletteDozen = 1;
	}

	//else if the rouletteNum is between 13-24, then rouletteDozen is set to 2
	else if (rouletteNum > 12 && rouletteNum < 25)
	{
		rouletteDozen = 2;
	}

	//else if the rouletteNum is greater than 24, then rouletteDozen is set to 3
	else if (rouletteNum > 24)
	{
		rouletteDozen = 3;
	}

	//the player enters a bet here for DozenBet
	cout << "Group 1 = 1 - 12\n";
	cout << "Group 2 = 13 - 24\n";
	cout << "Group 3 = 25 - 36\n";
	cout << endl;
	cout << "Enter Dozen to bet on : ";
	cin >> dozen;

	//if an invalid option was made, the while loop will continue to loop until 
	//a valid option is made
	while (dozen < 0 || dozen > 3)
	{
		cout << "An invalid option was made, please try again." << endl;
		cout << "Group 1 = 1 - 12\n";
		cout << "Group 2 = 13 - 24\n";
		cout << "Group 3 = 25 - 36\n";
		cout << endl;
		cout << "Enter Dozen to bet on : ";
		cin >> dozen;
		cout << endl;
	}
	cout << endl;

	//if the rouletteStatusFlag is ture, then the player will automatically loose their bet and the loosing message is displayed
	if (rouletteStatusFlag == 1)
	{
		cout << "The computer rolled : " << rouletteNum << endl;
		cout << "You lose!" << endl << endl;
	}

	//else if the player's bet was correct, a winning message will be displayed and the Multiplier function is called
	else if (rouletteDozen == dozen)
	{
		cout << "The computer rolled : " << rouletteNum << " Group " << dozen << endl;
		cout << "You win!" << endl << endl;
		Multiplier(WinMultiplier, money, PlayerP);
	}

	//otherwise, if the players bet was incorrect, then the loosing message is displayed
	else
	{
		cout << "The computer rolled : " << rouletteNum << " Group " << rouletteDozen << endl;
		cout << "You lose!" << endl << endl;
	}
}

/*-------------------------------------------------------------------------------------------

ColorBet function is used to detemrine if the player has made and won/lost a Color bet

-Within the parameter list, two bools are passed (rouletteStatusFlag and colorFlag)
-Within the parameter list, two integer variables are passed (rouletteNum and money)
-Within the parameter list, a pointer with the data type of Player is passed (PlayerP)
--------------------------------------------------------------------------------------------*/

void ColorBet(bool rouletteStatusFlag, bool colorflag, int rouletteNum, int money, Player* PlayerP)
{
	const int WinMultiplier = 1;
	int ColorBet = 0;
	bool PlayerFlag = false;
	string betType = " ";


	//the player enters a bet here for ColorBet
	cout << "Red = 1\n";
	cout << "Black = 0\n";
	cout << endl;
	cout << "Enter the color to bet on: ";
	cin >> ColorBet;

	//if an invalid option was made, the while loop will continue to loop until 
	//a valid option is made
	while (ColorBet < 0 || ColorBet > 1)
	{
		cout << "An invalid option was made, please try again.\n";
		cout << "Red = 1\n";
		cout << "Black = 0\n";
		cout << " " << endl;
		cout << "Enter Even/Odd to bet on : ";
		cin >> ColorBet;
	}
	cout << endl;
	PlayerFlag = ColorBet;

	//this is used to determine if the random number's color is red or black, it the colorFlag is true then the 
	//random number's color is red, otherwise the random number's color is black 
	if (colorflag == 1)
	{
		betType = "Red";
	}
	else if (colorflag == 0)
	{
		betType = "Black";
	}

	//if the rouletteStatusFlag is ture, then the player will automatically loose their bet and the loosing message is displayed
	if (rouletteStatusFlag == 1)
	{
		cout << "The computer rolled : " << rouletteNum << endl;
		cout << "You lose!" << endl << endl;
	}

	//else if the player's bet was correct, a winning message will be displayed and the Multiplier function is called
	else if (colorflag == PlayerFlag)
	{
		cout << "The computer rolled : " << rouletteNum << " " << betType << endl;
		cout << "You win!" << endl << endl;
		Multiplier(WinMultiplier, money, PlayerP);
	}

	//otherwise, if the players bet was incorrect, then the loosing message is displayed
	else
	{
		cout << "The computer rolled : " << rouletteNum << " " << betType << endl;
		cout << "You lose!" << endl << endl;
	}
}

/*-------------------------------------------------------------------------------------------

Even/OddBet function is used to detemrine if the player has made and won/lost an Even/Odd bet

-Within the parameter list, a bool is passed (rouletteStatusFlag)
-Within the parameter list, two integer variables are passed (rouletteNum and money)
-Within the parameter list, a pointer with the data type of Player is passed (PlayerP)
--------------------------------------------------------------------------------------------*/

void EvenOddBet(bool rouletteStatusFlag, int rouletteNum, int money, Player* PlayerP)
{
	const int WinMultiplier = 1;
	int evenOdd = 0;
	double fraction = 0.0;

	bool roulFlag = false;
	bool PlayerFlag = false;
	string betType = " ";

	//the player enters a bet here for Even/Odd
	cout << "Even = 1\n";
	cout << "Odd = 0\n";
	cout << endl;
	cout << "Enter Even/Odd to bet on : ";
	cin >> evenOdd;

	//if an invalid option was made, the while loop will continue to loop until 
	//a valid option is made
	while (evenOdd < 0 || evenOdd > 1)
	{
		cout << "An invalid option was made, please try again.\n";
		cout << "Even = 1\n";
		cout << "Odd = 0\n";
		cout << endl;
		cout << "Enter Even/Odd to bet on : ";
		cin >> evenOdd;
	}
	cout << endl;
	PlayerFlag = evenOdd;

	//the following equation is used to determine break down the random number into a smaller even or odd number
	//if it is an even number, the remaining number will be a 0
	//otherwise the remaining number will be 0.5
	fraction = static_cast<double>(rouletteNum) / 2;
	fraction = fraction - static_cast<int>(fraction);

	//if the fraction generated from the previous equation is 0.5, then the random number generated 
	//is an odd number and the roulFlag is set to false
	if (fraction == 0.5)
	{
		roulFlag = 0;
		betType = "Odd";
	}

	//otherwise, the random number generated is even and roulFlag is set to true
	else
	{
		roulFlag = 1;
		betType = "Even";
	}

	//if the rouletteStatusFlag is ture, then the player will automatically loose their bet and the loosing message is displayed
	if (rouletteStatusFlag == 1)
	{
		cout << "The computer rolled : " << rouletteNum << endl;
		cout << "You lose!" << endl << endl;
	}

	//else if the player's bet was correct, a winning message will be displayed and the Multiplier function is called
	else if (roulFlag == PlayerFlag)
	{
		cout << "The computer rolled : " << rouletteNum << " " << betType << endl;
		cout << "You win!" << endl << endl;
		Multiplier(WinMultiplier, money, PlayerP);
	}

	//otherwise, if the players bet was incorrect, then the loosing message is displayed
	else
	{
		cout << "The computer rolled : " << rouletteNum << " " << betType << endl;
		cout << "You lose!" << endl << endl;
	}
}

/*-------------------------------------------------------------------------------------------

LowHiBet is used to detemrine if the player has made and won/lost a LowHigh bet

-Within the parameter list, a bool is passed (rouletteStatusFlag)
-Within the parameter list, two integer variables are passed (rouletteNum and money)
-Within the parameter list, a pointer with the data type of Player is passed (PlayerP)
--------------------------------------------------------------------------------------------*/

void LowHiBet(bool rouletteStatusFlag, int rouletteNum, int money, Player* PlayerP)
{
	const int WinMultiplier = 1;
	int HighLow = 0;

	bool PlayerFlag = 0;
	bool roulFlag = 0;
	string betType = " ";

	//the user enters a bet here for LowHi bet
	cout << "Low 1-18 = 1\n";
	cout << "High 19-36 = 0\n";
	cout << endl;
	cout << "Enter High/Low to bet on: ";
	cin >> HighLow;

	//if an invalid option was made, the while loop will continue to loop until 
	//a valid option is made
	while (HighLow < 0 || HighLow > 1)
	{
		cout << "An invalid option was made, please try again.\n";
		cout << "Low 1-18 = 1\n";
		cout << "High 19-36 = 0\n";
		cout << endl;
		cout << "Enter High/Low to bet on : ";
		cin >> HighLow;
	}

	PlayerFlag = HighLow;
	cout << endl;

	//if the rouletteNum is greater than 19, then the 
	//LowHi bet is a Low Value, otherwise it is a High Value
	if (rouletteNum < 19)
	{
		roulFlag = 1;
		betType = "Low";
	}
	else if (rouletteNum > 18)
	{
		roulFlag = 0;
		betType = "High";
	}

	//if the rouletteStatusFlag is ture, then the player will automatically loose their bet and the loosing message is displayed
	if (rouletteStatusFlag == 1)
	{
		cout << "The computer rolled : " << rouletteNum << endl;
		cout << "You lose!" << endl << endl;
	}

	//else if the player's bet was correct, a winning message will be displayed and the Multiplier function is called
	else if (roulFlag == PlayerFlag)
	{
		cout << "The computer rolled : " << rouletteNum << " " << betType << endl;
		cout << "You win!" << endl << endl;
		Multiplier(WinMultiplier, money, PlayerP);
	}

	//otherwise, if the players bet was incorrect, then the loosing message is displayed
	else
	{
		cout << "The computer rolled : " << rouletteNum << " " << betType << endl;
		cout << "You lose!" << endl << endl;
	}
}

/*-------------------------------------------------------------------------------------------

DetermineRoulettestatus function is used to determine if an outside bet is invalid and returns 
a true/false

-Within the parameter list, an integer variable is passed (RouletteNum)
--------------------------------------------------------------------------------------------*/

bool DetermineRouletteStatus(int RouletteNum)
{
	//if the RouletteNum value is 0 or 00 then true is returned
	//otherwise false is returned
	if (RouletteNum = 0 || RouletteNum == 00)
	{
		return true; //cancel outside bets
	}
	else
	{
		return false; //keep the outside bets
	}
}

/*-------------------------------------------------------------------------------------------

Multiplier function is used to caculate the winnings if a winning bet is made 

-Within the parameter list, two integer variables are passed (Multi, and bets)
-Within the parameter list, a pointer witht the data type of Player is passed (p)

--------------------------------------------------------------------------------------------*/

void Multiplier(int Multi, int bets, Player* p)
{
	//the original value of the bet is multiplied by the winning multiplier, and the inital bet is then 
	//added onto the total. Afterwards, the amount if transfered into the players earnings using the Player
	//member function BetEarningsAdd().
	bets += (Multi * bets);
	p->BetEarningsAdd(bets);
}