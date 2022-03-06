#include "citire.h"
//functia roteste bitii spre dreapta de k ori
int rotr(char x, int k)
{
    int copie;
    //copia este conversia in int a lui x
    copie = (int)x;
    int i = 7, j, l, m;
    //s este unde vor fi stocati bitii dupa ce schimbam din baza 10 in baza 2
    char s[8];
    char aux;
    /*transforma un numar in baza 10 intr un numar in baza 2.Prima data initializeaza sirul s cu caracterul 0 pe toate cele 8 pozitii.
Transforma numarul n impartindu-l la 2 si punand retul in sirul s, in acelasi timp convertind acel numar in caracter.
Resturile lui n la impartirea cu 2 vor fi puse in ordine inversa pentru a crea binarul numarului.*/
    for (j = 0; j < 8; j++)
        s[j] = '0';

    while (copie != 0)
    {
        s[i] = (char)(copie % 2 + '0');
        i--;
        copie = copie / 2;
    }
    s[8] = '\0';
    //este aceeasi chestia daca fac restul lui k sau nu dar are eficenta mai mare asa , in loc sa faca de 50 de ori face de 2 ori
    k = k % 8;
    //muta ciclic de k ori bitii spre dreapta
    for (l = 0; l < k; l++)
    {
        aux = s[7];
        for (m = 6; m >= 0; m--)
            s[m + 1] = s[m];
        s[0] = aux;
    }
    /*transforma un numar in baza 2 intr un numar in baza 10.In acest fel, ia un numar,initial 0, si trece prin sir prin
intermediul contorului i converteste caracterul de pe poz i int int,il inmultesti cu 2 la puterea 7-i si aduni la numarul curent.
*/
    int number = 0;
    for (i = 7; i >= 0; i--)
    {
        number = ((int)(s[i]) - '0') * pow(2, 7 - i) + number;
    }
    return number;
}

