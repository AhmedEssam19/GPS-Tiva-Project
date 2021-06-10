#include "man_string.h"
void itoa(int n, char s[])
{
	 int i, sign;

	 if ((sign = n) < 0)  /* record sign */
			 n = -n;          /* make n positive */
	 i = 0;
	 do {       /* generate digits in reverse order */
			 s[i++] = n % 10 + '0';   /* get next digit */
	 } while ((n /= 10) > 0);     /* delete it */
	 if (sign < 0)
			 s[i++] = '-';
	 s[i] = '\0';
	 reverse_here(s);
}
int str_len(const char* s)
{
	int length = 0;
	while (*s++) {
		length++;
	}
	return length;
}


void reverse_here(char s[])
{
	 int i, j;
	 char c;

	 for (i = 0, j = str_len(s)-1; i<j; i++, j--) {
			 c = s[i];
			 s[i] = s[j];
			 s[j] = c;
	 }
}
