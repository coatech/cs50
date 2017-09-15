/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    int l = 0, r = n-1;
  while (l <= r)
  {
    int m = l + (r-l)/2;

    // Check if value is present at mid
    if (values[m] == value) 
        return m;  

    // If value greater, ignore left half  
    if (values[m] < value) 
        l = m + 1; 

    // If value is smaller, ignore right half 
    else 
         r = m - 1; 
  }
  return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
   int temp;
   int i,j;
	
   bool swapped = false;
   
   // loop through all numbers 
   for(i = 0; i < n-1; i++) { 
      swapped = false;
		
      // loop through numbers falling ahead 
      for(j = 0; j < n-1-i; j++) {

         // check if next number is lesser than current no
         //   swap the numbers. 
         //  (Bubble up the highest number)
			
         if(values[j] > values[j+1]) {
            temp = values[j];
            values[j] = values[j+1];
            values[j+1] = temp;

            swapped = true;
         }
			
      }

      // if no number was swapped that means 
      //   array is sorted now, break the loop. 
      if(!swapped) {
         break;
      }
   }
   return;
}
