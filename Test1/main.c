#include <stdio.h>
#include <stdlib.h>

char toLower(char ch); 
char *scanString();
void convertString(char *str);

int main(void) {
  char *string = NULL;
  string = scanString();

  if (string) {
    convertString(string);
    printf("%s", string);
    free(string);
  }

  return 0;
}

char toLower(char ch) {
    if (ch >=65 && ch <= 90) 
      ch = ch + 32;
    return ch;
}

char *scanString() {
  unsigned int i = 0;  // -2 is used as an arbitrary value to ignore real values

  char *string = NULL;
  string = malloc((i + 10)* sizeof(char));  // create a buffer size of 10

  if (!string) return NULL;  // allocation fail

  while (1) {
    int ch = getchar();

    if (ch == '\0' || ch == EOF || ch == '\n') {  // check end character
      string[i] = '\0';
      break;
    }

    string[i] = toLower(ch);
    i++;

    if (i % 10 == 0) {
      char *temp = string;
      string = realloc(string, (i + 10) * sizeof(char));
      if (string == NULL) {  // failed to allocate (too big)
        free(temp);
        break;
      }
    }
  }
  return string;
}

void convertString(char *str) {
  unsigned int index[256] = {0};  // index to store repeated elements 
  char *tmp = str;
  while (*tmp != '\0') {
    index[(int)*tmp]++;
    tmp++;
  }
  while (*str != '\0') {
    if (index[(int)*str] > 1) {
      *str = ')';
    } else {
      *str = '(';
    }
    str++;
  }
}