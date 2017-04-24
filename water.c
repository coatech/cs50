#include <stdio.h>
#include <cs50.h>

int main(void)
{
	//declarations of variables
	int mins,bottles;
	
	//prompting and validating user input;
	do{
		printf("Minutes: ");
		mins = get_int();
	}while(mins < 0);
	
	//calculating equivalent in bottles;
	bottles = 12 * mins;
	
	//printing the equivalent in bottles;
	printf("Bottles: %i\n",bottles);
}