#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include </usr/local/include/png.h>
#include </usr/local/include/libpng15/png.h>
#include "file.h"



/*IO file reading */

int getWymiar (char * plik, char * tryb){
	int read, wymiar;
	int len=0;
	char *test1;
	char *test2;
	char *test3;
	char * line = NULL;
	FILE * fp;
	fp = fopen(plik, "r");
	if (fp == NULL)
		return 0;
	read = getline(&line, (size_t *)&len, fp);
	test1 = strtok(line, " ");
	test2 = strtok(NULL, " ");
	test3 = strtok(NULL, " ");
	if(strncmp(tryb, "w", 1) == 0){
		wymiar =  atoi(test3);
		}
	else if(strncmp(tryb, "h", 1) == 0){
		wymiar = atoi(test2);
		}
	else{
		printf("zly tryb");
		exit(0);
		}
	free(line);
	fclose(fp);
	return wymiar;
}
int definedworld(char * plik, world_t *world){
	int read,i=0;
	int len=0;
	char *test1;
	char *test2;
	char *test3;
	char * line = NULL;
	FILE * fp;
	fp = fopen(plik, "r");
	if (fp == NULL)
		return 0;
	while ((read = getline(&line, (size_t *)&len, fp)) != -1) {

		test1 = strtok(line, " ");
		test2 = strtok(NULL, " ");
		test3 = strtok(NULL, " ");
		if(i == 0){
			if(!strcmp(test1, "Wymiary") == 0){
			printf("zly plik wsadowy if");
			return 0;	
			
			}else{
			}
		
		}else{

			if(!strcmp(test1, "life") == 0){
				printf("zly plik wsadowy else \n");
				return 1;	
			}else{
			if( (atoi(test2) > world->height) || (atoi(test3) > world->width) ){
				printf("Wymiary tablicy w pliku nie zgodne z wymiarami");
				return 1;
				}else{
				if((atoi(test2)<0) || atoi(test3)<0){
				printf("wymiary mniejsze od 0");
				
				}else{
				(world->array[atoi(test2)][atoi(test3)]).on = 1;
				}
				}
			}
		}	
		i++;
		test1 = NULL;
		test2 = NULL;
		test3 = NULL;

	}

	       free(line);

	return 0;
}

int writeGame(world_t * world, char * filename){
	int i=0,j=0;
	FILE * fp = fopen(filename, "w");
	if (fp == NULL){
		printf("plik nie otwarty pomyslnie");
		return 1;
		}
	char *temp;
	asprintf(&temp, "Wymiary %i %i\n", (world->height), (world->width));
	fputs(temp, fp);
	free(temp);
	for(i = 0; i< (world->height); i++){
		for(j = 0; j<(world->width); j++){
			if(world->array[i][j].on == 1){
				asprintf(&temp, "life %i %i\n", i, j);
				fputs(temp, fp);
				free(temp);
				}
				
		}
	}
	
	fclose(fp);
	return 0;
	}
