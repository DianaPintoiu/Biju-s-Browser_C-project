#include "citire.h"
int main()
{
    //deschid fisierul care are toate html-urile
    file = fopen("master.txt", "rt");
    //aloc 3 la baza de date(structul este in header si se numeste baza de date)
    site = calloc(3, sizeof(baza_de_date));
    //vine de la sine e nr de siteuri initial 0, citeste o linie din master.txt adauga 1 la contorul nr_siteuri
    int nr_siteuri = 0;
    //un fel de copii pt titlu, nume_site si vector
    char titlu[50], nume_site[30], vector[100];
    while (!feof(file)) //cat timp poti sa citesti din fisierul master.txt tu citesti
    {
        //citesti numlee site ului ca sa poti sa il deschizi
        fscanf(file, "%s", nume_site); 
        html_site = fopen(nume_site, "r");
        while (!feof(html_site))
        {
            //cat timp poti sa citesti din site-ul html care e din master.txt
            //citesti URL-ull, lungimea in octeti, numarul de accesari si checksum-ul si le bagi in baza de date
            fscanf(html_site, "%s", site[nr_siteuri].URL);
            fscanf(html_site, "%d", &site[nr_siteuri].lung_in_octeti);
            fscanf(html_site, "%d", &site[nr_siteuri].nr_accesari);
            fscanf(html_site, "%d", &site[nr_siteuri].checksum);
            //afisezi doar URL-ul si nr de accesari cu spatii intre ele pt task ul 1
            printf("%s %d ", site[nr_siteuri].URL, site[nr_siteuri].nr_accesari);
            while (fgets(vector, sizeof(vector), html_site))  //citesti in vector fiecare linie din fiecare site
            {
                //pentru a afla titlu comparam primele 7 caractere ale vectorului si 
                //daca sunt egale copiem totul fara primele 7 caractere pana se termina linia
                if (strncmp(vector, "<title>", 7) == 0)
                {
                    strcpy(titlu, vector + 7);
                    int i = 0;
                    /*ca sa stergem tagul de terminare a titlului </title> vom parcurge vectorul titlu pe caractere
                    iar cat timp nu ajunge la caracterul '<' se va copia in baza de date */
                    while (titlu[i] != '<')
                    {
                        site[nr_siteuri].titlu[i] = titlu[i];
                        i++;
                    }
                    //terminator de sir la final uwu
                    site[nr_siteuri].titlu[i] = '\0';
                    //se va afisa si titlul deoarece asa cere cerinta iar apoin newline pt ca acest lucru se va intampla pt toate site-urile html
                    printf("%s\n", site[nr_siteuri].titlu);
                }
                
            }
           //dupa cum ziceam creste nr de siteuri
                nr_siteuri++;
                //se realoca mai multa memorie daca nr_siteuri este divizibil cu 3 si mai mare decat 0 , de fiecare data se realoca cu 3 mai mult
                if (nr_siteuri % 3 == 0 && nr_siteuri > 0)
                    site = realloc(site, (3 + nr_siteuri) * sizeof(baza_de_date));
        }
            fclose(html_site); 
        }
        fclose(file);
        //se elibereaza memoria
        free(site);
        return 0;
    }