#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>

using namespace std;

// Rappresenta un prodotto dell'inventario.
struct Prodotto {
    int id;
    string nome;
    double prezzo;
    int quantita;
};

const string FILE_DATI = "prodotti.txt";

// Legge una riga e la converte in un intero positivo.
int leggiIntero(const string& messaggio, int minimo = 0) {
    while (true) {
        cout << messaggio;
        string riga;
        getline(cin, riga);

        stringstream ss(riga);
        int valore;
        char carattereExtra;

        if ((ss >> valore) && !(ss >> carattereExtra) && valore >= minimo) {
            return valore;
        }

        cout << "Input non valido. Inserisci un numero intero maggiore o uguale a "
             << minimo << ".\n";
    }
}

// Legge un numero decimale non negativo. Accetta sia il punto sia la virgola.
double leggiPrezzo(const string& messaggio) {
    while (true) {
        cout << messaggio;
        string riga;
        getline(cin, riga);

        replace(riga.begin(), riga.end(), ',', '.');

        stringstream ss(riga);
        double valore;
        char carattereExtra;

        if ((ss >> valore) && !(ss >> carattereExtra) && valore >= 0) {
            return valore;
        }

        cout << "Prezzo non valido. Inserisci un numero maggiore o uguale a 0.\n";
    }
}

// Legge un testo non vuoto.
string leggiTesto(const string& messaggio) {
    while (true) {
        cout << messaggio;
        string testo;
        getline(cin, testo);

        if (!testo.empty() && testo.find('|') == string::npos) {
            return testo;
        }

        cout << "Nome non valido: non può essere vuoto né contenere il carattere '|'.\n";
    }
}

