//Name: Jose Villanueva Vigil
//Course: COSC 2436
//Program set 1, problem 2 (BlobLocate)
//References: I used the PDF covering program set 1
//=================================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

//these are the function that will be utilized throughout the program
//their descriptions can be found towards the bottom of the program
void BlobCopy(char* [], char* [], int, int);
void BlobSizeChecker(char*[], int, int, int, int, int&);

int main()
{

	//two types of pointer arrays are defined here
	//two character arrays that will be used to collect the blob grid data
	//one integer array that will be used to hold the locations to be searched in the blob grid
	char** BlobArray = nullptr;
	char** CopyBlobArray = nullptr;
	int** LocationArray = nullptr;

	char CaseChecker = 'Y';

	string FileName;
	ifstream InputFile;


	//this while loop will continue to run while the CaseChekcer is not 'N'
	while (CaseChecker != 'N')
	{
		cout << "Enter file name: ";
		cin >> FileName;
		cout << " " << endl;


		//Opens file required for program to run
		InputFile.open(FileName);

		//if there is no file then an error is displayed
		if (InputFile.fail())
		{
			cout << "An error has Occured while opening the file\n";
		}
		else
		{

			//these are the variables that will be used to hold the data within the file
			int NumOfCases = 0;
			int RowSize = 0;
			int ColumnSize = 0;
			int GridTestCases = 0;
			int counter = 1;
			int RowNum = 0;
			int ColumnNum = 0;

			//this integer will be used to keep track of the blob size 
			int BlobSize = 0;
			
			//the number of cases that are within the file is collected here
			InputFile >> NumOfCases;

			for (int i = 0; i < NumOfCases; i++)
			{

				//the information needed for the blob grid sizes are collected here
				//the amount of locations that are to be searched within the grid are collected here
				InputFile >> RowSize;
				InputFile >> ColumnSize;
				InputFile >> GridTestCases;

				//BlobArray and CopyBlobArray allocate memory to create a new 
				//array of character pointer variables using the RowSize variable 
				BlobArray = new char* [RowSize];
				CopyBlobArray = new char* [RowSize];
				LocationArray = new int* [GridTestCases];
				//the LocationArray allocates memory to create a new 
				//array of integer pointer variables using the GridTestCases variable

				//the for loop is used to move through the array's created using
				//BlobArray and CopyBlobArray, to assign each array the characters 
				//stored within the file (getting data for the blob grid)
				for (int index = 0; index < RowSize; index++)
				{

					//each character pointer within the character pointer array allocates memory for a new
					//array of characters that will be used to store the blob grid information 
					BlobArray[index] = new char[ColumnSize];
					CopyBlobArray[index] = new char[ColumnSize];
					for (int index2 = 0; index2 < ColumnSize; index2++)
					{
						//the blob grid information is first passed to BlobArray
						//and then CopyBlobArray gets a copy of the blob grid information 
						//from the BlobArray
						InputFile >> BlobArray[index][index2];
						CopyBlobArray[index][index2] = BlobArray[index][index2];
					}
				}

				//this for loop is used to move through the arrays created using the 
				//LocationArray, assigning each array the locations that will be searched 
				for (int index = 0; index < GridTestCases; index++)
				{
					//each integer pointer within the integer pointer array allocates memory for a new array
					//of integers that will be used to store the location data 
					LocationArray[index] = new int[2];
					for (int index2 = 0; index2 < 2; index2++)
					{
						InputFile >> LocationArray[index][index2];
					}
				}

				cout << "Blob " << (counter) << ":" << endl;

				//this for loop is used to process the information for each blob grid 
				for (int index = 0; index < GridTestCases; index++)
				{
					cout << "Location (";

					//this for loop is used to print the contents of the LocationArray
					for (int index2 = 0; index2 < 2; index2++)
					{

						if (index2 == 0)
						{
							RowNum = LocationArray[index][index2];

							//RowNum is adjusted to collect the first location number(row)
							//and is decremented by one to account for the BlobArray's size
							RowNum--;
						}

						if (index2 == 1)
						{
							cout << ",";
							ColumnNum = LocationArray[index][index2];

							//ColumnNum is adjusted to collect the second location number(column)
							//and is decremented by one to account for the BlobArray's size
							ColumnNum--;
						}

						//the current position of LocationArray is printed
						cout << LocationArray[index][index2];
					}
					cout << "):";

					//if the current position of the BlobArray (using RowNum and ColumnNum) is '.'
					//then the "NO BLOB" message is printed 
					if (BlobArray[RowNum][ColumnNum] == '.')
					{
						cout << " NO BLOB" << endl;
					}

					//if the current position of the BlobArray (using RowNum and ColumnNum) is '*'
					//then a recursive function is called, this will be used to find the size of the blob
					else if (BlobArray[RowNum][ColumnNum] == '*')
					{

						//the BlobSizeChecker function is used to find the size of the blob
						BlobSizeChecker(CopyBlobArray, RowSize, ColumnSize, RowNum, ColumnNum, BlobSize);
						cout << " Size " << BlobSize << " Blob." << endl;
					}

					//the BlobCopy function is used to restore the CopyBlobArray to its previous state before
					//it was passed through the BlobSizeChecker function.
					//BlobSize is set to 0
					BlobCopy(BlobArray, CopyBlobArray, RowSize, ColumnSize);
					BlobSize = 0;
				}
				cout << endl;
				counter++;

				//the for loop is used to free the memory used to create the LocationArray
				//the LocationArray pointer is set to nullptr
				for (int index = 0; index < GridTestCases; index++)
				{
					delete[] LocationArray[index];
				}
				LocationArray = nullptr;

				//the for loop is used to free the memory used to create the BlobArray and CopyBlobArray
				//the BlobArray and CopyBlobArray pointers are set to nullptr
				for (int index = 0; index < RowSize; index++)
				{
					delete[] BlobArray[index];
					delete[] CopyBlobArray[index];
				}
				BlobArray = nullptr;
				CopyBlobArray = nullptr;
			}
		}

		cout << "Run again (Y/N): ";
		cin >> CaseChecker;
		CaseChecker = toupper(CaseChecker);
		cout << endl;

		//this while loop is used to check if the CaseChecker variable contains a valid option
		//if not, the while loop will continue to loop until a valid option is made
		while (CaseChecker != 'Y' && CaseChecker != 'N')
		{
			cout << "An invalid input was made, please try again\n";
			cout << "Run again (Y/N): ";
			cin >> CaseChecker;
			CaseChecker = toupper(CaseChecker);
			cout << endl;
		}

		//the InputFile is closed
		InputFile.close();
	}
	return 0;
}