//functia roteste bitii spre stanga de k ori
int rotl(char x, int k)
{
    int copie;
    //copia este conversia in int a lui x
    copie = (int)x;
    int i = 7, j, l, m;
    //s este unde vor fi stocati bitii dupa ce schimbam din baza 10 in baza 2
    char s[8];
    char aux;
    /*transforma un numar in baza 10 intr un numar in baza 2.Prima data initializeaza sirul s cu caracterul 0 pe toate cele 8 pozitii.
Transforma numarul n impartindu-l la 2 si punand retul in sirul s, in acelasi timp convertind acel numar in caracter.
Resturile lui n la impartirea cu 2 vor fi puse in ordine inversa pentru a crea binarul numarului.*/
    for (j = 0; j < 8; j++)
        s[j] = '0';
    while (copie != 0)
    {
        s[i] = (char)(copie % 2 + '0');
        i--;
        copie = copie / 2;
    }
    s[8] = '\0';
    //este aceeasi chestia daca fac restul lui k sau nu dar are eficenta mai mare asa , in loc sa faca de 50 de ori face de 2 ori
    k = k % 8;
    //muta ciclic de k ori bitii spre stanga
    for (l = 0; l < k; l++)
    {
        aux = s[0];
        for (m = 1; m < 8; m++)
            s[m - 1] = s[m];
        s[7] = aux;
    }
    /*transforma un numar in baza 2 intr un numar in baza 10.In acest fel, ia un numar,initial 0, si trece prin sir prin
intermediul contorului i converteste caracterul de pe poz i int int,il inmultesti cu 2 la puterea 7-i si aduni la numarul curent.
*/
    int number = 0;
    for (i = 7; i >= 0; i--)
    {
        number = ((int)(s[i]) - '0') * pow(2, 7 - i) + number;
    }
    return number;
}
int main()
{
    //deschid fisierul care are toate html-urile
    file = fopen("master.txt", "rt");
    //aloc 3 la baza de date(structul este in header si se numeste baza de date)
    site = calloc(3, sizeof(baza_de_date));
    //vine de la sine e nr de siteuri initial 0, citeste o linie din master.txt adauga 1 la contorul nr_siteuri
    //celelalte intializari sunt contori
    int nr_siteuri = 0, i, contor, j;
    int dimensiune;
    //un fel de copii pt titlu, nume_site si vector
    char titlu[50], nume_site[30], vector[100];
    char citire_URL[50];
    int cheie_gasita;
    int contor_daca_exista_site;
    ///este aceeasi functie de citire ca la taskul 2 si 3
    //vexi explicatia la task-ul 2 si 3
    while (!feof(file))
    {
        fscanf(file, "%s", nume_site);
        html_site = fopen(nume_site, "r");
        while (!feof(html_site))
        {
            fscanf(html_site, "%s", site[nr_siteuri].URL);
            fscanf(html_site, "%d", &site[nr_siteuri].lung_in_octeti);
            fscanf(html_site, "%d", &site[nr_siteuri].nr_accesari);
            fscanf(html_site, "%d", &site[nr_siteuri].checksum);
            fgetc(html_site);
            dimensiune = site[nr_siteuri].lung_in_octeti + 1;
            site[nr_siteuri].paragraf = calloc(dimensiune, sizeof(char));
            site[nr_siteuri].continut = calloc(dimensiune, sizeof(char));

            while (fgets(vector, sizeof(vector), html_site))
            {
                strcat(site[nr_siteuri].continut, vector);
                if (strncmp(vector, "<title>", 7) == 0)
                {
                    strcpy(titlu, vector + 7);
                    i = 0;
                    while (titlu[i] != '<')
                    {
                        site[nr_siteuri].titlu[i] = titlu[i];
                        i++;
                    }
                    site[nr_siteuri].titlu[i] = '\0';
                }
            }
            i = 0;
            contor = 0;
            while (i < strlen(site[nr_siteuri].continut))
            {
                if (site[nr_siteuri].continut[i] == '<' && site[nr_siteuri].continut[i + 1] == 'p')
                {
                    while (site[nr_siteuri].continut[i] != '>')
                        i++;
                    i++;
                    while (site[nr_siteuri].continut[i] != '<')
                    {
                        site[nr_siteuri].paragraf[contor] = site[nr_siteuri].continut[i];
                        i++;
                        contor++;
                    }
                    site[nr_siteuri].paragraf[contor] = '\0';
                }
                i++;
            }
            nr_siteuri++;
            if (nr_siteuri % 3 == 0 && nr_siteuri > 0)
                site = realloc(site, (3 + nr_siteuri) * sizeof(baza_de_date));
        }
        fclose(html_site);
    }
    fclose(file);
    //se citeste de la tastatura cate url-uri exista
    while (fgets(citire_URL, sizeof(citire_URL), stdin))
    {
        citire_URL[strlen(citire_URL) - 1] = '\0';
        contor_daca_exista_site = 0;
        cheie_gasita = 0;
        for (i = 0; i < nr_siteuri; i++)
        {
            if (strcmp(site[i].URL, citire_URL) == 0) //comparam pt fiecare site daca are url ul acelasi ca la cel citit
            {
                //il are deci acest contor devine 1
                contor_daca_exista_site = 1;
                for (j = 0; j < strlen(site[i].continut); j++) //luam fiecare caracter din continutul site-ului cu url-ul egal cu cel citit
                {
                    if (j % 2 == 0) //iar daca caracterul este pe pozitie para va actiona functia rotl
                        cheie_gasita = cheie_gasita ^ rotl(site[i].continut[j], j);
                    else //altfel a va actiona functia rotr
                        cheie_gasita = cheie_gasita ^ rotr(site[i].continut[j], j);
                }
                if (cheie_gasita == site[i].checksum) //daca checksum ul site-ului este egal cu cheia gasita se va afisa acest mesaj
                    printf("Website safe!\n");
                else
                    printf("Malicious website! Official key: %d. Found key: %d\n", site[i].checksum, cheie_gasita); //altfel asa
            }
        }
        if (contor_daca_exista_site == 0) //daca nu il are se va afisa acest mesaj
            printf("Website not found!\n");
    }
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