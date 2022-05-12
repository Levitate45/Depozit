#include <iostream>
#include <string.h>
#include <ios>
#include <limits>
#include <fstream>

using namespace std;

fstream db("db.txt");

struct itemEntry
{
    float unit_price;
    int copies, product_id;
    char name[30];
    char company[30];
};

class Store {
  public:
      int numItem;
      itemEntry database[100];

      Store() {
        numItem = 0;
      }
      void insertItem(char itemName[], char company[], int pid, int c, float p);
      void deleteItem(char itemName[], int pid);
      itemEntry *searchItem(char itemName[], int pid);
      void updateItem(char itemName[], int pid, int total, float price);
};

void Store::insertItem(char itemName[], char company[], int pid, int c, float p) {
    strcpy(database[numItem].name, itemName);
    strcpy(database[numItem].company, company);
    database[numItem].product_id = pid;
    database[numItem].copies = c;
    database[numItem].unit_price = p;

    // Introdu valorile in db.txt.
    db << "Nume:" << database[numItem].name << ",";
    db << "Companie:" << database[numItem].company << ",";
    db << "Numar:" << database[numItem].product_id << ",";
    db << "Bucati:" << database[numItem].copies << ",";
    db << "Pret:" << database[numItem].unit_price << ",";
    db << ";" << endl;

    cout << ":: InsertItem() = Obiect adaugat cu succes. \n";
    numItem++;
}

void Store::deleteItem(char itemName[], int pid) {
    int i;
    for (i = 0; i < numItem; i++)
    {
      if ((strcmp(itemName, database[i].name) == 0) && (database[i].product_id == pid))
      {
        database[i].copies--;
        cout << ":: DeleteItem() = Obiect sters cu succes. \n";
        return;
      }
    }
    cout << ":: DeleteItem() Error = Obiect negasit. \n";
}

itemEntry *Store::searchItem(char itemName[], int pid) {
    int i;
    for (i = 0; i < numItem; i++)
    {
      if ((strcmp(itemName, database[i].name) == 0) && (database[i].product_id == pid))
        cout << ":: SearchItem() = Obiect gasit cu succes. \n";

        return &database[i];
    }
    return NULL;
}

void Store::updateItem(char itemName[], int pid, int total, float price) {
    itemEntry *item = searchItem(itemName, pid);
    if (item != NULL)
    {
      cout << ":: UpdateItem() = Obiect actualizat cu succes. \n";

      item->copies += total;
      item->unit_price += price;
    } else {
      cout << ":: UpdateItem() Error = Obiectul nu a fost gasit."<<endl;
    }
}

void menuAddProduct(Store sto, char name[], char company[], int product_id, int copies, float unit_price) {
    cin.getline(name, 80);
    cout << "Nume produs:";
    cin.getline(name, 80);

    cout << "Nume companie:";
    cin.getline(company, 80);

    cout << "ID:";
    // Verificare citire de la tastatura pentru valori invalide.
    while (!(cin >> product_id)) {
      cout << "\n ERROR: Valoare incorecta. Introdu un numar.";
      cout << "\n";
      cin.clear(); // Eliberare buffer pentru urmatorul cin.
      cin.ignore(numeric_limits<streamsize>::max(),'\n');
    };
    cout << "Bucati : ";
    while (!(cin >> copies)) {
      cout << "ERROR: Valoare incorecta. Introdu un numar.";
      cout << " ";
      cin.clear(); // Eliberare buffer pentru urmatorul cin.
      cin.ignore(numeric_limits<streamsize>::max(),'\n');
    };

    cout << "PRET PER BUCATA : ";
    while (!(cin >> unit_price)) {
      cout << "ERROR: Valoare incorecta. Introdu un numar.";
      cout << " ";
      cin.clear(); // Eliberare buffer pentru urmatorul cin.
      cin.ignore(numeric_limits<streamsize>::max(),'\n');
    };

    sto.insertItem(name, company, product_id, copies, unit_price);
}

void menuDeleteProduct(Store sto, char name[], int product_id) {
    cin.getline(name, 80);
    cout << "NUME : ";
    cin.getline(name, 80);
    db << name << endl;

    cout << "NUMAR REZERVAT : ";
    while (!(cin >> product_id)) {
      cout << "ERROR: Valoare incorecta. Introdu un numar.";
      cout << " ";
      cin.clear(); // Eliberare buffer pentru urmatorul cin.
      cin.ignore(numeric_limits<streamsize>::max(),'\n');
    };
    db << product_id << endl;

    sto.deleteItem(name, product_id);
}

