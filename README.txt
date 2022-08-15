                               ==README==
                      
Stefan Alexandra Camelia grupa 314CB
->Tema foloseste structuri de arbori binari de cautare in construirea si 
functionarea unui sistem de fisiere, prin care se poate naviga prin comenzi 
de tip Linux.
->Pentru implemetare, am folosit doua structuri:una de tip director si una de
tip fisier. 
->Se citeste fiecare linie din fisierle de input, se extrage comanda aferenta
 si numele fisierului/directorului asupra caruia se efectueaza operatia.
 ->Pentru fiecare "comanda", se apeleaza functiile implementate care realizeaza
task-ul cerut

TOUCH
-Pentru comanda "touch", ne folosim de doua cazuri: 
1)atunci cand nu am maiintrodus pana la acel moment vreun fisier, deci
arborescenta de files este goala, vom folosi o functie auxiliara si vom
construi o frunza noua pur si simplu; 
2)verficam daca fisierul introdus exista deja in strucutura(inclusiv un 
director cu acelasi nume), caz in care afisam mesajele aferente:
"file/directory < name > already exists!" si de asemenea introducem noul nod
in ordinea RSD.

MKDIR
-Pentru comanda "mkdir", am folosit un algoritm absolut identic,  inlocuind
doar campul folosit (a->files devine, aici, a->directories);
 
LS
-Pentru comanda "ls", am construit doua functii utilitare:una pentru directoare, 
alta pentru fisier. Functiile sunt construite recursiv, operatiile sunt practic 
aplicate "radacinii" (generic spus) si folosindu-ne de recurenta aplicam pe 
stanga, respectiv dreapta(RSD). In final, apelam cele doua functii in functia 
principala "ls" cu parametri aferenti

RM 
-Pentru functia de remove file, vom evalua situatia dupa trei cazuri diferite:
1)atunci cand nodul pe care vrem sa l stergem nu are copii;2)nodul are un copil
si 30nodul are doi copii.Pentru prima parte ne folosim de recurenta, si, de
asemenea, afisam mesajul corespunzator atunci cand ce vrem sa stergem nu exista
de fapt in structura de fisiere.

RMDIR 
-Pentru comanda "rmdir", am folosit un algoritm absolut identic cu cel de 
remove file

CD 
-Pentru comanda de change directory, evaluam doua cazuri:
1) vrem sa ne intoarcem la directorul precedent, adica cd..
2)vrem sa mergem intr un anume director, adica parcurgem
arborele pana cand intalnim numele celui care ne intereseaza
In cazul in care avem cd<nume> iar directorul cu acel <nume>
nu exista, se va afisa mesajul "Directory not found!"

PWD 
-Se apeleaza "parintii", pana se intalneste "root".Astfel, la printare, va 
aparea calea directorului dat ca parametru: /root/../../..

Mentionez ca folosind ./check.sh am obtinut pe locat 101/135 si
