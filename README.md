# Proiect Gestionare Biblioteca

Acest proiect implementează un sistem de gestionare a bibliotecilor într-un mod obiectual, utilizând clase, moștenire și șabloane (template-uri). Codul principal oferă o interfață interactivă pentru administrarea cărților și utilizatorilor. Funcționalitățile acoperite includ adăugarea, afișarea, împrumutul, returnarea și gestionarea utilizatorilor și cărților.

Funcționalități principale ale proiectului:<br>
Gestionarea cărților:<br>

Adăugarea de cărți fizice și electronice.<br>
Afișarea tuturor cărților înregistrate.<br>
Împrumutul și returnarea cărților, inclusiv validarea datelor introduse.<br>
Afișarea cărților împrumutate și sortarea lor după titlu.<br>
Stocarea și citirea cărților dintr-un fișier (carti.txt).<br>
Gestionarea utilizatorilor:<br>

Adăugarea de utilizatori (elevi sau profesori) prin introducerea datelor lor.<br>
Afișarea tuturor utilizatorilor înregistrați.<br>
Stocarea și citirea utilizatorilor dintr-un fișier (utilizatori.txt).<br>
Statistici:<br>

Afișarea numărului total de utilizatori.<br>
Afișarea numărului total de cărți disponibile în sistem.<br>
Salvarea datelor:<br>

Persistența informațiilor despre cărți și utilizatori în fișiere, pentru a evita pierderea datelor între sesiuni.<br>
Validări și tratarea erorilor:<br>

Introducerea de validări pentru datele de intrare (ex. formatul datei, stocuri negative).<br>
Gestionarea excepțiilor folosind mecanismele C++ pentru a preveni comportamentele neașteptate.<br>
Clasa Template Biblioteca:<br>
Implementarea clasei Biblioteca<T> pentru a gestiona colecții de obiecte de tip T.<br>
Operațiuni precum adăugarea de elemente și afișarea tuturor obiectelor.<br>
Structura principală a codului:<br>
Clase principale:<br>

Carte: Clasa abstractă de bază pentru reprezentarea cărților.<br>
CarteFizica și CarteElectronica: Clase derivate din Carte, reprezentând specific tipurile de cărți.<br>
Utilizator: Clasa abstractă de bază pentru reprezentarea utilizatorilor.<br>
Elev și Profesor: Clase derivate din Utilizator.<br>
LibraryManagement: Clasă pentru gestionarea cărților.<br>
ManagerUtilizatori: Singleton pentru gestionarea utilizatorilor.<br>
Interfața interactivă:<br>

Implementată în main(), utilizând un meniu interactiv pentru utilizator.<br>
Fișiere de intrare/ieșire:<br>

Cărțile sunt salvate și încărcate din fișierul carti.txt.<br>
Utilizatorii sunt salvați și încărcați din fișierul utilizatori.txt.<br>
Cerințe suplimentare:<br>
Adăugarea unui mecanism de gestionare a cărților fizice și electronice, inclusiv stoc și format.<br>
Validarea corectă a datelor (ex. stocuri pozitive, formate de fișiere acceptabile).<br>
Gestionarea excepțiilor, precum stocuri negative sau date invalide.<br>
Proiectul pune accent pe utilizarea conceptelor de moștenire, șabloane (templates) și gestionarea resurselor prin intermediul pointerilor inteligenți <br>(shared_ptr). Acesta oferă o soluție completă și scalabilă pentru gestionarea unei biblioteci.<br>
