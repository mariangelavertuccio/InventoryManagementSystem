# Inventory Management System

Un semplice sistema di gestione dell'inventario sviluppato in **C++17** come progetto pratico di portfolio.

## Funzionalità

- Inserimento di nuovi prodotti con ID, nome, prezzo e quantità
- Visualizzazione dell'inventario
- Ricerca di un prodotto tramite ID
- Modifica dei dati di un prodotto
- Eliminazione di un prodotto con conferma
- Calcolo del valore totale di ogni prodotto e dell'intero inventario
- Salvataggio automatico dei dati in `prodotti.txt`
- Caricamento automatico dei dati all'avvio
- Controllo degli input e gestione di valori non validi


## Tecnologie e concetti C++

- C++17
- `struct`
- `vector`
- Funzioni
- Cicli e condizioni (`do-while`, `for`, `switch`)
- Riferimenti e parametri
- Input/output da console
- Lettura e scrittura su file (`fstream`)
- Ricerca e gestione degli elementi in un contenitore

## Requisiti

È necessario un compilatore C++ che supporti lo standard C++17, ad esempio GCC.

## Compilazione ed esecuzione

Da terminale, nella cartella del progetto:

```bash
g++ main.cpp -std=c++17 -Wall -Wextra -o inventory.exe
```

Su Windows PowerShell:

```powershell
.\inventory.exe
```

Su Linux/macOS:

```bash
./inventory
```

## Persistenza dei dati

Il programma crea automaticamente il file `prodotti.txt` nella cartella da cui viene eseguito. I dati vengono salvati dopo ogni inserimento, modifica o eliminazione e ricaricati al successivo avvio.

Il file `prodotti.txt` è un file dati generato dal programma e non è necessario caricarlo su GitHub.

## Possibili sviluppi futuri

- Separazione del codice in più file (`.h` e `.cpp`)
- Test automatici
- Interfaccia grafica
- Database SQLite
- Gestione di categorie e fornitori
- Report e statistiche avanzate

## Autrice

Progetto personale di Mariangela Vertuccio
