#define WORD_MAX 255
#define MEAN_MAX 10000
static char code[128] = {0};

void separate_mean(char* mean);
void initDic(char *filename);
void initSoundex(char *filename);
void add_code(const char *s, int c);
void init();
char* soundex(const char *s);

void add_code(const char *s, int c){
	while(*s){
		code[(int)*s] = code[0x20 ^ (int)*s] = c;
		s++;
	}
}
 
void init(){
	static const char *cls[] =
		{ "AEIOU", "", "BFPV", "CGJKQSXZ", "DT", "L", "MN", "R", 0};
	int i;
	for (i = 0; cls[i]; i++)
		add_code(cls[i], i - 1);
}

char *soundex(const char *s){
	static char out[5];
	int c, prev, i;

	out[0] = out[4] = 0;
	if(!s || !*s) return out;

	out[0] = *s++;

	/* first letter, though not coded, can still affect next letter: Pfister */
	prev = code[(int)out[0]];
	for(i = 1; *s && i < 4; s++){
		if((c = code[(int) * s]) == prev) continue;
		if(c == -1) prev = 0;	/* vowel as separator */
		else if(c > 0){
			out[i++] = c + '0';
			prev = c;
		}
	}
	while(i < 4) out[i++] = '0';
	return out;
}

void initSoundex(char *filename){
	FILE *datafile;
	datafile = fopen(filename, "r");
	char word[WORD_MAX], mean[MEAN_MAX];

    soundexTree = btcrt("../data/soundex.dat", 0, 0);
    while(fscanf(datafile, "%[^@]", word) == 1){
		fgets(mean, MEAN_MAX, datafile);
		char wordTmp[100];
        strcpy(wordTmp, soundex(word));
        strcat(wordTmp, word);
        binsky(soundexTree, wordTmp, 0);
	}
	fclose(datafile);
}

void initDic(char *filename){
    FILE *datafile;
    dictionary = btcrt("../data/evdic.dat", 0, 0);
	datafile = fopen(filename, "r");

    char word[WORD_MAX], mean[MEAN_MAX];

    while(fscanf(datafile, "%[^@]", word) == 1){
        fgets(mean, MEAN_MAX, datafile);
        separate_mean(mean);
        btins(dictionary, word, mean, strlen(mean) + 1);
    }
    fclose(datafile);
}

void separate_mean(char* mean){
    int i = 0, j = 1;
    while (mean[j] != '\0'){
        if (mean[j] == '\\' && mean[j + 1] == 'n'){
            mean[i++] = '\n';
            j += 2;
        }
        else{
            if(i != j)
                mean[i++] = mean[j++];
            else{
                i++; j++;
            }
	    }
	}
	mean[i] = '\0';
}