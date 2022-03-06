#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
typedef struct {
    char URL[50];
    int lung_in_octeti;
    int nr_accesari;
    int checksum;
    char titlu[50];
    char *paragraf;
    char *continut;
}baza_de_date;
baza_de_date *site;
enum colours{white, black, red, green, blue, yellow};
FILE *file;
FILE *html_site;