int trovaIndicePerId(const vector<Prodotto>& prodotti, int id) {
    for (size_t i = 0; i < prodotti.size(); ++i) {
        if (prodotti[i].id == id) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

void salvaInventario(const vector<Prodotto>& prodotti) {
    ofstream file(FILE_DATI);

    if (!file) {
        cout << "Errore: impossibile salvare il file dei prodotti.\n";
        return;
    }

    file << fixed << setprecision(2);

    for (const Prodotto& prodotto : prodotti) {
        file << prodotto.id << '|'
             << prodotto.nome << '|'
             << prodotto.prezzo << '|'
             << prodotto.quantita << '\n';
    }
}

void caricaInventario(vector<Prodotto>& prodotti) {
    ifstream file(FILE_DATI);

    if (!file) {
        return; // Il file verrà creato al primo salvataggio.
    }

    string riga;
    while (getline(file, riga)) {
        stringstream ss(riga);
        string idTesto, nome, prezzoTesto, quantitaTesto;

        if (!getline(ss, idTesto, '|') ||
            !getline(ss, nome, '|') ||
            !getline(ss, prezzoTesto, '|') ||
            !getline(ss, quantitaTesto)) {
            continue;
        }

        try {
            Prodotto prodotto;
            prodotto.id = stoi(idTesto);
            prodotto.nome = nome;
            prodotto.prezzo = stod(prezzoTesto);
            prodotto.quantita = stoi(quantitaTesto);

            if (prodotto.id > 0 && !prodotto.nome.empty() &&
                prodotto.prezzo >= 0 && prodotto.quantita >= 0 &&
                trovaIndicePerId(prodotti, prodotto.id) == -1) {
                prodotti.push_back(prodotto);
            }
        } catch (const exception&) {
            // Ignora le righe non valide senza interrompere il caricamento.
        }
    }
}

void aggiungiProdotto(vector<Prodotto>& prodotti) {
    cout << "\n--- AGGIUNGI PRODOTTO ---\n";

    int id = leggiIntero("Inserisci ID prodotto: ", 1);

    if (trovaIndicePerId(prodotti, id) != -1) {
        cout << "Esiste già un prodotto con questo ID.\n";
        return;
    }

    string nome = leggiTesto("Inserisci nome prodotto: ");
    double prezzo = leggiPrezzo("Inserisci prezzo: ");
    int quantita = leggiIntero("Inserisci quantità: ", 0);

    prodotti.push_back({id, nome, prezzo, quantita});
    salvaInventario(prodotti);

    cout << "\nProdotto aggiunto correttamente!\n";
    cout << "Valore totale del prodotto: "
         << fixed << setprecision(2) << prezzo * quantita << " euro\n";
}

void visualizzaProdotti(const vector<Prodotto>& prodotti) {
    cout << "\n--- INVENTARIO ---\n";

    if (prodotti.empty()) {
        cout << "L'inventario è vuoto.\n";
        return;
    }

    cout << left
         << setw(8) << "ID"
         << setw(22) << "NOME"
         << right
         << setw(14) << "PREZZO"
         << setw(14) << "QUANTITA"
         << setw(18) << "VALORE TOTALE" << '\n';

    cout << string(76, '-') << '\n';

    double valoreInventario = 0.0;

    for (const Prodotto& prodotto : prodotti) {
        double valoreTotale = prodotto.prezzo * prodotto.quantita;
        valoreInventario += valoreTotale;

        cout << left
             << setw(8) << prodotto.id
             << setw(22) << prodotto.nome
             << right << fixed << setprecision(2)
             << setw(14) << prodotto.prezzo
             << setw(14) << prodotto.quantita
             << setw(18) << valoreTotale << '\n';
    }

    cout << string(76, '-') << '\n';
    cout << "Numero prodotti: " << prodotti.size() << '\n';
    cout << "Valore complessivo inventario: "
         << fixed << setprecision(2) << valoreInventario << " euro\n";
}

void cercaProdotto(const vector<Prodotto>& prodotti) {
    cout << "\n--- CERCA PRODOTTO ---\n";
    int id = leggiIntero("Inserisci ID da cercare: ", 1);
    int indice = trovaIndicePerId(prodotti, id);

    if (indice == -1) {
        cout << "Nessun prodotto trovato con ID " << id << ".\n";
        return;
    }

    const Prodotto& p = prodotti[static_cast<size_t>(indice)];
    cout << "\nProdotto trovato:\n";
    cout << "ID: " << p.id << '\n';
    cout << "Nome: " << p.nome << '\n';
    cout << "Prezzo: " << fixed << setprecision(2) << p.prezzo << " euro\n";
    cout << "Quantità: " << p.quantita << '\n';
    cout << "Valore totale: " << p.prezzo * p.quantita << " euro\n";
}

void modificaProdotto(vector<Prodotto>& prodotti) {
    cout << "\n--- MODIFICA PRODOTTO ---\n";
    int id = leggiIntero("Inserisci ID del prodotto da modificare: ", 1);
    int indice = trovaIndicePerId(prodotti, id);

    if (indice == -1) {
        cout << "Prodotto non trovato.\n";
        return;
    }

    Prodotto& p = prodotti[static_cast<size_t>(indice)];

    cout << "Prodotto attuale: " << p.nome << '\n';
    p.nome = leggiTesto("Nuovo nome: ");
    p.prezzo = leggiPrezzo("Nuovo prezzo: ");
    p.quantita = leggiIntero("Nuova quantità: ", 0);

    salvaInventario(prodotti);
    cout << "Prodotto modificato correttamente.\n";
}

void eliminaProdotto(vector<Prodotto>& prodotti) {
    cout << "\n--- ELIMINA PRODOTTO ---\n";
    int id = leggiIntero("Inserisci ID del prodotto da eliminare: ", 1);
    int indice = trovaIndicePerId(prodotti, id);

    if (indice == -1) {
        cout << "Prodotto non trovato.\n";
        return;
    }

    cout << "Confermi l'eliminazione di \""
         << prodotti[static_cast<size_t>(indice)].nome << "\"? (s/n): ";

    string conferma;
    getline(cin, conferma);

    if (conferma == "s" || conferma == "S") {
        prodotti.erase(prodotti.begin() + indice);
        salvaInventario(prodotti);
        cout << "Prodotto eliminato correttamente.\n";
    } else {
        cout << "Operazione annullata.\n";
    }
}

void mostraMenu() {
    cout << "\n========================================\n";
    cout << "       INVENTORY MANAGEMENT SYSTEM\n";
    cout << "========================================\n";
    cout << "1. Aggiungi prodotto\n";
    cout << "2. Visualizza prodotti\n";
    cout << "3. Cerca prodotto\n";
    cout << "4. Modifica prodotto\n";
    cout << "5. Elimina prodotto\n";
    cout << "0. Esci\n";
    cout << "----------------------------------------\n";
}
#ifndef UNIT_TEST
int main() {
    vector<Prodotto> prodotti;
    caricaInventario(prodotti);

    cout << "Benvenuto nell'Inventory Management System!\n";
    cout << "Prodotti caricati: " << prodotti.size() << '\n';

    int scelta;

    do {
        mostraMenu();
        scelta = leggiIntero("Seleziona un'opzione: ", 0);

        switch (scelta) {
            case 1:
                aggiungiProdotto(prodotti);
                break;
            case 2:
                visualizzaProdotti(prodotti);
                break;
            case 3:
                cercaProdotto(prodotti);
                break;
            case 4:
                modificaProdotto(prodotti);
                break;
            case 5:
                eliminaProdotto(prodotti);
                break;
            case 0:
                salvaInventario(prodotti);
                cout << "Dati salvati. Uscita dal programma...\n";
                break;
            default:
                cout << "Scelta non valida. Riprova.\n";
        }
    } while (scelta != 0);

    return 0;
}