void menuSearchProduct(Store sto, char name[], int product_id) {
    cin.getline(name, 80);
    cout << "\n NUME : ";
    cin.getline(name, 80);
    db << name << endl;

    cout << "\n NUMAR REZERVAT : ";
    while (!(cin >> product_id)) {
      cout << "\n ERROR: Valoare incorecta. Introdu un numar.";
      cout << "\n";
      cin.clear(); // Eliberare buffer pentru urmatorul cin.
      cin.ignore(numeric_limits<streamsize>::max(),'\n');
    };
    db << product_id << endl;

    itemEntry *test;
    test = sto.searchItem(name, product_id);
    if (test != NULL)
    {
      cout << "\n\t------------->REZULTAT<--------------";
      cout << "\n   OBIECT GASIT"
          << "\n NUME:" << test->name << "\n\t\t\t COMPANIE :"
          << test->company << "\n\t\t\t NUMAR REZERVAT:" << test->product_id
          << "\n BUCATI:" << test->copies
          << "\n PRET PER BUCATA:" << test->unit_price;
    }
    else
      cout << "\n OBIECT NEGASIT";
}

void menuUpdateProduct(Store sto, char name[], int product_id, int copies, int unit_price) {
    cout << "\n INTRODUCETI DATELE : ";
    cin.getline(name, 80);
    cout << "\n NUME : ";
    cin.getline(name, 80);
    db << name << endl;

    cout << "\n NUMAR REZERVAT : ";
    while (!(cin >> product_id)) {
      cout << "\n ERROR: Valoare incorecta. Introdu un numar.";
      cout << "\n";
      cin.clear(); // Eliberare buffer pentru urmatorul cin.
      cin.ignore(numeric_limits<streamsize>::max(),'\n');
    };
    db << product_id << endl;

    cout << "\n NOUL NUMAR DE BUCATI : ";
    while (!(cin >> copies)) {
      cout << "\n ERROR: Valoare incorecta. Introdu un numar.";
      cout << "\n";
      cin.clear(); // Eliberare buffer pentru urmatorul cin.
      cin.ignore(numeric_limits<streamsize>::max(),'\n');
    };
    db << copies << endl;

    cout << "\n NOUL PRET PER BUCATA : ";
    while (!(cin >> unit_price)) {
      cout << "\n ERROR: Valoare incorecta. Introdu un numar.";
      cout << "\n";
      cin.clear(); // Eliberare buffer pentru urmatorul cin.
      cin.ignore(numeric_limits<streamsize>::max(),'\n');
    };
    db << unit_price << endl;

    sto.updateItem(name, product_id, copies, unit_price);
}

int main()
{
    fstream db;
    db.open("db.txt", ios::out);
    Store sto;
    char name[30], company[30];
    int product_id, copies, unit_price, option;
    option = 0;
    char parola[50]="1234",z[50],c=0;
    while(c<3)
    {
    cout<<"Introdu parola:"<<endl;
    cin>>z;
    if(strcmp(parola,z)==0)
    { while (option != -1)
      {
        cout << "### MENIU MAGAZIN ### \n";
        cout << "Introdu '1' pentru a adauga date. \n";
        cout << "Introdu '2' pentru a sterge date. \n";
        cout << "Introdu '3' pentru a cauta date. \n";
        cout << "Introdu '4' pentru a actualiza date. \n";
        cout << "Introdu '-1' pentru a iesi din meniu. \n";
        cout << "Optiunea: \n";

        // Verifica fiecare citire de la tastatura. Daca option nu e numar intreg, notifica utilizatorul si cere-i alta valoare.
        if (cin >> option) switch (option)
        {
        case 1:
          menuAddProduct(sto, name, company, product_id, copies, unit_price);
          break;

        case 2:
          menuDeleteProduct(sto, name, product_id);
          break;

        case 3:
          menuSearchProduct(sto, name, product_id);
          break;

        case 4:
          menuUpdateProduct(sto, name, product_id, copies, unit_price);
          break;
        case -1:
          cout << "Multumim ca ati folosit serviciul." << endl;
          break;
        }
        // Error handling in cazul in care option nu e int.
        else {
          cout << "ERROR: Optiune invalida. Alege o optiune existenta." << endl;
          cin.clear(); // Eliberare buffer pentru urmatorul cin.
          cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
      }
    return 0;
    }
    else
    {cout<<"Parola incorecta!"<<endl;
      c++;

    if(c==3) cout<<"Nu mai aveti incercari.";
    }
    }
    }
