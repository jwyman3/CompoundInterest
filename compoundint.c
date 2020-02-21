/*
 *  Program Name: COP 2220 Project 4
 *  Description: Project 4
 *  Author: Jacob Wyman
 *  Date: Dec 1st, 2019
 *  N-Number: N01430059
 */
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#define UP_TRM_LIMIT 99
#define LW_TRM_LIMIT 1
#define UP_APR_LIMIT 24.99
#define LW_APR_LIMIT .1
#define UP_DEP_LIMIT 100000
#define LW_DEP_LIMIT 1
#define PERIODS 1
#define MAX_ARRAY_SZ 99
#define EXTENSION ".txt"
#define EXTENSION_LENGHT 4

//Function prototypes
bool printinstructions(void);
bool getTermYears(int*, int, int);
bool getAPR(float*, float, float);
bool getInitialBalance(double*, double, double);
bool withinLimits(double value, double upLimit, double lowLimit);
bool produceSavingsSchedule(int, float, double);

//Add your function prototypes
bool outputFile();
bool printSavingsSchedule(int years, float APR, double principal, char *filename);
bool addExtension(char *fileName);
//get output filename from user
//pass in array of values and file name to print out to file

int main()
{
	//Local Declarations
	int term = 0;
	float APR = 0.0;
	double deposit = 0.0;
	//declare your array here usinng the defined constant
	char fileName[MAX_ARRAY_SZ] = {0};
	//Local Statements
	if(printinstructions())
	{
		printf("Do the calculations.\n");
		getTermYears(&term, UP_TRM_LIMIT, LW_TRM_LIMIT);
		getAPR(&APR, UP_APR_LIMIT, LW_APR_LIMIT);
		getInitialBalance(&deposit, UP_DEP_LIMIT, LW_DEP_LIMIT);
		produceSavingsSchedule(term, APR, deposit);
		//Call your added functions here
		outputFile(&fileName);
		addExtension(fileName);
		printSavingsSchedule(term, APR, deposit, fileName);
	}
	else
		printf("User wants to quit.\n");
		
	return 0;
}//end main
//Dont add Commenting here
bool printinstructions()
{
	char input[80]={0};
	char userChoice = ' ';
	printf("This program will create a savings schedule for an annual compounding savings account.\n");
	printf("Enter in 'c' to continue or 'q' to quit.\n");
	do{
		scanf(" %s", &input);
		userChoice = input[0];
		userChoice = tolower(userChoice);
		if(userChoice == 'c')
			return true;
		else if(userChoice == 'q')
			return false;
		else
			printf("The value you entered is invalid, please try again.\n");
	}while(userChoice != 'q' || userChoice != 'c');
}//end function
//Dont add Commenting here
bool getTermYears(int* term, int upLimit, int lowlimit)
{
	do{
		printf("Enter in the term for the savings in years.\n");
		scanf(" %d", *&term);
		if(withinLimits((double)*term, 100.0, 0.0))
			break;
		printf("The input was not correct.\n");
	}while(true);
	return true;
}//end function
//Dont add Commenting here
bool getAPR(float* APR, float upLimit, float lowLimit)
{
	do{
		printf("Enter the Annual Percentage Rate (APR).\n");	
		scanf(" %f", *&APR);
		if(withinLimits((double)*APR, (double)upLimit,(double)lowLimit))
			break;
		printf("The input was not correct.\n");
	}while(true);
	return true;
}//end function
//Dont add Commenting here
bool getInitialBalance(double* principal, double upLimit, double lowLimit)
{
	do{
		printf("Enter in the initial balance (principal).\n");
		scanf(" %lf", *&principal);
		if(withinLimits((double)*principal, (double)upLimit,(double)lowLimit))
			break;
		printf("The input was not correct.\n");
	}while(true);
	return true;
}//end function
//Dont add Commenting here
bool withinLimits(double value, double upLimit, double lowLimit)
{
	printf("The value entered: %10.2lf\n", value);
	if((value <= upLimit) && (value >= lowLimit))
		return true;
	else
		return false;
}
//Dont add Commenting here
bool produceSavingsSchedule(int years, float APR, double principal)
{
	double balance = principal;//The initial starting balance
	double begBalance = 0.0;//Balance at beginning of each term
	double totInt = 0.0;//Accumulated interest
	double earnings = 0.0;//interst earned in period
	float decRate = APR / 100;//decimal value of APR
	printf("Rate %4.2f% Balance $%10.2lf Term: %d years\n\n", APR,balance, years);
	printf("| Period |  Beginning Balance |");
	printf(" Earned Interest | Ending Balance |");
	printf(" Accrued Interest |\n");
	printf("|________|____________________|_________________|________________|__________________|\n");
	for(int i = 0 ; i < years; i++)
	{	
	
		begBalance = balance;
		earnings = balance * decRate;	
		balance += earnings;
		totInt += earnings;
		printf("|     %3d", i);
		printf("|          %10.2lf", begBalance);
		printf("|       %10.2lf", earnings);
		printf("|      %10.2lf", balance);
		printf("|        %10.2lf", totInt);
		printf("|\n");
	}

	return true;
}//end function

bool outputFile(char *filename){

	printf("Enter file name: ");
	scanf("%s", filename);
}//End Function

bool printSavingsSchedule(int years, float APR, double principal, char *filename)
{

	FILE *out_file = fopen(filename, "w");


	double balance = principal;//The initial starting balance
	double begBalance = 0.0;//Balance at beginning of each term
	double totInt = 0.0;//Accumulated interest
	double earnings = 0.0;//interst earned in period
	float decRate = APR / 100;//decimal value of APR
	fprintf(out_file, "Rate %4.2f%% \tBalance $%10.2lf \tTerm: %d years\n\n", APR,balance, years);
	fprintf(out_file, "| Period |  Beginning Balance |");
	fprintf(out_file, " Earned Interest | Ending Balance |");
	fprintf(out_file, " Accrued Interest |\n");
	fprintf(out_file, "|________|____________________|_________________|________________|__________________|\n");
	for(int i = 0 ; i < years; i++)
	{	
	
		begBalance = balance;
		earnings = balance * decRate;	
		balance += earnings;
		totInt += earnings;
		fprintf(out_file, "|     %3d", i);
		fprintf(out_file, "|          %10.2lf", begBalance);
		fprintf(out_file, "|       %10.2lf", earnings);
		fprintf(out_file, "|      %10.2lf", balance);
		fprintf(out_file, "|        %10.2lf", totInt);
		fprintf(out_file, "|\n");
	}

	
	return true;
}//end function

bool addExtension(char *fileName){
	int i = 0;
	int j = 0;
	char extension[EXTENSION_LENGHT] = {EXTENSION};
	do{
		if(fileName[i] != 0){
			i++;
		}else if(fileName[i] == 0){
			break;
		}
	}while(1);
		for(j = 0; j < EXTENSION_LENGHT; j++, ++i){
		fileName[i] = extension[j];
		}
	return true;
}//End Function
