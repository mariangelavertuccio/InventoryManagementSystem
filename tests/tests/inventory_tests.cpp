
#define UNIT_TEST
#include "../main.cpp"

#include <cassert>
#include <iostream>

using namespace std;

int main() {

    vector<Prodotto> prodotti = {
        {1, "Laptop", 850.50, 5},
        {2, "Mouse", 20.00, 10},
        {3, "Keyboard", 45.00, 3}
    };

    // Test 1: ricerca di un prodotto esistente
    assert(trovaIndicePerId(prodotti, 1) == 0);

    // Test 2: ricerca di un altro prodotto
    assert(trovaIndicePerId(prodotti, 2) == 1);

    // Test 3: ricerca di un prodotto inesistente
    assert(trovaIndicePerId(prodotti, 99) == -1);

    // Test 4: ricerca in un inventario vuoto
    vector<Prodotto> inventarioVuoto;
    assert(trovaIndicePerId(inventarioVuoto, 1) == -1);

    cout << "All tests passed successfully!" << endl;

    return 0;
}
