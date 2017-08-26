#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc != 2 ){return 1;}
    string key = argv[1];
    int keylen = strlen(key);
    bool flag = false, flag1 = false ;
    
    for (int i = 0, m = strlen(key); i < m; i++){
      if (isalpha(key[i])){flag1 = true;}
      else{flag = true;}
     }

    if (argc == 2 && flag == false)
    {
        printf("plaintext: ");
        string s = get_string();
        printf("ciphertext: ");
        if (s != NULL){
            int j = 0;
            for (int i = 0, n = strlen(s); i < n; i++){
                if(isupper(s[i])){
                    char pi = s[i] - 65;
                    char key_j = toupper(key[j]) - 65;
                    char ci =(pi + key_j) % 26;
                    ci = ci + 65; 
                    printf("%c", toupper(ci));
                    j = (j + 1) % keylen;
                }
                else if(islower(s[i])){
                    char pi = s[i] - 97;
                    char key_j = tolower(key[j]) - 97;
                    char ci =(pi + key_j) % 26;
                    ci = ci + 97; 
                    printf("%c", tolower(ci));
                    j = (j + 1) % keylen;
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