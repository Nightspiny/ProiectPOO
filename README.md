# Proiect Gestionare Biblioteca

Acest proiect implementează un sistem de gestionare a bibliotecilor într-un mod obiectual, utilizând clase, moștenire și șabloane (template-uri). Codul principal oferă o interfață interactivă pentru administrarea cărților și utilizatorilor. Funcționalitățile acoperite includ adăugarea, afișarea, împrumutul, returnarea și gestionarea utilizatorilor și cărților.

Funcționalități principale ale proiectului:
Gestionarea cărților:

Adăugarea de cărți fizice și electronice.
Afișarea tuturor cărților înregistrate.
Împrumutul și returnarea cărților, inclusiv validarea datelor introduse.
Afișarea cărților împrumutate și sortarea lor după titlu.
Stocarea și citirea cărților dintr-un fișier (carti.txt).
Gestionarea utilizatorilor:

Adăugarea de utilizatori (elevi sau profesori) prin introducerea datelor lor.
Afișarea tuturor utilizatorilor înregistrați.
Stocarea și citirea utilizatorilor dintr-un fișier (utilizatori.txt).
Statistici:

Afișarea numărului total de utilizatori.
Afișarea numărului total de cărți disponibile în sistem.
Salvarea datelor:

Persistența informațiilor despre cărți și utilizatori în fișiere, pentru a evita pierderea datelor între sesiuni.
Validări și tratarea erorilor:

Introducerea de validări pentru datele de intrare (ex. formatul datei, stocuri negative).
Gestionarea excepțiilor folosind mecanismele C++ pentru a preveni comportamentele neașteptate.
Clasa Template Biblioteca:
Implementarea clasei Biblioteca<T> pentru a gestiona colecții de obiecte de tip T.
Operațiuni precum adăugarea de elemente și afișarea tuturor obiectelor.
Structura principală a codului:
Clase principale:

Carte: Clasa abstractă de bază pentru reprezentarea cărților.
CarteFizica și CarteElectronica: Clase derivate din Carte, reprezentând specific tipurile de cărți.
Utilizator: Clasa abstractă de bază pentru reprezentarea utilizatorilor.
Elev și Profesor: Clase derivate din Utilizator.
LibraryManagement: Clasă pentru gestionarea cărților.
ManagerUtilizatori: Singleton pentru gestionarea utilizatorilor.
Interfața interactivă:

Implementată în main(), utilizând un meniu interactiv pentru utilizator.
Fișiere de intrare/ieșire:

Cărțile sunt salvate și încărcate din fișierul carti.txt.
Utilizatorii sunt salvați și încărcați din fișierul utilizatori.txt.
Cerințe suplimentare:
Adăugarea unui mecanism de gestionare a cărților fizice și electronice, inclusiv stoc și format.
Validarea corectă a datelor (ex. stocuri pozitive, formate de fișiere acceptabile).
Gestionarea excepțiilor, precum stocuri negative sau date invalide.
Proiectul pune accent pe utilizarea conceptelor de moștenire, șabloane (templates) și gestionarea resurselor prin intermediul pointerilor inteligenți (shared_ptr). Acesta oferă o soluție completă și scalabilă pentru gestionarea unei biblioteci.
