# Hospital Manager

Acest proiect reprezintă o aplicație de tip consolă scrisă în C++, ce simulează gestiunea unui spital privat. Include funcționalități pentru managementul doctorilor, pacienților, programărilor și inventarului medical.

### 🔹 Doctori
- Afișarea tuturor doctorilor
- Căutare doctor după nume
- Atribuirea pacienților în funcție de specialitate și boală
- Externarea pacienților
- Afișarea doctorilor specializați în „Cardiologie” folosind funcție generică `filterByPredicate`

---

### 🔹 Pacienți
- Adăugarea pacienților noi (cu validare CNP, vârstă, gen)
- Asocierea unor boli
- Vizualizarea detaliilor unui pacient
- Afișarea pacienților peste 60 de ani (seniori) folosind `filterByPredicate`

---

### 🔹 Programări
- Adăugarea unei programări doar dacă:
  - Pacientul este asignat doctorului
  - Doctorul este calificat pentru boala pacientului
  - Data este validă (cu cel puțin 7 zile în viitor, doar zile lucrătoare între 08:30 și 18:45)
  - Nu există conflict de orar
- Validare detaliată pentru dată și oră (`std::tm`, `chrono`)
- Implementare `AppointmentBuilder` pentru creare fluentă a unei programări
- Afișarea tuturor programărilor existente

---

### 🔹 Inventar medical
- Clasă generică `InventoryItemTemplate<T>`
  - T poate fi `int`, `std::string` etc., pentru informații adiționale precum: cod lot, locație, observații
- Adăugare iteme în inventar prin meniu interactiv
- Validări pentru nume, tip și preț
- Listare completă a echipamentelor și medicamentelor
- Design extensibil și sigur (folosind `unique_ptr`, `vector`, template-uri)

---

## ⚠️ Excepții personalizate
Sistemul gestionează erori folosind excepții derivate din `SpitalException`, printre care:
- `EntityNotFoundException`
- `InvalidInputException`
- `AppointmentConflictException`
- `InvalidAppointmentException`
- `InvalidCNPException`

---

## 🧰 Tehnologii și concepte C++ utilizate

- `C++11` standard
- STL: `vector`, `map`, `unique_ptr`, `algorithm`, `chrono`, `sstream`
- Programare orientată pe obiecte
- Excepții personalizate
- Design pattern: Builder (`AppointmentBuilder`)
- Template-uri (pentru inventar)
- Funcții lambda și generice (`filterByPredicate`)

---

| Marius MC | https://github.com/mcmarius/oop-template     |






### Important!

Aveți voie cu cod generat de modele de limbaj la care nu ați contribuit semnificativ doar în folder-ul `generated`.
Codul generat pus "ca să fie"/pe care nu îl înțelegeți se punctează doar pentru puncte bonus, doar în contextul
în care oferă funcționalități ajutătoare și doar dacă are sens.

O cerință nu se consideră îndeplinită dacă este realizată doar prin cod generat.

- **Fără cod de umplutură/fără sens!**
- **Fără copy-paste!**
- **Fără variabile globale!**
- **Fără atribute publice!**

### Tema 0

- [✔️] Nume proiect (poate fi schimbat ulterior)
- [✔️] Scurtă descriere a temei alese, ce v-ați propus să implementați

## Tema 1

#### Cerințe
- [✔️] definirea a minim **3-4 clase** folosind compunere cu clasele definite de voi; moștenirile nu se iau în considerare aici
- [✔️] constructori de inițializare cu parametri pentru fiecare clasă
- [✔️] pentru o aceeași (singură) clasă: constructor de copiere, `operator=` de copiere, destructor
<!-- - [ ] pentru o altă clasă: constructor de mutare, `operator=` de mutare, destructor -->
<!-- - [ ] pentru o altă clasă: toate cele 5 funcții membru speciale -->
- [✔️] `operator<<` pentru **toate** clasele pentru afișare (`std::ostream`) folosind compunere de apeluri cu `operator<<`
- [✔️] cât mai multe `const` (unde este cazul) și funcții `private`
- [✔️] implementarea a minim 3 funcții membru publice pentru funcționalități netriviale specifice temei alese, dintre care cel puțin 1-2 funcții mai complexe
  - nu doar citiri/afișări sau adăugat/șters elemente într-un/dintr-un vector
- [✔️] scenariu de utilizare **cu sens** a claselor definite:
  - crearea de obiecte și apelarea tuturor funcțiilor membru publice în main
  - vor fi adăugate în fișierul `tastatura.txt` DOAR exemple de date de intrare de la tastatură (dacă există); dacă aveți nevoie de date din fișiere, creați alte fișiere separat
- [✔️] minim 50-55% din codul propriu să fie C++, `.gitattributes` configurat corect
- [✔️] tag de `git`: de exemplu `v0.1`
- [✔️] serviciu de integrare continuă (CI) cu **toate bifele**; exemplu: GitHub Actions

## Tema 2

