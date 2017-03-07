#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "miniDB.h"

void createMovieArray() {
	numMovies = 0;
	maxMovies = 100;
	movies = malloc(sizeof(movie_des) * maxMovies);
}

char *trim(char *str) {
	char *end;
	while(isspace((unsigned char)*str)) str++;
	if(*str == 0)  
		return str;
		end = str + strlen(str) - 1;
	      	while(end > str && isspace((unsigned char)*end)) end--;
		*(end+1) = 0;
		return str;
}

/*int isValidDate(char * date) {
	char * newDate = strdup(date);
	char * dateArr[3];
	int i;
	char * token;
	token = strtok(newDate, "/");
	while (token != NULL) {
		dateArr[i] = token;
		token = strtok(NULL, ",");
		i++;
	}
	int month = atoi(dateArr[0]);
	int days = atoi(dateArr[1]);
	
	if (month < 1 || month > 12) {
		printf("Invalid\n");
		return 0;
	}
	if (month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
		if (days > 31 || days < 1) {
			printf("Invalid\n");
			return 0;
		}
	}
	if (month == 2 || month == 4 || month == 6 || month == 9 || month == 11 || month == 1) {
		if (days > 30 || days < 1) {
			printf("Invalid\n");
			return 0;
		}
	}
	printf("Good to go\n");
	return 1;
}	
*/
void readFile(char * filename) {	
	FILE * file;
	file = fopen(filename, "r");
	if (file == NULL) {
		return;
	}
	char str[512];
	while (fgets(str, sizeof(str), file)) { //checks every line of file
		movies[numMovies] =(movie_des *) malloc(sizeof(movie_des));
		char * movieArr[4];
		char * token;
		token = strtok(str, ",");
		int j = 0;
		while (token != NULL) {
			movieArr[j] = trim(token);
			//printf("%s" , token);
			token = strtok(NULL, ",");
			j++;
		}
		movies[numMovies] -> title = strdup(movieArr[0]);
		movies[numMovies] -> date = strdup(movieArr[1]);
		movies[numMovies] -> director = strdup(movieArr[2]);
		//int x = strlen(movieArr[3]);
		//movieArr[3][x-1] = '\0';
		movies[numMovies] -> ID = strdup(movieArr[3]);
		//movies[numMovies] = newMovie;
		numMovies++;
	}
	fclose(file);
}

void addData(char *title, char *date, char *director, char * ID) {
	int i = 0;
	FILE * file = fopen(database, "w+");
	for (i = 0; i < numMovies; i++) {
		if (strcmp(movies[i] -> ID, ID) == 0) {
			return;
		}
	}
	movie_des * newMovie = malloc(sizeof(movie_des));
	newMovie -> title = title;
	newMovie -> date = date;
	newMovie -> director = director;
	newMovie -> ID = ID;
	movies[numMovies] = newMovie;
	numMovies++;
	int j = 0;
	for (j = 0; j < numMovies; j++) {
		fprintf(file, "%s, %s, %s, %s\n", movies[j] -> title, movies[j] -> date, movies[j] -> director, movies[j] -> ID);
	}	
	fclose(file);
}

void editData(char * ID, char * feature, char * data) {
	FILE * file = fopen(database, "w+");
	int i;
	for (i = 0; i < numMovies; i++) {
		if (strcmp(movies[i] -> ID, ID) == 0) {
			if (strcmp(feature, "DIRECTOR") == 0) {
				movies[i] -> director = data;
			}
			if (strcmp(feature, "DATE") == 0) {
				movies[i] -> date = data;
			}
			if (strcmp(feature, "TITLE") == 0) {
				movies[i] -> title = data;
			}	
		}
	}
	int j = 0;
	for (j = 0; j < numMovies; j++) {
		fprintf(file, "%s, %s, %s, %s\n", movies[j] -> title, movies[j] -> date, movies[j] -> director, movies[j] -> ID);
	}	
	fclose(file);
}
		
