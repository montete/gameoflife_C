#define _GNU_SOURCE
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include </usr/local/include/png.h>
#include </usr/local/include/libpng15/png.h>
#include "struct.h"
#include "gol.h"
#include "file.h"
#include "topng.h"
char * help = "\n	Gra w życie:\n\
	użycie: ./gameoflife -s [-a liczba generacji] [-f nazwa_pliku liczba_generacji]\n \
	s - nie wypisuj nic na standardowym wyjściu (standardowo: bez s) \n\
	a - generowanie losowej gry w życie (50x50) o podanej liczbie generacji\n\
	f - generowanie gry w życie z podanego pliku, o podanej liczbie generacji\n";

int main(int argc, char *argv[]) {
	world_t gameoflife;
	int c,gen_num = 2, aflag = 0, fflag = 0, sflag =0;
    int i=0; 
	char * avalue = "nothing";
	char * fvalue = "nothing";
	extern char *optarg;
	extern int optind;
	char * tmp;
	char * filepath;
	char * wd = "w";
	char * hg = "h";
	FILE *fp;
	char * file = "life-przyklad";
	if (argc == 1){
		printf(help);
	}
	while ((c = getopt (argc, argv, "a:f:hs")) != -1){
		switch (c)
		{
			case 'a':
				if(aflag == 1){
					printf("aflag set multiple times\n");
					printf(help);
					return 0;
					}
				if(strcmp(optarg, "-a") == 0){
					printf("aflag set multiple times\n");
					printf(help);
					return 0;
				}else if(strcmp(optarg, "-f") == 0){
					fflag++;
					
				}else{
					avalue = strdup(optarg);
				}
				aflag++;
				break;
			case 'f':
				if(fflag == 1){
					printf("fflag set multiple times\n");
					printf(help);
					return 0;
					}
				if(strcmp(optarg, "-f") == 0){
					printf("fflag set multiple times\n");
					printf(help);
					return 0;
				}else if(strcmp(optarg, "-a") == 0){
					aflag++;
					
				}else{
					fvalue = strdup(optarg);
				}
				fflag++;
				break;
			case 's':
				if(sflag == 1){
					printf("sflag set multiple times\n");
					printf(help);
					return 0;
				}
				sflag++;
				break;
			case 'h':
				printf(help);
				printf("help");
				return 0;
				break;
			return 1;
			default:
				printf(help);
				printf("default\n");
				return 0;
				break;
	}
}
		
		
		if((sflag==1) && (aflag ==0) && (fflag ==0)){
			printf("	not a single important flag set");
			printf(help);
			return 0;
		}
		if((aflag == 1) && (fflag ==1)){
			printf("	two flags at once\n");
			printf(help);
			return 0;
		}
		if((aflag ==1) && ((optind) < argc)){
			printf("	-a needs only 1 argument");
			printf(help);
			return 0;
			}
		if((fflag ==1) && ((optind+1) < argc)){
			printf("	-f needs only 2 argument");
			printf(help);
			return 0;
			}
		if(aflag ==1){
			if(atoi(avalue) == 0){
					printf("zła ilość ewolucji");
					return 0;
				}else{
					gen_num = atoi(avalue);
				}
				if(createworld(&gameoflife, 50, 50)) {
					randomizeworld(&gameoflife);
				do {
					asprintf(&tmp, "Generacja-%i", i+1); 
					asprintf(&filepath, "src/random-%i.png", i+1);
					createScaledImage(&gameoflife, filepath, 20);
					if(sflag != 1){
						printf(tmp);
						printf("\n");
						printworld(&gameoflife, stdout);
						printf("\n");
					}
					free(tmp);
					free(filepath);
					fflush(stdin);
					updateworld(&gameoflife);
					i++;					
				}while(i != gen_num);
					asprintf(&tmp, "Generacja %i", i+1);
					writeGame(&gameoflife, tmp);
					destroyworld(&gameoflife);
					free(tmp);
				} 
		}
		if(fflag ==1){
				if (argc == 3){
					printf("brak pliku docelowego");
					return 0;
				}else{
				fp = fopen(fvalue, "r");
						if (fp == NULL){
						printf("brak pliku docelowego");
						return 0;
						}
				fclose(fp);		
				file = fvalue;
				}
				if(atoi(argv[optind]) <= 0){
					printf("zła ilość ewolucji");
					return 0;
				}else{
					gen_num = atoi(argv[optind]);
				}
				int w = getWymiar(fvalue, wd);
				int h = getWymiar(fvalue, hg);
				if(createworld(&gameoflife, w, h)) {
					if(definedworld(file, &gameoflife) ==1){
						return 0;
					}
				do {
					asprintf(&tmp, "Generacja %i", i+1); 
					asprintf(&filepath, "src/%i.png", i+1);
					createScaledImage(&gameoflife, filepath, 20);
					if(sflag!=1){
						printf(tmp);
						printf("\n");
						printworld(&gameoflife, stdout); 
						printf("\n");
					}
					free(filepath);
					free(tmp);
					fflush(stdin);
					updateworld(&gameoflife);
					i++;					
				}while(i != gen_num);
					asprintf(&tmp, "Generacja %i", i+1); 
					writeGame(&gameoflife, tmp);
					destroyworld(&gameoflife); 
					free(tmp);		
				}
		}
	return 0;	
}
