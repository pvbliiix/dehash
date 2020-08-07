#include <crypt.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
  const char salt[16] = "$1$ocwCRNW6$";
  char value[64];

  FILE* dictionary = fopen("dictionary_polish.dic", "r");
  FILE* decrypted = fopen("decrypted.txt", "w");

  char hash[34] = "$1$ocwCRNW6$u1e9dUjacFOB4l6c07FKx/";

  while(fscanf(dictionary, "%s", value) != EOF)
  {
    char *hashfake;
    int options = 4;

    char valueog[64];
    memcpy(valueog, value, sizeof(value));

    for(int i = 0; i < 10000; i++)
    {
      memcpy(value, valueog, sizeof(valueog));
      for(int j = 0; j < options; j++)
      {
        char num[5];
        sprintf(num, "%d", i);
        printf("num: %s\n", num);
      switch(j)
      {
        case 0:
          break;
        case 1:
          value[0] = toupper(value[0]);
          break;
        case 2:
          strcat(value, num);
          value[0] = tolower(value[0]);
          break;
        case 3:
          value[0] = toupper(value[0]);
          break;
        default:
          break;
      }
      hashfake = crypt(value, salt);

      printf("hash: %s, value: %s\n", hashfake, value);

      if(strcmp(hashfake, hash) == 0)
      {
        fprintf(decrypted, "HASH: %s\nPASSWORD: %s\n-----------------\n", hashfake, value);
        printf("======================\nHASH %s DECRYPTED: %s\n", hashfake, value);
        fclose(decrypted);
        getchar();
      }
    }
    }
  }
  return 0;
}
