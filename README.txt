Pe checkerul local am punctaj maxim
https://imgur.com/cS7xiq1
TASK 1:
durata: peste 7 ore ca am vrut sa fac toata citirea(plus ce era intre p-uri)

implementare: Pentru task-ul 1 am realizat citire din fisierul master.txt, iar apoi citirea din fieacre fisier html care avea titlu scris
pe fiecare linie a fisierului master.txt. Dupa ce se deschide fiecare fisier html se va citi de pe prima linie url-ul,lungimea in octeti, 
numarul de accesari si checksum-ul si se va baga in baza de  date a al catelea site este citit 
(acest lucru se prezinta prin contorul nr_siteuri),(site[nr_siteuri]) si se va afisa URL-ul si nr dev accesari.
Pentru ca nu trebuie sa citim decat titlul pentru a-l afisa,
vom citi fiecare linie din fisierul html iar cand gasim tagul <title> vom copia toata linia fara primele 7 caractere (adica tagul de inceput 
de titlu ) intr-o copie a titlului. Dupa ce copiem linia aceea, vom cauta prin titlu(adica prin copie) si vom copia in baza de date 
(site[nr_siteuri].titlu) caracterv cu caracter titlul pana la caracterul '<', care arata ca se termina titlu deoarece urmeaza secventa "</title".
Se va afisa titlu si apoi newline.
se va creste nr_siteuri si se va realoca dinamic cu inca 3 daca nr_sieuri a ajuns la multiplu de 3 si nu e 0.
la final se elibereaza memoria.

TASK 2:
durata: cam in jur de 10 ore ca nu-mi mergea nimic si voiam sa ma dau batuta dar nu.

implementare: Pentru task-ul 2 am facut aceeasi citire ca la task-ul 1 , dar am memorat fiecare linie a html-ului in continut(in afara de prima
linie care a fost memorata fiecare cuvant de pe prima linie in alte variabile din struct). Aceasta variabila se numeste continut , iar 
pentru a parsa prin tagurile din continut am parcurs caracter cu carcater continutul, iar cand gasea tagul "<p" si pana cand se termina caracterul ">"
(adica daca are site ul html text cu culoare sau culoare de fundal va trece de ele pana gaseste ">", iar daca nu exista formatarea textului
doar ajunge la caracterul ">"). Astfel acum o sa fie doar paragraful din interiorul site ului html care va fi salvat pentru fiecare site
intr-un vector numit paragraf.
Pentru task-ul 2 am citit de la tastatura niste cuvinte cheie intr-un vector numit text_citit si am folosit un strtok pentru a lua fiecare cuvant din 
textul citit si fiecare cuvant din fiecare paragraf al fiecarui site , iar daca gaseam cuvantul din text_citit in paragraf aveam un vector de frecventa
care devenea 1 pt indicele site-ului . La final luam un alt vector care trebuia sortat si puneam in el toti indicii care aveau in vectorul de frecventa 1.
Avem 2 functii in taskul 2, una de comparare numita comparare1 si una de sortare, numita sortare. Functia de comparare ia 2 titluri iar daca sunt egale atunci
se compara  in functie de nr de accesari . Daca nr de accesari sunt in ordine descrescatoare se retunreaza 0, adica nu se va sorta invers (trebuie sa fie
 sortati descrescator in functie de nr de accesari). Daca nu sunt egale titlurile se va sorta crescator in functie de continutul paragrafelor, adica cand
difera o litera intre 2 paragrafe atunci daca sunt in ordine crescatoare(alfabetica sau cum se numeste) se returneaza 0, adica nu se sorteaza , altfel 1.
Functia de sortare e una simpla care primeste ca parametru functia de comparare ca pointer, iar daca returneaza 1 se vor interschimba indicii din vectorul
care trebuie sortat.
La final se vor afisa url-urile care au indicii in vectorul care a fost sortat, in ordinea in care apar in vector.

TASK 3:
durata: in jur de 2 ore deoarece doar a trebuit sa fa niste schimbari la task-ul 2

implementare:
Citirea e exact la fel ca la task-ul 2 (si cea din fisiere si cea de la tastatura).
Functia de sortare e exact la fel , iar singura diferenta de la functia de comparare, numita comparare2 este ca se compara doar nr de accesari a 2 siteuri,
daca sunt in ordine crescatoare returneaza 1 adica va trebui sa fie sortate, altfel 0.
Exista la fel un vector de frecventa si un vector sortat. Diferenta este ca atunci cand parcurgem cu strtok-uri cuvant cu cuvant o sa am un contor numit ok,
acesta se va folosi pt cuvintele dintre ghilimele, iar daca cuvantul din textul citit are primul sau ultimul caracter egal cu o ghilimea(sper ca asa se zice
sunt la poli) atunci contorul ok va creste. Ok este intial 0, iar atunci cand devine 1 inseamna ca am intrat in cuvintele dintre ghilimele, deci vectorul de frecventa nu 
va creste daca ok este egal cu 1 chiar daca exista un cuvant din paragraf egal cu un cuvant dintre ghilimele(deparece tre sa exista toata sintaxa nu doar un cuvant).
Altfel daca nu e 1, adica ori e inainte de ghilimele, ori dupa, ori nu exista ghilimele vectorul nde frecventa va creste. Daca cuvantul din textul citit
are primul caracter egal cu minus "-" atunci vectorul de frecventa va deveni -1, pentru a avea alta conditie ca daca exista acest cuvant in paragraf 
nu va fi pus in vectorul sortat indicele.
La final se va lua copia facuta la textul_citit si se va lua doar cuvintele dintre ghilimele intr-un string numit copie_ghilimele si se va parcurge din nou
prin toate site-urile, de data asta fara strtok iar daca se gaseste secventa din copie_ghilimele in paragraf si exista aceasta secventa si nu aeste vectorul
de frecventa -1, atunci vectorul de frecventa al indecelui siteului va primi 1.
La final se vor afisa url-urile care au indicii in vectorul care a fost sortat, in ordinea in care apar in vector.

TASK 4:
durata: in jur de o ora 

implementare:Task-ul 4 are 2 functii, rotr si rotl, care sunt aproape aceleasi , singura diferenta este cum se muta bitii, la rotr se mute spre dreapta, iar
la rotl se muta spre stanga. Deci functiile primesc ca parametru un x de tip char pe care il convertesc printr-o copie in int.
Dupa coverteste un numar de tip int intr-un sir de tip char care este forma binara a numarului.. Dupa se face siftarea bitiilor spre dreapta/stanga, iar
la final converteste un sir de tip char care este in forma binara intr-un numar de tip int si dupa aceea il returneaza.
Citirea este la fel ca la task-ul 2 si 3, iar la citirea de la tastatura se citeste cate o linie pana se termina, se compara cu fiecare url din toate site-urile
iar daca nu exista in baza de date acel url se va afisa "Website not found!". Altfel daca se gaseste url-ul se va calcula cheia_gasita astfel,
se va lua fiecare caracter din continut, iar daca caracterul este pe pozitie para va functiona fnctia rotl, altfel functia rotr. Se va calcula cu xor cheia
gasita, iar la final daca cheia_gasita este egala cu checksum-ul se va afisa "Website safe!",  altfel se va afisa
 "Malicious website! Official key: (checksumul). Found key: (cheia gasita)\n" .