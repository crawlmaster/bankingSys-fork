# **Banking System**


Idei :
 - stocare : toate datele intr un fisier pe care aplic o anumita criptare (ceva simplu spre mediu) pentru a simula pe cat se poate de mult un sistem real bancar
 - ca stocare in program un min-heap/max-heap sau arbori , de ce una si de ce alta ?
 - programul poate fi folosit atat de clienti cat si de angajati, in functie de cine foloseste verifica daca acea persoana este si ofera accesul
 - pentru clienti : 
   * verificare sold , depunere numerar , extragere numerar , extragere iban (poate chiar in PDF - idee buna si realizabila ; ori biblioteca deja implementat , ori functie brute force) , (pentru viitor - credit cu un anumit procentaj , kinda - sub ?)
   * la finalul unei actiuni de implica bani , genereaza o chitanta (posibil pdf)


Ca angajat la banca s ar putea implementa o oarecare :ierarhie , (angajati simpli - care au acces si lucreaza cu clienti , contabili care au acces la bani si ii si manageriaza , admin - un soi de supervisior care verifica daca toata lumea isi face treaba cum trebuie - un oarecare .log files la un moment dat s ar putea de implementat pentru partea de cyber care in functie de anumite "atacuri" fac anumite activitati)


Pe viitor s ar putea adauga si data creeri contului pentru a putea eliminta clientii a caror carduri sunt expirate 

<br>
<br>

## **Pasii de implementare**


1. Crearea structurii pentru clienti ✅