/*-------------------------------------------------------------------------------------------

BlobCopy function is used to return the CopyBlobArray to its original state 
(before the recursive function took place) so that it may be used again in the recursive function

-Within the parameter list, two arrays of character pointers are passed (MainBlob and CopyBlob)
-Within the parameter list, two integeres are passed (NumRows and NumColumns)

--------------------------------------------------------------------------------------------*/

void BlobCopy(char *MainBlob[], char *CopyBlob[], int NumRows, int NumColumns)
{
	//the for loop is used to move through both the CopyBlob and MainBlob arrays
	for (int index = 0; index < NumRows; index++)
	{
		for (int index2 = 0; index2 < NumColumns; index2++)
		{
			//the current position of CopyBlob is assigned the current (value)
			//position of MainBlob
			CopyBlob[index][index2] = MainBlob[index][index2];
		}
	}
}

/*-------------------------------------------------------------------------------------------

BlobSizeChecker is a recursive function that is used to find the size of a blob within the 
CopyBlobArray

-Within the parameter list, an array of character pointers is passed (CopyBlob)
-Within the parameter list, two integer values are passed, which are used to indicate the size of 
of the CopyBlob array (NumRows and NumColumns)
-Within the parameter list, two integer values are passed, which are used to indicate where 
a blob character was found (RowLoc and ColumnLoc)
-Within the parameter list, an integer value is passed by reference, which is used to keep track
of the blob's size (counter)

--------------------------------------------------------------------------------------------*/
void BlobSizeChecker(char *CopyBlob[], int NumRows, int NumColumns, int RowLoc, int ColumnLoc, int& counter)
{

	//because the current position in the grid is a blob charcater (*), the position is changed 
	//to a nonblob character (.) to prevent the function from looping between two blobs
	//the counter variable is also incremeted by one(adds onto itself using (+=1)
	CopyBlob[RowLoc][ColumnLoc] = '.';
	counter += 1;

	//this if statement is used if the blob character found was within the top left corner of the grid
	if (RowLoc == 0 && ColumnLoc == 0)
	{

		//the for loop moves through the top left corner and calls the BlobSizeChecker function if a 
		//blob character was found 
		for (int index = 0; index < 2; index++)
		{
			if (CopyBlob[RowLoc + index][ColumnLoc + 1] == '*')
			{
				BlobSizeChecker(CopyBlob, NumRows, NumColumns, (RowLoc + index), (ColumnLoc + 1), counter);
			}
			if (CopyBlob[RowLoc + index][ColumnLoc] == '*')
			{
				BlobSizeChecker(CopyBlob, NumRows, NumColumns, (RowLoc + index), ColumnLoc, counter);
			}
		}
	}

	//this else if statement is used if the blob character found was within the bottom left corner of the grid
	else if (RowLoc == NumRows - 1 && ColumnLoc == 0)
	{

		//the for loop moves through the bottom left corner and calls the BlobSizeChecker function if a 
		//blob character was found 
		for (int index = 0; index < 2; index++)
		{
			if (CopyBlob[RowLoc - index][ColumnLoc + 1] == '*')
			{
				BlobSizeChecker(CopyBlob, NumRows, NumColumns, (RowLoc - index), (ColumnLoc + 1), counter);
			}
			if (CopyBlob[RowLoc - index][ColumnLoc] == '*')
			{
				BlobSizeChecker(CopyBlob, NumRows, NumColumns, (RowLoc - index), ColumnLoc, counter);
			}
		}
	}

	//this else if statement is used if the blob character found was within the top right corner of the grid
	else if (RowLoc == 0 && ColumnLoc == NumColumns - 1)
	{

		//the for loop moves through the top right corner and calls the BlobSizeChecker function if a 
		//blob character was found 
		for (int index = 0; index < 2; index++)
		{
			if (CopyBlob[RowLoc + index][ColumnLoc - 1] == '*')
			{
				BlobSizeChecker(CopyBlob, NumRows, NumColumns, (RowLoc + index), (ColumnLoc - 1), counter);
			}
			if (CopyBlob[RowLoc + index][ColumnLoc] == '*')
			{
				BlobSizeChecker(CopyBlob, NumRows, NumColumns, (RowLoc + index), ColumnLoc, counter);
			}
		}
	}

	//this else if statement is used if the blob character found was within the bottom right corner of the grid
	else if (RowLoc == NumRows - 1 && ColumnLoc == NumColumns - 1)
	{

		//the for loop moves through the bottom right corner and calls the BlobSizeChecker function if a 
		//blob character was found 
		for (int index = 0; index < 2; index++)
		{
			if (CopyBlob[RowLoc - index][ColumnLoc - 1] == '*')
			{
				BlobSizeChecker(CopyBlob, NumRows, NumColumns, (RowLoc - index), (ColumnLoc - 1), counter);
			}
			if (CopyBlob[RowLoc - index][ColumnLoc] == '*')
			{
				BlobSizeChecker(CopyBlob, NumRows, NumColumns, (RowLoc - index), ColumnLoc, counter);
			}
		}
	}

	//this else if statement is used if the blob character found was within the first row of the grid
	else if (RowLoc == 0)
	{

		//the for loop moves through the first row and calls the BlobSizeChecker function if a 
		//blob character was found 
		for (int index = 0; index < 2; index++)
		{
			if (CopyBlob[RowLoc + index][ColumnLoc - 1] == '*')
			{
				BlobSizeChecker(CopyBlob, NumRows, NumColumns, (RowLoc + index), (ColumnLoc - 1), counter);
			}
			if (CopyBlob[RowLoc + index][ColumnLoc] == '*')
			{
				BlobSizeChecker(CopyBlob, NumRows, NumColumns, (RowLoc + index), (ColumnLoc), counter);
			}
			if (CopyBlob[RowLoc + index][ColumnLoc + 1] == '*')
			{
				BlobSizeChecker(CopyBlob, NumRows, NumColumns, (RowLoc + index), (ColumnLoc + 1), counter);
			}
		}
	}

	//this else if statement is used if the blob character found was within the last row of the grid
	else if (RowLoc == NumRows - 1)
	{

		//the for loop moves through the last row and calls the BlobSizeChecker function if a 
		//blob character was found 
		for (int index = 0; index < 2; index++)
		{
			if (CopyBlob[RowLoc - index][ColumnLoc - 1] == '*')
			{
				BlobSizeChecker(CopyBlob, NumRows, NumColumns, (RowLoc - index), (ColumnLoc - 1), counter);
			}
			if (CopyBlob[RowLoc - index][ColumnLoc] == '*')
			{
				BlobSizeChecker(CopyBlob, NumRows, NumColumns, (RowLoc - index), (ColumnLoc), counter);
			}
			if (CopyBlob[RowLoc - index][ColumnLoc + 1] == '*')
			{
				BlobSizeChecker(CopyBlob, NumRows, NumColumns, (RowLoc - index), (ColumnLoc + 1), counter);
			}
		}
	}

	//this else if statement is used if the blob character found was within the first column of the grid
	else if (ColumnLoc == 0)
	{

		//the for loop moves through the first column and calls the BlobSizeChecker function if a 
		//blob character was found 
		for (int index = 0; index < 2; index++)
		{
			if (CopyBlob[RowLoc - 1][ColumnLoc + index] == '*')
			{
				BlobSizeChecker(CopyBlob, NumRows, NumColumns, (RowLoc - 1), (ColumnLoc + index), counter);
			}
			if (CopyBlob[RowLoc][ColumnLoc + index] == '*')
			{
				BlobSizeChecker(CopyBlob, NumRows, NumColumns, RowLoc, (ColumnLoc + index), counter);
			}
			if (CopyBlob[RowLoc + 1][ColumnLoc + index] == '*')
			{
				BlobSizeChecker(CopyBlob, NumRows, NumColumns, (RowLoc + 1), (ColumnLoc + index), counter);
			}
		}
	}

	//this else if statement is used if the blob character found was within the last column of the grid
	else if (ColumnLoc == NumColumns - 1)
	{

		//the for loop moves through the last column and calls the BlobSizeChecker function if a 
		//blob character was found 
		for (int index = 0; index < 2; index++)
		{
			if (CopyBlob[RowLoc - 1][ColumnLoc - index] == '*')
			{
				BlobSizeChecker(CopyBlob, NumRows, NumColumns, (RowLoc - 1), (ColumnLoc - index), counter);
			}
			if (CopyBlob[RowLoc][ColumnLoc - index] == '*')
			{
				BlobSizeChecker(CopyBlob, NumRows, NumColumns, RowLoc, (ColumnLoc - index), counter);
			}
			if (CopyBlob[RowLoc + 1][ColumnLoc - index] == '*')
			{
				BlobSizeChecker(CopyBlob, NumRows, NumColumns, (RowLoc + 1), (ColumnLoc - index), counter);
			}
		}
	}

	//if none of the previous conditions were met, then this else statement will be executed 
	//this else statment searches in a (3x3) area for a blob character 
	//(implies that the blob character found is not located along any bondaries such as the min and max, row and column values)
	else
	{

		//the for loop moves through the (3x3) area and calls the BlobSizeChecker function if a 
		//blob character was found 
		for (int index = 0; index < 3; index++)
		{
			if (CopyBlob[RowLoc - 1][((ColumnLoc - 1) + index)] == '*')
			{
				BlobSizeChecker(CopyBlob, NumRows, NumColumns, (RowLoc - 1), (((ColumnLoc - 1) + index)), counter);
			}
			if (CopyBlob[RowLoc][((ColumnLoc - 1) + index)] == '*')
			{
				BlobSizeChecker(CopyBlob, NumRows, NumColumns, RowLoc, (((ColumnLoc - 1) + index)), counter);
			}
			if (CopyBlob[RowLoc + 1][((ColumnLoc - 1) + index)] == '*')
			{
				BlobSizeChecker(CopyBlob, NumRows, NumColumns, (RowLoc + 1), (((ColumnLoc - 1) + index)), counter);
			}
		}
	}
}