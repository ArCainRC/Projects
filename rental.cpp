#include <iostream>
#include <string>
using namespace std;

int main()
{
	double odStart;	//intializing all the variables
	double odEnd;
	double days;
	string custName;
	string lux; 
	double month;
	double rentCharge;
	double baseCharge;
	double monthRate;
	double miles;
	string output;
	int check=0;	// a check variable that decides whether to output a value or an error message
	
		cout << "Odometer at start: ";
		cin >> odStart;
		cout << "Odometer at end: ";
		cin >> odEnd;
		miles = odEnd - odStart;
		cout << "Rental days: ";
		cin >> days;
		cout << "Customer name: ";
		cin.ignore(10000, '\n');
		getline(cin, custName);
		cout << "Luxury car ? (y / n): ";
		getline(cin, lux);
		cout << "Month (1=Jan, 2=Feb, etc.): ";
		cin >> month;

		if (lux == "y")	//to calculate the base charge per day
		{
			baseCharge = 61 * days;
		}
		else
		{
			baseCharge = 33 * days;
		}

		if ((month >= 1 && month <= 3) || month == 12) //monthly rate for winter months vs normal months
		{
			monthRate = 0.27;
		}
		else
		{
			monthRate = 0.21;
		}

		if (miles <= 100)   //to calculate the charge per mile when total distance is <100
		{
			rentCharge = baseCharge + miles * 0.27;
		}
		else if (miles >= 100 && miles <= 400)	//to calculate the charge per mile when total distance is between 100 and 400
		{
			rentCharge = baseCharge + 27 + (miles - 100)*monthRate;
		}
		else if (miles > 400)	//to calculate the charge per mile when total distance is >400
		{
			rentCharge = baseCharge + 27 + 300 * monthRate + (miles - 400)*0.19;
		}

		cout.setf(ios::fixed);
		cout.precision(2);
		cout << "---" << endl;
		if (odStart < 0) 
		{
			output = "The starting odometer reading must be nonnegative.";
			check = 1;
		}
		else if (odStart > odEnd)
		{
			output = "The final odometer reading must be at least as large as the starting reading.";
			check = 1;
		}
		else if (days <= 0)
		{
			output = "The number of rental days must be positive.";
			check = 1;
		}
		else if (custName.empty() == true)
		{
			output = "You must enter a customer name.";
			check = 1;
		}
		else if (lux != "n" && lux != "y")
		{
			output = "You must enter y or n.";
			check = 1;
		}
		else if (month < 1 || month > 12)
		{
			output = "The month number must be in the range 1 through 12.";
			check = 1;
		}

		if (check == 0) //check will be equal to 1 if an error has occurred
		{
			cout << "The rental charge for " << custName << " is $" << rentCharge;
		}
		else	//the output will be whatever error message was triggered
		{
			cout << output;
		}


}