#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
	//declarations of variables
	int amount, count=0;
	float change;
	//prompting and validating user input;
	do{
		printf("O hai! ");
		printf("How much change is owed?\n");
		change = get_float();
	}while(change < 0);
    //converting dollas to cent
	change = change * 100;
	amount =  roundf(change);
    //looking for the greedy path
	while(amount >= 25){
	    count = count + 1; 
	    amount = amount - 25;
	}

	while(amount >= 10){
	    count = count + 1;
	    amount = amount - 10;
	}

	while(amount >= 5){
	    count = count + 1;
	    amount = amount - 5;
	}

	while(amount >= 1){
	    count = count + 1;
	    amount = amount - 1;
	}
	// printing the finally number of coin
	printf("%i\n", count);
}