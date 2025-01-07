# Proiect Gestionare Biblioteca

Acest proiect implementează un sistem de gestionare a bibliotecilor într-un mod obiectual, utilizând clase, moștenire și șabloane (template-uri). Codul principal oferă o interfață interactivă pentru administrarea cărților și utilizatorilor. Funcționalitățile acoperite includ adăugarea, afișarea, împrumutul, returnarea și gestionarea utilizatorilor și cărților.

## Functionalitati principale ale proiectului<br>

### Gestionarea cartilor:
* Adăugarea de cărți fizice și electronice.<br>
* Afișarea tuturor cărților înregistrate.<br>
* Împrumutul și returnarea cărților, inclusiv validarea datelor introduse.<br>
* Afișarea cărților împrumutate și sortarea lor după titlu.<br>
* Stocarea și citirea cărților dintr-un fișier (carti.txt).<br>

### Gestionarea utilizatorilor:
* Adăugarea de utilizatori (elevi sau profesori) prin introducerea datelor lor.<br>
* Afișarea tuturor utilizatorilor înregistrați.<br>
* Stocarea și citirea utilizatorilor dintr-un fișier (utilizatori.txt).<br>

### Statistici:
* Afișarea numărului total de utilizatori.<br>
* Afișarea numărului total de cărți disponibile în sistem.<br>

### Salvarea datelor:
* Persistența informațiilor despre cărți și utilizatori în fișiere, pentru a evita pierderea datelor între sesiuni.<br>

### Validari si tratarea erorilor:
* Introducerea de validări pentru datele de intrare (ex. formatul datei, stocuri negative).<br>
* Gestionarea excepțiilor folosind mecanismele C++ pentru a preveni comportamentele neașteptate.<br>

### Clasa template Biblioteca:
* Implementarea clasei Biblioteca<T> pentru a gestiona colecții de obiecte de tip T.<br>
* Operațiuni precum adăugarea de elemente și afișarea tuturor obiectelor.<br>


## Structura principala a codului<br>

### Clase principale:
* Carte: Clasa abstractă de bază pentru reprezentarea cărților.<br>
* CarteFizica și CarteElectronica: Clase derivate din Carte, reprezentând specific tipurile de cărți.<br>
* Utilizator: Clasa abstractă de bază pentru reprezentarea utilizatorilor.<br>
* Elev și Profesor: Clase derivate din Utilizator.<br>
* LibraryManagement: Clasă pentru gestionarea cărților.<br>
* ManagerUtilizatori: Singleton pentru gestionarea utilizatorilor.<br>

### Interfata Interactiva:
* Implementată în main(), utilizând un meniu interactiv pentru utilizator.<br>

### Fisiere de intrare/iesire:
* Cărțile sunt salvate și încărcate din fișierul carti.txt.<br>
* Utilizatorii sunt salvați și încărcați din fișierul utilizatori.txt.<br>

### Cerinta suplimentara:
* Adăugarea unui mecanism de gestionare a cărților fizice și electronice, inclusiv stoc și format.<br>
* Validarea corectă a datelor (ex. stocuri pozitive, formate de fișiere acceptabile).<br>
* Gestionarea excepțiilor, precum stocuri negative sau date invalide.<br>

Proiectul pune accent pe utilizarea conceptelor de moștenire, șabloane (templates) și gestionarea resurselor prin intermediul pointerilor inteligenți (shared_ptr). Acesta oferă o soluție completă și scalabilă pentru gestionarea unei biblioteci.<br>
