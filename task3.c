#include "citire.h"
/*functia de comparare2 va compara nr de acesari a 2 site uri iar daca sunt in ordine crescatoare se va returna 1, altfel 0
*/
int comparare2(int nr_accesari1, int nr_accesari2)
{

    if (nr_accesari1 < nr_accesari2)
        return 1;
    else
        return 0;
}
/* functia de sortare va avaea ca argument un pointer la  functia comparare1, iar in ea se va face o sortare simpla in functie de functia 
comparator care daca returneaza 1 se va face swap la vectorul care trebuie sortat(vect_sortat).Daca returneaza 0 inseamna ca nu trebuie sortate numerele 
din vect_sortat
*/
void sortare(int vector_siteuri_fr[], int n, int vect_sortat[],
             int (*comparare)(int nr_accesari1, int nr_accesari2))
{
    int i, j, aux;
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (comparare(site[vect_sortat[i]].nr_accesari, site[vect_sortat[j]].nr_accesari) == 1)
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
    int (*comparare[1])(int, int) = {comparare2};
    //un fel de copii pt titlu, nume_site si vector, textul citit  de la tastatura
    char titlu[50], nume_site[30], vector[100], text_citit[1000], paragraf[1000];
    char *cuvant_citit;
    char *cuvant_din_paragraf;
    char *adresa1;
    char *adresa2;
    char copie_ghilimele[100] = {0};
    char copie_citire[100] = {0};
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
            dimensiune = site[nr_siteuri].lung_in_octeti + 1;
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
    //se inchide fisierul ca trebe
    fclose(file);
    //un contor ok care daca gaseste un cuvant din textul citit cu ghilimele ca primul sau ult caracter creste
    int ok = 0;
    //facem strtok pt fiecare cuvant din textul citit de la tastatura
    cuvant_citit = strtok_r(text_citit, " \n", &adresa1);
    while (cuvant_citit != NULL)
    {
        //facem o copie la tot textul citit
        strcat(copie_citire, cuvant_citit);
        strcat(copie_citire, " ");
        if (cuvant_citit[0] == '"' || cuvant_citit[strlen(cuvant_citit) - 1] == '"')
        {
            ok++;
        }

        //luam fiecare site html
        for (i = 0; i < nr_siteuri; i++)
        {
            //facem o copie la fiecare paragraf din site.paragraf ca sa nu stricam baza de date
            strcpy(paragraf, site[i].paragraf);
            //facem strtok pt fiecare cuvant din paragraf
            cuvant_din_paragraf = strtok_r(paragraf, " \n", &adresa2);
            while (cuvant_din_paragraf != NULL)
            {
                //comparam fiecare cuvant din paragraf din toate siteurile cu cuvantul citit iar daca il gasim frecventa acelui  site devine 1
                //acest lucru numai daca cuvantul nu este intre paranteze, cu alte cuvinteb  contorul ok nu este egal cu 1
                //se face accest lucru pt fiecare cuvant citit
                if (strcmp(cuvant_din_paragraf, cuvant_citit) == 0 && ok != 1)
                {
                    vector_siteuri_fr[i] = 1;
                }
                char copie[100];
                //daca exista un cuvamt cu minus in fata nu mai trebuie sa luam site-ul daca gasim acel cuvant im site
                if (cuvant_citit[0] == '-')
                {
                    //copiem cuvamtul fara - intr-o copie
                    strcpy(copie, cuvant_citit + 1);
                    //daca il gasim in paragraf atunci frecventa devine -1
                    if (strcmp(cuvant_din_paragraf, copie) == 0)
                        vector_siteuri_fr[i] = -1;
                }
                cuvant_din_paragraf = strtok_r(NULL, " \n", &adresa2);
            }
        }
        cuvant_citit = strtok_r(NULL, " \n", &adresa1);
    }
    //parcurgem textul citit de la tastatura la care am facut o copie in copie_citire
    contor = 0;
    for (i = 0; i < strlen(copie_citire); i++)
    {
        //daca gasim ghilimele atunci vom lua cuvantul sau cuvintele din ghilimele si le vom pune caracter cu caracter in copie_ghilimele
        if (copie_citire[i] == '"')
        {
            i++;
            while (copie_citire[i] != '"')
            {
                copie_ghilimele[contor] = copie_citire[i];
                i++;
                contor++;
            }
            //la final terminator de sir uwu
            copie_ghilimele[contor] = '\0';
        }
    }
    //acum daca exita copie_ghilimele ,iar frecventa vectorului pt fiecare site este diferita de -1,
    //adica nu a fost gasit un cuvant cu - in fata , moment in care site ul trebuie evitat
    //atunci se va compara ce exista in paragraful site ului si ce e in copie_ghilimele iar daca e dif de null frecventa va deveni 1
    for (i = 0; i < nr_siteuri; i++)
        if (copie_ghilimele[0] != '\0' && vector_siteuri_fr[i] != -1 && strstr(site[i].paragraf, copie_ghilimele) != NULL)
        {
            vector_siteuri_fr[i] = 1;
        }
    //la final o sa avem un vector cu frecventa siteurilor (adica in ce siteuri am gasit unul sau mai multe cuvinte citite)
    //asadar pt a vedea cate site uri au aceleasi cuvinte care sunt citite de la tastatura vom lua un contor cate_parag_sun_cu_cuv,
    // care va creste de fiecare data cand frecventa vectorului e diferita de 0
    for (i = 0; i < 1000; i++)
    {
        if (vector_siteuri_fr[i] > 0)
            cate_parag_sun_cu_cuv++;
    }
    i = 0;
    //acum vom crea un vector care va primi nr siteurilor care au frecventa diferita de 0;
    //de exemplu pt cuvantul bine sunt 3 si 6, iar vectorul vect_sortat va primi acele numere 3 si 6 (indicii siteurilor)
    for (c = 0; c < 1000; c++)
        if (vector_siteuri_fr[c] > 0)
        {
            vect_sortat[i] = c;
            i++;
        }
    //se apeleaza functia de sortare pentru a vedea ordinea i  care se vor afisa siteurile
    sortare(vector_siteuri_fr, cate_parag_sun_cu_cuv, vect_sortat, comparare[0]);
    for (i = 0; i < cate_parag_sun_cu_cuv; i++)
        printf("%s\n", site[vect_sortat[i]].URL);
    //se vor afisa URL-rile site-urilor dupa sortare
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