#### Cerințe
- [✔️] separarea codului din clase în `.h` (sau `.hpp`) și `.cpp`
- [✔️] moșteniri:
  - minim o clasă de bază și **3 clase derivate** din aceeași ierarhie
  - ierarhia trebuie să fie cu bază proprie, nu derivată dintr-o clasă predefinită
  - [✔️] funcții virtuale (pure) apelate prin pointeri de bază din clasa care conține atributul de tip pointer de bază
    - minim o funcție virtuală va fi **specifică temei** (i.e. nu simple citiri/afișări sau preluate din biblioteci i.e. draw/update/render)
    - constructori virtuali (clone): sunt necesari, dar nu se consideră funcții specifice temei
    - afișare virtuală, interfață non-virtuală
  - [✔️] apelarea constructorului din clasa de bază din constructori din derivate
  - [✔️] clasă cu atribut de tip pointer la o clasă de bază cu derivate; aici apelați funcțiile virtuale prin pointer de bază, eventual prin interfața non-virtuală din bază
    - [✔️] suprascris cc/op= pentru copieri/atribuiri corecte, copy and swap
    - [✔️] `dynamic_cast`/`std::dynamic_pointer_cast` pentru downcast cu sens
    - [✔️] smart pointers (recomandat, opțional)
- [✔️] excepții
  - [✔️] ierarhie proprie cu baza `std::exception` sau derivată din `std::exception`; minim **3** clase pentru erori specifice distincte
    - clasele de excepții trebuie să trateze categorii de erori distincte (exemplu de erori echivalente: citire fișiere cu diverse extensii)
  - [✔️] utilizare cu sens: de exemplu, `throw` în constructor (sau funcție care întoarce un obiect), `try`/`catch` în `main`
  - această ierarhie va fi complet independentă de ierarhia cu funcții virtuale
- [✔️] funcții și atribute `static`
- [✔️] STL
- [✔️] cât mai multe `const`
- [✔️] funcții *de nivel înalt*, de eliminat cât mai mulți getters/setters/funcții low-level
- [ ✔️] minim 75-80% din codul propriu să fie C++
- [✔️] la sfârșit: commit separat cu adăugarea unei noi clase derivate fără a modifica restul codului, **pe lângă cele 3 derivate deja adăugate** din aceeași ierarhie
  - noua derivată nu poate fi una existentă care a fost ștearsă și adăugată din nou
  - noua derivată va fi integrată în codul existent (adică va fi folosită, nu adăugată doar ca să fie)
- [✔️] tag de `git` pe commit cu **toate bifele**: de exemplu `v0.2`

## Tema 3

#### Cerințe
- [✔️] 2 șabloane de proiectare (design patterns)
- [✔️] o clasă șablon cu sens; minim **2 instanțieri**
  - [✔️] preferabil și o funcție șablon (template) cu sens; minim 2 instanțieri
- [✔️] tag de `git` pe commit cu **toate bifele**: de exemplu `v0.3` sau `v1.0`

## Instrucțiuni de compilare

Proiectul este configurat cu CMake.

Instrucțiuni pentru terminal:

1. Pasul de configurare
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
# sau ./scripts/cmake.sh configure
```

Sau pe Windows cu GCC:
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -G Ninja
# sau ./scripts/cmake.sh configure -g Ninja
```

La acest pas putem cere să generăm fișiere de proiect pentru diverse medii de lucru.


2. Pasul de compilare
```sh
cmake --build build --config Debug --parallel 6
# sau ./scripts/cmake.sh build
```

Cu opțiunea `parallel` specificăm numărul de fișiere compilate în paralel.


3. Pasul de instalare (opțional)
```sh
cmake --install build --config Debug --prefix install_dir
# sau ./scripts/cmake.sh install
```

Vezi și [`scripts/cmake.sh`](scripts/cmake.sh).

Observație: folderele `build/` și `install_dir/` sunt adăugate în fișierul `.gitignore` deoarece
conțin fișiere generate și nu ne ajută să le versionăm.


## 📚 Resurse utilizate

Pe parcursul dezvoltării acestui proiect, m-am documentat și am aplicat concepte din mai multe surse externe de încredere. Acestea m-au ajutat să înțeleg și să implementez eficient principiile OOP, utilizarea STL și design patterns în C++:

- 📘 **C++ Primer (5th Edition)** – Stanley B. Lippman, Josée Lajoie, Barbara E. Moo  
  *Pentru aprofundarea claselor, STL, excepțiilor și manipulării șabloanelor (template-uri)*

- 📘 **Effective Modern C++** – Scott Meyers  
  *Ghid avansat pentru folosirea corectă a `unique_ptr`, `auto`, lambdas și move semantics*

- 🌐 [cplusplus.com](http://www.cplusplus.com/)  
  *Documentație oficială C++: pentru referințe rapide la `std::vector`, `std::map`, `std::chrono`, `std::get_time`, etc.*

- 🌐 [cppreference.com](https://en.cppreference.com/)  
  *O resursă tehnică esențială pentru detalii exacte despre standardul C++11 și STL*

- 📹 [The Cherno – YouTube](https://www.youtube.com/user/TheChernoProject)  
  *Playlist C++ Series – explicații vizuale excelente despre clase, templates și pointeri inteligenți*

- 🌐 [Refactoring.Guru](https://refactoring.guru/design-patterns/builder/cpp/example)  
  *Pentru înțelegerea și aplicarea design pattern-ului Builder*

- 🌐 [Stack Overflow](https://stackoverflow.com/)  
  *Pentru soluții punctuale legate de conversii de timp (`std::tm`, `std::chrono`), STL și debugging general*

- 📄 Notițele și exemplele de curs/laborator din cadrul disciplinei POO  
  *Fundamentul proiectului și cerințele de implementare au fost adaptate din cadrul cursului oficial*

---