void removeData(char * ID) {
	FILE * file = fopen(database, "w+");
	int i;
	for (i = 0; i < numMovies; i++) {
		if (strcmp(movies[i] -> ID, ID) == 0) {
			int j;
			free(movies[i]);
			for (j = i; j < numMovies - 1; j++) {
				movies[j] = movies[j + 1];
			}
			movies[numMovies - 1] = NULL;
			numMovies--;
		}
	}	
	int j = 0;
	for (j = 0; j < numMovies; j++) {
		fprintf(file, "%s, %s, %s, %s\n", movies[j] -> title, movies[j] -> date, movies[j] -> director, movies[j] -> ID);
	}	
	fclose(file);
}	
	
void lookup(char * feature, char * data) {
	int i;
	tempMovieCount = 0;
	tempMovies = malloc(sizeof(movie_des) * 100);

	if (strcmp(feature, "DIRECTOR") == 0) {
		for (i = 0; i < numMovies; i++) {
			if (strcmp(movies[i] -> director, data) == 0) {
				movie_des * newMov = malloc(sizeof(movie_des));
				newMov -> director = strdup(movies[i] -> director);
				newMov -> title = strdup(movies[i] -> title);
				newMov -> date = strdup(movies[i] -> date);
				newMov -> ID = strdup(movies[i] -> ID);
				tempMovies[tempMovieCount] = newMov;
				tempMovieCount++;
			}
		}
	}

	else if (strcmp(feature, "TITLE") == 0) {
		for (i = 0; i < numMovies; i++) {
			if (strcmp(movies[i] -> title, data) == 0) {
				movie_des * newMov = malloc(sizeof(movie_des));
				newMov -> director = strdup(movies[i] -> director);
				newMov -> title = strdup(movies[i] -> title);
				newMov -> date = strdup(movies[i] -> date);
				newMov -> ID = strdup(movies[i] -> ID);	
				tempMovies[tempMovieCount] = newMov;
				tempMovieCount++;
			}
		}
	}

	else if (strcmp(feature, "ID") == 0) {
		for (i = 0; i < numMovies; i++) {
			if (strcmp(movies[i] -> ID, data) == 0) {
				movie_des * newMov = malloc(sizeof(movie_des));
				newMov -> director = strdup(movies[i] -> director);
				newMov -> title = strdup(movies[i] -> title);
				newMov -> date = strdup(movies[i] -> date);
				newMov -> ID = strdup(movies[i] -> ID);
				tempMovies[tempMovieCount] = newMov;
				tempMovieCount++;
			}
		}
	}

	else if (strcmp(feature, "DATE") == 0) {
		for (i = 0; i < numMovies; i++) {
			if (strcmp(movies[i] -> date, data) == 0) {
				movie_des * newMov = malloc(sizeof(movie_des));
				newMov -> director = strdup(movies[i] -> director);
				newMov -> title = strdup(movies[i] -> title);
				newMov -> date = strdup(movies[i] -> date);
				newMov -> ID = strdup(movies[i] -> ID);
				tempMovies[tempMovieCount] = newMov;
				tempMovieCount++;
			}
		}
	}
}

void display(char * feature, char * flag, char * max) {
		
}


/*int main() {
	isValidDate("10/02/1997");
	return 1;
}
*/
/*int main() {
	createMovieArray();
	readFile("test.csv");
	lookup("DIRECTOR", "George Lucas");
	FILE * fp = fopen("outputFile.csv", "a");
	int i;
	for (i = 0; i < tempMovieCount; i++) {
		fprintf(fp, "%s, %s, %s, %s\n", tempMovies[i]-> title, tempMovies[i] -> date, tempMovies[i] -> director, tempMovies[i] -> ID);	
	}
	fprintf(fp, "FUCK YOU");
	fclose(fp);
	return 1;
}*/	
						
/*int main(int argc, char * argv[]) {
	createMovieArray();
	readFile(argv[1]);
	FILE * f;
	f = fopen(argv[2], "r");
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
			FILE * fp = fopen(argv[3], "a");
			fprintf(fp, "%s, %s, %s\n", commandArr[0], commandArr[1], commandArr[2]);
			int i;
			fclose(fp);
			FILE  * newF = fopen(argv[3], "a");
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
}*/



