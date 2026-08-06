# 🏦 Banking System (C)

> Sistem bancar CLI, scris în C, cu persistență criptată pe disc, metadate binare packed și hash table în memorie pentru lookup rapid al clienților.


Repo: [github.com/justxma/bankingSys](https://github.com/justxma/bankingSys)

---

## 📑 Cuprins

- [Despre proiect](#-despre-proiect)
- [Arhitectură & Flux de date](#-arhitectură--flux-de-date)
- [Structura & ierarhia fișierelor](#-structura--ierarhia-fișierelor)
- [Specificații de stocare](#-specificații-de-stocare)
- [Compilare & Build (Makefile)](#-compilare--build-makefile)
- [Utilizare (Usage)](#-utilizare-usage)
- [Meniu principal](#-meniu-principal)
- [Principii de dezvoltare & siguranță](#-principii-de-dezvoltare--siguranță)
- [Roadmap](#-roadmap)
- [Licență](#-licență)

---

## 📌 Despre proiect

**Banking System** este un proiect personal educațional, scris integral în **C (C99+)**, care simulează un sistem bancar minimal, operabil din linia de comandă (CLI).

Proiectul demonstrează concepte de bază și avansate de programare de sistem:

- gestiune manuală a memoriei (`malloc`/`calloc`/`free`);
- persistență pe disc prin fișiere binare și text criptat;
- structuri de date packed (`#pragma pack`) pentru interoperabilitate binară;
- criptare simplă (shift cipher) + encodare hexazecimală;
- hash table pentru căutare rapidă a clienților în memorie.

Scopul este de a exersa arhitectura unui sistem de tip client-record management, cu un accent puternic pe siguranța memoriei și pe organizarea modulară a codului sursă.

---

## 🧩 Arhitectură & Flux de date

Fluxul de scriere/citire al datelor clienților trece prin mai multe straturi de transformare:

```
[Date Plaintext] ──► [Cifru Multi-Char Shift] ──► [Encoder Hex String] ──► [Scriere Fișier]

[Citire Fișier]  ──► [Decoder Hex String] ──► [Inversare Cifru Shift] ──► [Memorie RAM]
```

### Straturi de procesare

| Strat | Descriere |
|---|---|
| **Alphabet Shifting** | Deplasează limitele alfabetice (`a-z`, `A-Z`) și numerice (`0-9`) în mod ciclic, folosind aritmetică modulară. |
| **Hex Encoding Layer** | Bytes-ii cifrului brut sunt convertiți în perechi hexazecimale, astfel încât caracterele de control (ex: newline, terminatori de string) să nu afecteze parsere precum `fgets` sau `fscanf`. |

### Metadate binare & sistem de control

Sistemul se bazează pe o structură C **packed**, salvată în `dataBase/config.meta`:

```c
#pragma pack(push, 1)
typedef struct {
    char       headerKw[5];         // Semnătură magică "CFMT\0"
    uint32_t   numberOfClients;     // Numărul total de înregistrări
    uint32_t   lastID;              // Ultimul ID alocat (auto-increment)
    uint8_t    isEncrypted;         // Flag criptare (1 = Activ, 0 = Plain)
    uint8_t    cypherShift;         // Cheia de deplasare a cifrului
    uint64_t   createdTime;         // Timestamp UNIX - creare DB
    uint64_t   lastTimeModified;    // Timestamp UNIX - ultima modificare
    uint32_t   dbChecksum;          // Hash de verificare a integrității
} dbConfig;
#pragma pack(pop)
```

Citind această structură cu dimensiune fixă via `fread()` la pornire, sistemul determină parametrii operaționali în timp **O(1)**, fără a citi `dataBase.txt`.

---

## 🗂 Structura & ierarhia fișierelor

```
banking_sys/
├── dataBase/
│   ├── config.meta          # Fișier binar de control pentru metadate & stare DB
│   └── dataBase.txt         # Stocare principală criptată (persistență)
│
├── executable_files/        # Folder țintă pentru binarele compilate
│
├── include/                 # Fișiere header (.h) — declarații & structuri
│   ├── config.h
│   ├── crypto.h
│   ├── hashtable.h
│   └── utils.h
│
├── src/                     # Implementări module core (.c)
│   ├── config.c
│   ├── crypto.c
│   ├── hashtable.c
│   └── utils.c
│
├── main_sys.c                # Punct de intrare & router meniu CLI
└── Makefile                  # Script de automatizare a build-ului
```

### Rol pe module

| Modul | Responsabilitate |
|---|---|
| `config.c/.h` | Citire/scriere `config.meta`, gestionare metadate DB |
| `crypto.c/.h` | Cifrare/decifrare shift + encodare/decodare hex |
| `hashtable.c/.h` | Structura de date hash table pentru clienți în RAM |
| `utils.c/.h` | Funcții helper generale (I/O, string, validări) |
| `main_sys.c` | Meniu CLI, orchestrarea fluxului aplicației |

---

## 💾 Specificații de stocare

| Strat de stocare | Format | Cale | Scop |
|---|---|---|---|
| **Control Header** | Binar packed (`#pragma pack(1)`) | `dataBase/config.meta` | Verificare rapidă O(1) a stării, timestamps, configurație sistem |
| **Client Storage** | Hex Streams criptate | `dataBase/dataBase.txt` | Persistența înregistrărilor între sesiuni |
| **In-Memory Cache** | Hash Buckets dinamice | RAM (Heap) | Lookup, editare și execuție sub-milisecundă |

---

## ⚙️ Compilare & Build (Makefile)

### Cerințe preliminare

- **GCC** (`gcc`) cu suport pentru C99 sau mai nou
- **GNU Make** (`make`)
- **Valgrind** *(opțional)* — pentru profiling de memorie pe Linux/macOS

### Comenzi de build

**1. Compilare binar**

Compilează toate fișierele sursă și le leagă în `executable_files/main_sys`:

```bash
make
```

**2. Rulare aplicație**

Compilează (dacă e necesar) și execută aplicația:

```bash
make run
```

**3. Curățare artefacte de build**

Elimină executabilele, fișierele obiect și output-urile temporare:

```bash
make clean
```

### Audit de memorie cu Valgrind

Pentru a garanta zero memory leaks, pointeri dangling sau buffer overflows la runtime:

```bash
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         ./executable_files/main_sys
```

---

## 🚀 Utilizare (Usage)

### 1. Faza de inițializare

La pornire, aplicația rulează următoarea secvență de boot:

1. Afișează bannerul ASCII și branding-ul terminalului.
2. Verifică existența fișierului `dataBase/config.meta`.
   - Dacă **lipsește**, inițializează o configurație implicită cu semnătura `CFMT` și o salvează în mod `wb`.
   - Dacă **există**, citește parametrii binari (`fread`) direct în memorie.
3. Încarcă `dataBase/dataBase.txt`, decriptează înregistrările "in flight" și populează Hash Table-ul din memorie.

### 2. Exemplu rapid de rulare

```bash
git clone https://github.com/justxma/bankingSys.git
cd bankingSys/banking_sys
make
make run
```

---

## 📋 Meniu principal

Utilizatorul interacționează prin interfața de linie de comandă:

| Opțiune | Acțiune |
|---|---|
| **[1]** Authenticate / Login | Caută o înregistrare client după ID/username via Hash Table |
| **[2]** Register New Client | Colectează detaliile utilizatorului, generează ID auto-incrementat, scrie payload criptat în fișier, actualizează `config.meta` |
| **[3]** View System Metadata | Afișează datele de creare formatate, cheia de shift, numărul total de clienți și timestamp-urile de modificare |
| **[4]** Exit | Salvează datele în așteptare, actualizează `lastTimeModified`, eliberează toată memoria heap alocată și iese elegant din program |

---

## 🛡 Principii de dezvoltare & siguranță

- **Memory Management** — fiecare bloc `malloc`/`calloc` este însoțit de un `free()` corespunzător.
- **Pointer Safety** — pointerii dubli sunt folosiți doar în rutinele de realocare dinamică; manipulările standard de array folosesc pointeri simpli (`char *`).
- **Standardized Types** — se preferă tipurile explicite din `<stdint.h>` (`uint32_t`, `uint64_t`) în locul tipurilor dependente de arhitectură, pentru a garanta alinierea structurală cross-platform.
- **File Stream Isolation** — fișierele deschise sunt închise (`fclose`) imediat după transferul de date, pentru a evita resource leaks.

---

## 🔮 Roadmap

- [ ] **Suport multi-valută** — clienții pot deține solduri EUR, USD și RON
- [ ] **Audit Log tranzacții** — jurnal append-only pentru depuneri, retrageri și transferuri
- [ ] **Criptare AES-256** — upgrade de la cifrul shift-based la un cifru bloc AES
- [ ] **Arhitectură server multi-threaded** — server TCP bazat pe socket-uri, pentru conectarea CLI de la clienți remote

---

## Project still in development!

## 📜 Licență

Distribuit sub **licența MIT**. Creat în scop educațional și demonstrativ, pentru programare de sistem în C, securitate și arhitectură software de nivel scăzut.