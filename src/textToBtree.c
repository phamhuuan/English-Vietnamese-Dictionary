#define WORD_MAX 255
#define MEAN_MAX 10000

void separate_mean(char* mean);
int convert_text_to_bt(char * filename);

int convert_text_to_bt(char *filename){
    FILE * datafile;
    BTA *convertfile;
    convertfile = btcrt("../data/evdic.dat", 0, 0);
	datafile = fopen(filename, "r");

    char word[WORD_MAX], mean[MEAN_MAX];
    int line;

    while (fscanf(datafile, "%[^@]", word) == 1){
        fgets(mean, MEAN_MAX, datafile);
        line++;
        separate_mean(mean);
        btins(convertfile, word, mean, strlen(mean) + 1);    
    }
    btcls(convertfile);
    fclose(datafile);
    return 1;
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