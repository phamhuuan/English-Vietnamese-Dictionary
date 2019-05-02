#include <stdio.h>

static char code[128] = {0};

const char* soundex(const char *s){
	static char out[5];
	int c, prev, i;

	out[0] = out[4] = 0;
	if(!s || !*s) return out;

	out[0] = *s++;

	/* first letter, though not coded, can still affect next letter: Pfister */
	prev = code[(int)out[0]];printf("Out[0] = %d\n", (int)out[0]);printf("Prev1 = %d\n", prev);
	for(i = 1; *s && i < 4; s++){
		if((c = code[(int) *s]) == prev) {printf("c(continue) = %d\n", c);continue;}
		if(c == -1) prev = 0;	/* vowel as separator */
		else if(c > 0){
			out[i++] = c + '0';
			prev = c;printf("c(prev) = %d\n", c);
            printf("Prev2 = %d\n", prev);
		}
	}
	while(i < 4) out[i++] = '0';
	return out;
}

int main(){
    printf("%s\n", soundex("1234"));
}