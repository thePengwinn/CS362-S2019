#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    
	int temp;
	char c;

		temp = (rand() % 95) + 32;
		c = (char)temp;


    return c;
}

char *inputString()
{
   // create a string to fill with random letters(the first 5 letters select from e - t)
	char str[6];
	int i;
	for (i = 0; i < 5; i++) {
		int temp1 = (rand() % 16) + 101;
		char c = (char)temp1;
		str[i] = c;
	}

	// random number between 0 and 15, anything over 3 puts expected end of '\0'
	int temp1 = (rand() % 16);
	
	//normal end
	if (temp1 > 3) {
		str[5] = '\0';
	}

	//0 gives string of 6 random chars and random end
	else if (temp1 == 0) {
		for (i = 0; i < 6; i++) {
			int temp2 = (rand() % 96) + 32;
			char c = (char)temp2;
			str[i] = c;
		}
	}

	//1 gives string of 5 with random end letter
	else if (temp1 == 1) {
		int temp2 = (rand() % 96) + 32;
		str[5] = (char)temp2;
	}

	//2 gives too short of a string
	else if (temp1 == 2) {
		char str2[5];
		int i;
		for (i = 0; i < 5; i++) {
			int temp1 = (rand() % 16) + 101;
			char c = (char)temp1;
			str[i] = c;
		}
		char *s = str2;
		return s;
	}

	//3 gives too long a string
	else if (temp1 == 3) {
		char str2[7];
		int i;
		for (i = 0; i < 7; i++) {
			int temp1 = (rand() % 16) + 101;
			char c = (char)temp1;
			str[i] = c;
		}
		char *s = str2;
		return s;
	}




	char *s = str;
	return s;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
