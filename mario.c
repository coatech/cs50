#include <stdio.h>
#include <cs50.h>

int main(void)
{
	//declarations of variables
	int height,i, space, j=0;
	
	//prompting and validating user input;
	do{
		printf("Height: ");
		height = get_int();
	}while(height < 0 || height > 23);
	
	for(i=1; i<=height; ++i, j=0)
    {
        for(space=1; space<=height-i; ++space)
        {
            printf(" ");
        }

        for(j=1; j<=i+1; ++j)
        {
            printf("#");
        }
        printf("\n");
    }
}