#include <stdio.h>
typedef struct movie_des {
	char * title;
	char * date;
	char * director;
	char * ID;
} movie_des;


movie_des ** movies; //array of all movies 
int numMovies; //number of movies in the array
int maxMovies; //the max number of movies the array can store

char * database;
char * commands;
char * outputFile;

char *trim(char *str);
	
movie_des ** tempMovies;
int tempMovieCount;

void createMovieArray(); //initializes array and global variables
void readFile(char * fileName); //reads file and stores everything in array of movies
void addData(char *title, char *date, char *director, char * ID); 
void editData(char * ID, char *feature, char * data);
void removeData(char * ID);
void lookup(char *feature, char *data);
void display(char *feature, char * flag, char * max);
