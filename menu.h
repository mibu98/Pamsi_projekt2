#ifndef MENU_H_
#define MENU_H_

//#include "graf_lista.h"
#include "graf_macierz.h"

void show_menu() {
  cout << "\n0. Zakoncz menu - przejdz do sekcji pomiarowej " << endl;
  cout << "1. Wyswietl parametry" << endl;
  cout << "2. Zapisz" << endl;
  cout << "3. Wczytaj" << endl;
  cout << "4. Wypelnij graf" << endl;
  cout << "5. Usun zawartosc" << endl;
  cout << "6. Wyswietl menu" << endl;
}

void menu(graph &graf) {
  int option;
  show_menu();
  do {
    cout << "Twoja opcja: ";
    cin >> option;

    switch (option) {
    case 0:
      break;

    case 1:
      graf.show_variables();
      break;

    case 2:
      graf.save_name(const_cast<char *>("lista_dane.txt"));
      break;

    case 3:
      graf.read();
      break;

    case 4:
      graf.remove_all();
      graf.fill_graph();
      break;

    case 5:
      graf.remove_all();
      break;

    case 6:
      show_menu();
      break;

    default:
      break;
    }
  } while (option != 0);
}

#endif
