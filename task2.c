#include "citire.h"
/*avem o functie de comparare intre  baze de date in functie de titlu, paragraf sau nr de accesari.
se vor compara astfel: daca au acelasi titlu se compara in functie de nr de accesari , iar daca sunt crescatoare returneaza 1, altfel 0;
daca titlurile sunt diferite se compara in functie dev ce e in continut, adica paragrafele, iar daca sunt crescatoare (adica primul caracter din 
paragraf e mai mic din pdv alfabetic returneaza 0), altfel 1. daca primul caracter la ambele sunt egale se compara restul pana se gaseste o diferenta
*/
int comparare1(char titlu1[], char titlu2[], char paragraf1[], char paragraf2[], int nr_accesari1, int nr_accesari2)
{
    if (strcmp(titlu1,titlu2) == 0)
    {
        if (nr_accesari1 < nr_accesari2)
            return 1;
        else
            return 0;
    }
    else
    {
        if (strcmp(paragraf1, paragraf2) < 0)
            return 0;
        else
            return 1;
    }
}
/* functia de sortare va avaea ca argument un pointer la  functia comparare1, iar in ea se va face o sortare simpla in functie de functia 
comparator care daca returneaza 1 se va face swap la vectorul care trebuie sortat(vect_sortat).Daca returneaza 0 inseamna ca nu trebuie sortate numerele 
din vect_sortat
*/
void sortare(int vector_siteuri_fr[], int n, int vect_sortat[],
             int (*comparare)(char titlu1[], char titlu2[], char paragraf1[], char paragraf2[], int nr_accesari1, int nr_accesari2))
{
    int i, j, aux;
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (comparare(site[vect_sortat[i]].titlu, site[vect_sortat[j]].titlu, site[vect_sortat[i]].paragraf, site[vect_sortat[j]].paragraf, 
            site[vect_sortat[i]].nr_accesari, site[vect_sortat[j]].nr_accesari) == 1)
            {
                aux = vect_sortat[i];
                vect_sortat[i] = vect_sortat[j];
                vect_sortat[j] = aux;
            }
  
}
int main()
{
    //deschid fisierul care are toate html-urile
    file = fopen("master.txt", "rt");
     //aloc 3 la baza de date(structul este in header si se numeste baza de date)
    site = calloc(3, sizeof(baza_de_date));
    //vine de la sine e nr de siteuri initial 0, citeste o linie din master.txt adauga 1 la contorul nr_siteuri
    //celelalte intializari sunt contori
    int nr_siteuri = 0, i, contor, c;
    int dimensiune;
    //este fun vector de frecventa pt site-uri
    //a se vedea functionalitatea lui mai tarziu
    int vector_siteuri_fr[1000] = {0};
     //a se vedea functionalitatea mai tarziu
    int cate_parag_sun_cu_cuv = 0, vect_sortat[1000];
    //initializarea functiei comparator ca pointer
    int (*comparare[1])(char *, char *, char *, char *, int, int) = {comparare1};
    //un fel de copii pt titlu, nume_site si vector, textul citit  de la tastatura
    char titlu[50], nume_site[30], vector[100], text_citit[1000], paragraf[1000];
    char *cuvant_citit;
    char *cuvant_din_paragraf;
    char *adresa1;
    char *adresa2;
    //se citeste un text de la tastatura
    fgets(text_citit, sizeof(text_citit), stdin);
    while (!feof(file)) //cat timp poti sa citesti din fisierul master.txt tu citesti
    {
        //citesti numlee site ului ca sa poti sa il deschizi
        fscanf(file, "%s", nume_site);
        html_site = fopen(nume_site, "r");
        while (!feof(html_site)) //cat timp poti sa citesti din site-ul html care e din master.txt
        {
            //citesti URL-ull, lungimea in octeti, numarul de accesari si checksum-ul si le bagi in baza de date
            fscanf(html_site, "%s", site[nr_siteuri].URL);
            fscanf(html_site, "%d", &site[nr_siteuri].lung_in_octeti);
            fscanf(html_site, "%d", &site[nr_siteuri].nr_accesari);
            fscanf(html_site, "%d", &site[nr_siteuri].checksum);
            fgetc(html_site);
            dimensiune= site[nr_siteuri].lung_in_octeti + 1;
            site[nr_siteuri].paragraf = calloc(dimensiune, sizeof(char));
            site[nr_siteuri].continut = calloc(dimensiune, sizeof(char));
            while (fgets(vector, sizeof(vector), html_site)) //citesti in vector fiecare linie din fiecare site
            {
                //se concateneaza fiecare linie in baza de date intr-un vector cu tot continutul
                strcat(site[nr_siteuri].continut, vector);
                //pentru a afla titlu comparam primele 7 caractere ale vectorului si 
                //daca sunt egale copiem totul fara primele 7 caractere pana se termina linia
                if (strncmp(vector, "<title>", 7) == 0)
                {
                    strcpy(titlu, vector + 7);
                    i = 0;
                     /*ca sa stergem tagul de terminare a titlului </title> vom parcurge vectorul titlu pe caractere
                    iar cat timp nu ajunge la caracterul '<' se va copia in baza de date */
                    while (titlu[i] != '<')
                    {
                        site[nr_siteuri].titlu[i] = titlu[i];
                        i++;
                    }
                    //terminator de sir la final uwu
                    site[nr_siteuri].titlu[i] = '\0';
                }
            }
            i = 0;
            contor = 0;
            while (i < strlen(site[nr_siteuri].continut)) //se citeste cat timp nu s-a terminat ce e in continut
            {
                //nu cont ce e pana gasesc '<p' dar de aici incepe distractia
                if (site[nr_siteuri].continut[i] == '<' && site[nr_siteuri].continut[i + 1] == 'p')
                {
                    //daca intre tagurile p exista culoarea textului sau bg-ul nu conteaza se trece peste
                    while (site[nr_siteuri].continut[i] != '>')
                        i++;
                    //daca a intrat in while a ajuns la caracterul '>' iar daca nu tot la caracterul acela a ajuns
                    //deci trecem peste el cu i++
                    i++;
                    //aici vom lua caracter cu caracter si vom baga ce e intre tagurile p in paragraf pana se gaseste caracterul '<' so apoi gata
                    while (site[nr_siteuri].continut[i] != '<')
                    {
                        site[nr_siteuri].paragraf[contor] = site[nr_siteuri].continut[i];
                        i++;
                        contor++;
                    }
                    //terminator de sir la final uwu
                    site[nr_siteuri].paragraf[contor] = '\0';
                }
                //pana intra in if mai tre sa treaca prin alte taguri deci i++
                i++;
            }
            //dupa cum ziceam creste nr de siteuri
            nr_siteuri++;
            //se realoca mai multa memorie daca nr_siteuri este divizibil cu 3 si mai mare decat 0 , de fiecare data se realoca cu 3 mai mult
            if (nr_siteuri % 3 == 0 && nr_siteuri > 0)
                site = realloc(site, (3 + nr_siteuri) * sizeof(baza_de_date));
        }
        //se inchide fisierul ca trebe
        fclose(html_site);
    }
    //se inchide si master.txt ca trebe
    fclose(file);
    //facem strtok pt fiecare cuvant din textul citit de la tastatura
    cuvant_citit = strtok_r(text_citit, " \n",&adresa1);
    while (cuvant_citit != NULL)
    {
        //luam fiecare site html 
        for (i = 0; i < nr_siteuri; i++)
        {
            //facem o copie la fiecare paragraf din site.paragraf ca sa nu stricam baza de date
            strcpy(paragraf, site[i].paragraf);
            //facem strtok pt fiecare cuvant din paragraf
            cuvant_din_paragraf = strtok_r(paragraf, " \n",&adresa2);
            //comparam fiecare cuvant din paragraf din toate siteurile cu cuvantul citit iar daca il gasim frecventa acelui  site devine 1
            //se face accest lucru pt fiecare cuvant citit
            while (cuvant_din_paragraf != NULL)
            {
                
                if (strcmp(cuvant_din_paragraf, cuvant_citit) == 0)
                {
                    vector_siteuri_fr[i] = 1;
                }
                cuvant_din_paragraf = strtok_r(NULL, " \n",&adresa2);
            }
        }
        cuvant_citit = strtok_r(NULL, " \n",&adresa1);
    }
    //la final o sa avem un vector cu frecventa siteurilor (adica in ce siteuri am gasit unul sau mai multe cuvinte citite)
    //asadar pt a vedea cate site uri au aceleasi cuvinte care sunt citite de la tastatura vom lua un contor cate_parag_sun_cu_cuv,
    // care va creste de fiecare data cand frecventa vectorului e diferita de 0
    for (i = 0; i < 1000; i++)
        if (vector_siteuri_fr[i] != 0)
            cate_parag_sun_cu_cuv++;
    //acum vom crea un vector care va primi nr siteurilor care au frecventa diferita de 0;
    //de exemplu pt cuvantul bine sunt 3 si 6, iar vectorul vect_sortat va primi acele numere 3 si 6 (indicii siteurilor)
    i = 0;
    for (c = 0; c < 1000; c++)
        if (vector_siteuri_fr[c] != 0)
        {
            vect_sortat[i] = c;
            i++;
        }
    //se apeleaza functia de sortare pentru a vedea ordinea i  care se vor afisa siteurile
    sortare(vector_siteuri_fr, cate_parag_sun_cu_cuv, vect_sortat, comparare[0]);
    //se vor afisa URL-rile site-urilor dupa sortare
    for (i = 0; i < cate_parag_sun_cu_cuv; i++)
        printf("%s\n", site[vect_sortat[i]].URL);
    //se va elibera memoria
    for (i = 0; i < nr_siteuri; i++)
    {
        free(site[i].continut);
        free(site[i].paragraf);
    }
    //se va elibera memoria
    free(site);
    return 0;
}