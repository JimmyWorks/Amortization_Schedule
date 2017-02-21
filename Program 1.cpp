//============================================================================
// Name        : CS1337 Program 1.cpp
// Author      : Jimmy Nguyen (UTD-ID: 2021347379)
// Version     : Final Draft
// Description : This program is written to calculate and print a single or
//               multiple loan re-payment schedules for the user.  The program
//               will import a local .txt file.  The file must be formatted
//               to input an initial number of schedules to be printed followed
//               by three numbers, respectively: balance, interest rate and fixed
//               monthly payments.  The program will then print the schedule
//               to the console and export a copy to a user-defined .txt output
//               file.  The program does check for the following errors:
//               improper # of schedules in input file, cannot locate input file
//               and unable to create output file.
//============================================================================

#include <iostream>
#include <fstream>  //header that includes file commands
#include <string>  //header that includes string functions
#include <iomanip>  //header that includes printout formatting
using namespace std;  //namespacing allows you to write functions that have the same name

void perform_calculations(float, float, float, ostream& outfile);
// Function prototype for calculating loan payment variables and printing to console and copy to user-defined outfile (outfile must be passed by reference!!)

int main() {

	string infile_name, outfile_name;  // Name holders for infile and outfile defined by user input
	int count_of_items_in_file = -34404;  // The first variable in the input file defining # of loan re-payment schedules to be performed (-34404 is error sentinel)

	ifstream infile;  //the actual input file object
	ofstream outfile;  //the actual output file object

//Prompt the User for the Input File
	askinput:  														// Error goto if the user defines an improper input file
	cout << "Please enter the input file name: " << endl; 			//prompt user
	cin >> infile_name; 											//grab input
	cout << "The user entered file name: " << infile_name << endl; //debug check

//Open the input file for reading.
	infile.open(infile_name.c_str()); //.open is a method but it only takes char* so a method for converting a string to char* is needed

//Check if we successfully opened input file.
	if (!infile){  // if infile != 0

		cout << "Error: Unable to open file '" << infile_name << "' for reading." << endl;
		cout << "Please try again." << endl << endl;
		goto askinput;												//Send them back to the beginning to try again
	}

	infile >> count_of_items_in_file; // Grab the first value from file

	if(count_of_items_in_file<1){ //Check if number of schedules to be printed is a valid positive integer (at least 1 or greater)
		cout << "Error: '" << infile_name << "' wants to print '" << count_of_items_in_file << "' schedules.\n" << "At least 1 schedule or more is required." << endl;
		cout << "Closing file '" << infile_name << "'.  Please try again below." << endl << endl;
		infile.close();		// Close any files opened;
		goto askinput;												//Send them back to the beginning to try again
	}

		cout << "Successfully opened the input file!"  // Note: Remember to close all files before program terminates
		<< endl;

	//Prompt the user for the output file
	askoutput:
	cout << "Please enter the output file name: " << endl;
	cin >> outfile_name; //grab input
	cout << "User entered output file name as: " << outfile_name << endl;

	//Open the output file for writing
	outfile.open(outfile_name.c_str());
	//Check if we successfully opened the file
	if (!outfile){
	cout << "Error:  Unable to open file '" << outfile_name << "' for writing." << endl;
	cout << "Please try again." << endl << endl;
	goto askoutput;

}
	else
		cout << "Successfully opened the output file!" << endl << endl << endl << endl << endl;
	// Note: Remember to close all files before program terminates

	//Begin Running Loan Repayment Schedule Calculations and Printing Out Report
		cout << "Number of payment schedules: " << count_of_items_in_file << endl << endl;
		outfile << "Number of payment schedules: " << count_of_items_in_file << endl << endl;


		// Loop through and read values and calculate via a function.
			for (int i=0; i<count_of_items_in_file; i++)
			{
				float balance, int_rate, monthly;

				infile >> balance;
				infile >> int_rate;
				infile >> monthly;

				cout << std::fixed << std::setprecision(2)<< "Starting Balance: $" << balance << endl;
				cout << std::fixed << std::setprecision(3)<< "Annual Interest Rate: " << int_rate << endl;
				cout << std::fixed << std::setprecision(2) << "Monthly Payment: $" << monthly << endl << endl;

				outfile << std::fixed << std::setprecision(2)<< "Starting Balance: $" << balance << endl;
				outfile << std::fixed << std::setprecision(3)<< "Annual Interest Rate: " << int_rate << endl;
				outfile << std::fixed << std::setprecision(2) << "Monthly Payment: $" << monthly << endl << endl;

				perform_calculations(balance, int_rate, monthly, outfile);
			}

			cout << "Schedules complete." << endl;
			cout << "Written by: Jimmy Nguyen." << endl;
			cout << "For all questions, email: Jimmy@JimmyWorks.net" << endl;

			outfile << "Written by: Jimmy Nguyen." << endl;
			outfile << "For all questions, email: Jimmy@JimmyWorks.net" << endl;

			// Done... clean up and exit
			infile.close();		// Close any files we open;
			outfile.close();	// Close any files we open;


	return 0;
}


void perform_calculations(float balance, float int_rate, float monthly, ostream &outfile)
{
	int_rate = int_rate/12.00;
	int payment =1;
	float interest, principal, interest_total=0.00;

	std::cout << std::fixed << std::setprecision(2); //fixing the decimal places of float printouts to 2 decimal places
	std::cout << std::left << setw(8) << "Payment" << std::right << setw(15) << "Amount" << setw(15) << "Interest" << setw(15) << "Principal" << setw(20) << "Balance" << endl << endl;
	outfile << std::left << setw(8) << "Payment" << std::right << setw(15) << "Amount" << setw(15) << "Interest" << setw(15) << "Principal" << setw(20) << "Balance" << endl << endl;

	while(balance > 0){

		interest = int_rate*balance;  //calculation for dollars paid towards interest
		interest_total = interest_total + interest;

		if(balance <= monthly)
			monthly = balance+interest;

		principal = monthly-interest;
		balance = balance - principal;  //calculation for new balance printed and used in next iteration

		std::cout << std::left << setw(8)<< payment << std::right << setw(15) << monthly << setw(15) << interest << setw(15) << monthly-interest << setw(20)<< balance << endl;
		outfile << std::fixed << std::setprecision(2) << std::left << setw(8)<< payment << std::right << setw(15) << monthly << setw(15) << interest << setw(15) << monthly-interest << setw(20)<< balance << endl;

		payment++;
	}

	cout << endl << "Total Payments Made: " << payment-1 << endl;
	cout << "Total Interest Paid: $" << interest_total << endl << endl;
	cout << "------------------------------------------------------" << endl << endl;

	outfile << endl << "Total Payments Made: " << payment-1 << endl;
	outfile << "Total Interest Paid: $" << interest_total << endl << endl;
	outfile << "------------------------------------------------------" << endl << endl;

	return;
}

