#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

bool isValidUppercaseStateCode(string stateCode)    // method provided to verify state codes
{
	const string codes =
		"AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
		"LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
		"OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
	return (stateCode.size() == 2 &&
		stateCode.find('.') == string::npos  &&  // no '.' in stateCode
		codes.find(stateCode) != string::npos);  // match found
}


bool hasProperSyntax(string pollData)
{
	int size = pollData.size();
	int raw = 0;    // to create a variable for the position of the next letter after a comma to be stored

	for (int i = raw; i < size; )   // loop used to evaluate every character of the string up to the last character
	{
		string stateCode;
		for (int j = i + 1; i <= j; i++)    // this lets us check a string consisting of two letters
		{
			if (i >= size) // size check to prevent out of bounds error
			{
				return(false);
			}
			char a = toupper(pollData[i]);   // turn the characters of the state code to uppercase for evaluation
			stateCode += a;
		}

		if (!isValidUppercaseStateCode(stateCode))   // using the method given to check valdity of state code
		{
			return(false);
		}
		
		if (i == size)
		{
			return(true);
		}

		int commacheck = 0; // a variable used to restart the while loop below either when a comma is found(in order to recheck state code) or to end the loop if all characters are evaluated
		while (commacheck == 0)
		{
			if (i >= size) // size check to prevent out of bounds error
			{
				return(false);
			}

			if (isdigit(pollData[i]))    // the character checked will be the one right after the state code, which must be a digit
			{
				i++;
				if (i >= size)   // size check to prevent out of bounds error
				{
					return(false);
				}
				if (isdigit(pollData[i]))    // if there is a digit now, then it's a 2 digit number of seats
				{
					i++;
					if (i >= size)   // size check to prevent out of bounds error
					{
						return(false);
					}
					if (isalpha(pollData[i]))    // this character must be the party code (an alphabet)       
					{
						i++;
						if (size == i) // if this party code is the last character of the string, this lets us exit the while loop and eventually exit the for loop  
						{
							commacheck = 1; // change of commacheck in order to exit while loop
							continue;
						}
					}
					else
					{
						return(false);
					}
				}
				else if (isalpha(pollData[i]))   // if there is an alphabet, this means that it was a 1 digit number of seats and we check for party code now
				{
					i++;
					if (size == i) // if this party code is the last character of the string, this lets us exit the while loop and eventually exit the for loop
					{
						commacheck = 1; // change of commacheck in order to exit while loop
						continue;
					}
				}
				else
				{
					return(false);
				}
			}
			else if (pollData[i] == ',') // if a comma is encountered, we change commacheck in order to prepare for evaluating a new state from the start of the for loop
			{
				if (i == size - 1)   // without this, a string ending in a comma is treated as legitimate
				{
					return(false);
				}
				i++;
				commacheck = 1; // change of commacheck in order to exit while loop
				continue;
			}
			else
			{
				return(false);
			}
		}

		if (commacheck == 1)
		{
			raw = i;  // assigns the current value of i to raw
			continue;  // restarts loop back to checking statecode, or ends it if all characters have been evaluated
		}
	}
	return(true);
}


int tallySeats(string pollData, char party, int& seatTally)
{
	if (!hasProperSyntax(pollData))  // verifies if string is a proper data string 
	{
		return 1;
	}

	if (!isalpha(party)) // checks if party is a letter
	{
		return 2;
	}

	seatTally = 0;
	int size = pollData.size();	

	for (int i = 2; i < size; i++) // No need to check for i=0, as the first letter of a legitimate poll string will have no value related to it, and position 0-1 will be out of bounds
	{
		if (toupper(party) == toupper(pollData[i]))
		{
			if (isdigit(pollData[i - 1]))	// to verify that the party name isn't a letter of a state code
			{
				char a = pollData[i - 1];
				int b;
				b = a - '0';
				if (isdigit(pollData[i - 2]))  // for a 2 digit number of seats
				{
					char a1 = pollData[i - 2];
					int b1;
					b1 = a1 - '0';
					b1 *= 10; // we multiply the digit in the tens place by 10 and add it to the previous number to get number of seats for one state
					b += b1;
				}
				seatTally += b;
			}
		}
	}
	return 0;
}

int main()
{
	assert(hasProperSyntax("CT5D,NY9R17D1I,VT,ne3r00D"));
	assert(hasProperSyntax("AL35D6E,AZ7I64D"));
	assert(!hasProperSyntax("ZT5D,NY9R17D1I,VT,ne3r00D"));
	assert(hasProperSyntax("CT"));
	int seats;
	seats = -999;    // so we can detect whether tallySeats sets seats
	assert(tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", 'd', seats) == 0 && seats == 22);
	seats = -999;    // so we can detect whether tallySeats sets seats
	assert(tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", '%', seats) == 2 && seats == -999);
	seats = -999;    // so we can detect whether tallySeats sets seats
	assert(tallySeats("a", '%', seats) == 1 && seats == -999);
	seats = -999;    // so we can detect whether tallySeats sets seats
	assert(tallySeats("fsdgfchg", 'a', seats) == 1 && seats == -999);
	seats = -999;    // so we can detect whether tallySeats sets seats
	assert(tallySeats("", 'a', seats) == 0 && seats == 0);
	seats = -999;    // so we can detect whether tallySeats sets seats
	assert(tallySeats(",", '%', seats) == 1 && seats == -999);
	seats = -999;    // so we can detect whether tallySeats sets seats
	assert(tallySeats("AL", 'A', seats) == 0 && seats == 0);
	seats = -999;    // so we can detect whether tallySeats sets seats
	assert(tallySeats("AL34D,AZ", 'A', seats) == 0 && seats == 0);


	cout << "All tests succeeded" << endl;

}