//Name: Jose Villanueva Vigil
//Course: COSC 2436
//Program set 1, problem 1 (ExpEvaluation)
//References: I used the PDF covering program set 1
//=================================================================================

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//these are the function that will be utilized throughout the program
//their descriptions can be found towards the bottom of the program
void TransferContents(string, char[]);
void NumericData(int, int[], char[], char[]);
void TotalData(int, char[], int[], int&);
void DisplayData(int, char[], int[], int);

//the SIZE and SIZE2 constant integer variable are used to set the sizes of the
//input, numInput, and values array
const int SIZE = 80;
const int SIZE2 = 27;

//the input and numInput arrays are initialized to their default values
char input[SIZE] = {};
int numInput[SIZE] = {};

//the values array is intialized using a pre-set series of characters
char values[SIZE2] = {
	'X','a','b','c','d','e','f',
	'g','h','i','j','k','l','m',
	'n','o','p','q','r','s','t',
	'u','v','w','x','y','z' };

int main()
{
	//the value integer variable is used to hold the total value of each expression
	int value = 0;
	int point = 1;

	//the string data variable is used to get the user input/expression
	string data;

	//the check character variable is used to store a character value 
	char check = 'y';

	cout << "===================================================================================" << endl;
	cout << "IMPORTANT NOTICE" << endl << endl;
	cout << "-If an expression of more than 80 characters is entered, then an error message will" << endl;
	cout << "be displayed(and loop) until the expression is less than or equal to 80 characters." << endl;
	cout << "-If an incorrect input is made(to run the program), then an error message will be" << endl;
	cout << " displayed(and loop) until a correct input is made." << endl;
	cout << "===================================================================================" << endl << endl;

	//the if statment checks for a valid input using the check vriable 
	if (check != 'y' && check != 'n' || check == 'y')
	{

		//the while loop will continue to run while the check variable is not 'n'
		while (check != 'n')
		{

			//the if statement check to see if the check variable is 'y'
			//if so, then the data regarding the expression will be proccessed here
			if (check == 'y')
			{
				cout << "Enter expression: ";
				getline(cin, data);

				//if the length of the expression excceds 80 characters, then an error message is displayed
				//the error will continue to loop until the expression is less than or equal to 80
				if (data.length() > 80)
				{
					while (data.length() > 80)
					{
						cout << "The line of texted entered is too long, please try again." << endl;
						cout << "Enter expression: ";
						getline(cin, data);
					}
				}

				//the data is proccessed using the functions mentioned earlier 
				TransferContents(data, input);
				NumericData(static_cast<int>(data.length()), numInput, input, values);
				TotalData(static_cast<int>(data.length()), input, numInput, value);

				cout << endl;
				cout << "Expression " << point << ": " << data << endl << endl;

				DisplayData(static_cast<int>(data.length()), input, numInput, value);

				cout << "Run again (Y/N): ";
				cin >> check;
				cout << endl;
				check = tolower(check);
				cin.ignore(1, '\n');

				value = 0;
				point++;
			}

			//the else statement checks for any invalid input that may have been entered, this error will continue
			//to loop until a correct input is entered.
			else
			{
				while (check != 'y' && check != 'n')
				{
					cout << "An invalid input was made, please try again\n";
					cout << "If you would like to run the program, enter (Y), else, enter (N): ";
					cin >> check;
					check = tolower(check);
				}
			}
		}
	}
	return 0;
}


/*-------------------------------------------------------------------------------------------

NumericData function is used to assign the numeric data, of each variable, into a seperate array
that will contain the numeric data of each variable that will be used later in the program

-Within the parameter list, an integer value is passed(len)
-Within the parameter list, an array of integers is passed(UserValues)
-Within the parameter list, two arrays of characters are passed(UserInput and Values)

--------------------------------------------------------------------------------------------*/

void NumericData(int len, int UserValues[], char UserInput[], char Values[])
{
	int counter = 0;

	//the 1st for loop is used to move through the UserInput array 
	for (int index = 0; index < len; index++)
	{

		//the 2nd(nested) for loop is used to move through thr Values array
		for (int index2 = 0; index2 < 27; index2++)
		{

			//the if statement is used to check if the current position of the UserInput array is 
			//an alphabetical character, it will also check if the alphabetical character found
			//matches an alphabetical character that if found within the Values array 
			if (isalpha(UserInput[index]) && UserInput[index] == Values[index2])
			{

				//of the statement is true, then the value stored in the UserValues array
				//if the current position of the Values array, and the counter variable is incremented by one
				UserValues[counter] = index2;
				counter++;
			}
		}
	}
}

/*-------------------------------------------------------------------------------------------

TransferContents function is used to transfer the string contents of a string into a character array

-Within the parameter list, a string variable is passed(s)
-Within the parameter list, an array of characters is passed(S) 

--------------------------------------------------------------------------------------------*/

void TransferContents(string s, char S[])
{
	//the length variable is initalized with the length of the s string
	//using the length() function and the static_cast feature
	int length = static_cast<int>(s.length());
	int i2 = 0;
	bool WhiteSpace = true;

	//the for loop is used to move through the s string
	//and the S character array
	for (int i = 0; i < length; i++)
	{
		WhiteSpace = true;

		//the if statement check to see if the current position in the s string is a space
		if (isspace(s[i]))
		{
			//if the current position is a space, i2 is incremented by (1) and the 
			//space bool is changed to false.  
			i2++;
			WhiteSpace = false;
		}

		//the if statement is used to check if the current positon of the s string is a space
		//if it is not, the following code will be executed.
		if (WhiteSpace == true)
		{
			//if the i2 variable this statement is executed (no spaces in the string)
			if (i2 == 0)
			{
				S[i] = tolower(s[i]);
			}
			//if the previous statement is false, this statement will be executed instead (indicates that there is a space within the string)
			else
			{
				S[i - i2] = tolower(s[i]);
			}
		}
	}
}

