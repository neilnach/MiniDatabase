#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miniDB.h"

int main(int argc, char * argv[]) {
	createMovieArray();
	database = argv[1];
	commands = argv[2];
	outputFile = argv[3];
	readFile(argv[1]);
	FILE * f;
	f = fopen(commands, "r");
	if (f == NULL) {
		printf("Cannot open file...");
		return 1;
	}
	char str[512];
	while (fgets(str, sizeof(str), f)) { //checks every line of file
		char * commandArr[5];
		char * token;
		token = strtok(str, ",");
		int j = 0;
		while (token != NULL) {
			commandArr[j] = strdup(trim(token));
			//printf("%s" , token);
			token = strtok(NULL, ",");
			j++;
		}

		if (strcmp(commandArr[0], "ADD") == 0) {
			addData(commandArr[1], commandArr[2], commandArr[3], commandArr[4]);
		}
		else if (strcmp(commandArr[0], "EDIT") == 0) {
			editData(commandArr[1], commandArr[2], commandArr[3]);
		}
		else if (strcmp(commandArr[0], "REMOVE") == 0) {
			removeData(commandArr[1]);
		}
		else if (strcmp(commandArr[0], "LOOKUP") == 0) {
			lookup(commandArr[1], commandArr[2]);
			FILE * fp = fopen(outputFile, "a");
			fprintf(fp, "%s, %s, %s\n", commandArr[0], commandArr[1], commandArr[2]);
			int i;
			fclose(fp);
			FILE  * newF = fopen(outputFile, "a");
			for (i = 0; i < tempMovieCount; i++) {
				fprintf(newF, "%s, %s, %s, %s\n", tempMovies[i]-> title, tempMovies[i] -> date, tempMovies[i] -> director, tempMovies[i] -> ID);
				free(tempMovies[i]);
			}
			free(tempMovies);
			fclose(newF);
		}
	
		else if (strcmp(commandArr[0], "DISPLAY") == 0) {
			display(strdup(commandArr[1]), strdup(commandArr[2]), strdup(commandArr[3]));							
		}
	}
	fclose(f);
	return 1;
}	
