#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        int key = atoi(argv[1]);
        printf("plaintext: ");
        string s = get_string();
        printf("ciphertext: ");
        if (s != NULL){
            for (int i = 0, n = strlen(s); i < n; i++){
                if(isupper(s[i])){
                    char pi = s[i] - 65;
                    char ci =(pi + key) % 26;
                    ci = ci + 65; 
                    printf("%c", toupper(ci));
                }
                else if(islower(s[i])){
                    char pi = s[i] - 97;
                    char ci =(pi + key) % 26;
                    ci = ci + 97; 
                    printf("%c", tolower(ci));
                }
                else{
                    printf("%c", s[i]);
                }
            }
            printf("\n");
        }
        return 0;
    }
    else{
        return 1;
    }
}