/*-------------------------------------------------------------------------------------------

TotalData function is used to evaluate the (++/--) and the (+/-) operators within a given expression,
as well as total the values to give the overall total value of a given expression

-Within the parameter list, an integer value is passed(len)
-Within the parameter list, an integer value is being passed by reference(val)
-Within the parameter list, an array of characters is passed(InputData)
-Within the parameter list, an array of integers is passed(ValueData)

--------------------------------------------------------------------------------------------*/

void TotalData(int len, char InputData[], int ValueData[], int& val)
{
	int counter = 0;
	char sign = ' ';

	//this for loop is used to scan the InputData array for any varaiables 
	//that contain a (++/--) before them, once they are found, the 
	//varaibles are incremeted based on the operators before them
	for (int i = 0; i < len; i++)
	{

		//the is statement is used to look for 
		//any alphabetical characters within the 
		//InputData array
		if (isalpha(InputData[i]))
		{
			
			//a nested if statement is used to check 
			//if the (++/--) operators are before
			//the variable, and then checks to see
			//if the operators are matching
			if (InputData[i + 1] == InputData[i + 2])
			{

				//this nested if statment checks to see which 
				//operator was detected and increments the 
				//variable by that value.
				//Afterwards, the counter value is incremeted 
				//and the operators that were found are removed
				//from the InputData array
				if (InputData[i + 1] == '+')
				{
					ValueData[counter]++;
				}
				else if (InputData[i + 1] == '-')
				{
					ValueData[counter]--;
				}
				InputData[i + 1] = ' ';
				InputData[i + 2] = ' ';
				counter++;
			}

			//if the (++/--) do not match, then the counter
			//variable is incremented 
			else
			{
				counter++;
			}
		}
	}

	//the counter variable is re-adjusted to
	//the size of the ValueData array
	counter = counter - 1;

	//the following for loop repeats the exact same process
	//as the for loop above, except this for loop is used to check
	//for any (++/--) that are ahead of a(ny) variable 
	for (int i = len; i > 0; i--)
	{
		if (isalpha(InputData[i]))
		{
			if (InputData[i - 1] == InputData[i - 2])
			{
				if (InputData[i - 1] == '+')
				{
					ValueData[counter]++;
				}
				else if (InputData[i - 1] == '-')
				{
					ValueData[counter]--;
				}
				InputData[i - 1] = ' ';
				InputData[i - 2] = ' ';
				counter--;
			}
			else
			{
				counter--;
			}
		}
	}

	//the counter variable is set to 0
	counter = 0;

	//the following for loop is used to move through 
	//the remaining contents of the InputData, and (+/-)
	//the remaining variables within the array
	for (int i = 0; i < len; i++)
	{

		//the if statement checks for the first alphabetical
		//character within the InputData and add's it to the 
		//total value in the val variable, the counter is then
		//incremented by one
		if (sign == ' ' && isalpha(InputData[i]))
		{
				val += ValueData[counter];
				counter++;
		}

		//the following if/else if statement is use to
		//search for a (+/-) character, once the character has been 
		//found, the sign variable is set to the charater that was found
		if (InputData[i] == '+')
		{
			sign = '+';
		}
		else if (InputData[i] == '-')
		{
			sign = '-';
		}

		//the if statement is used to check for the (+/-) character 
		//that was stored within the sign variable, and will also check for an
		//alphabetical character within the InputData array. Once both values are found
		//the variable is then added or subtracted to the val variable, and the counter 
		//variable is incremeneted
		if (sign == '+' && isalpha(InputData[i]))
		{
			sign = ' ';
			val += ValueData[counter];
			counter++;
		}
		else if (sign == '-' && isalpha(InputData[i]))
		{
			sign = ' ';
			val -= ValueData[counter];
			counter++;
		}
	}
}


/*-------------------------------------------------------------------------------------------

DisplayData function is used to display the results/answers of a given epxression,as well as the
variables within the expression. After the results have been displayed, the contents of the 
arrays used are cleared.

-Within the parameter list, two integer values are passed(len and val)
-Within the parameter list, an array of characters is passed(InputData)
-Within the parameter list, an array it integers is passed(Values)

--------------------------------------------------------------------------------------------*/


void DisplayData(int len, char InputData[], int Values[], int val)
{
	int counter = 0;

	cout << "Value = " << val << endl;

	//a for loop is used to move through the contents of the InputData array
	//an if statment is used witin the for loop to search for alphabetical 
	//characters/values within the array
	for (int i = 0; i < len; i++)
	{

		//once an alphabetical character is found, the message corresponding with the value
		//of the alphabetical character is displayed, and the counter variable is incremented 
		//by one
		if (isalpha(InputData[i]))
		{
			cout << InputData[i] << " = " << Values[counter] << endl;
			counter++;
		}
	}
	cout << endl;

	//a for loop is used to clear the contents of both arrays
	for (int i = 0; i < len; i++)
	{
		InputData[i] = ' ';
		Values[i] = 0;
	}
}