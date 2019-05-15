#ifndef GRAF_MACIERZ_H_
#define GRAF_MACIERZ_H_

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <fstream>
#include <math.h>

struct node {
  int nr1;
  int nr2;
  int len;
};

class variables {
public:
  int vertex;
  float density;
  int connections;
};

using namespace std;

class graph : public variables {
  int **matrix;

public:
  graph() {
    vertex = 0;
    density = 0;
    connections = 0;
  }

  graph(int vert, float dens) {
    vertex = vert;
    density = dens;
    connections = density * vertex * (vertex - 1) / 2;

    matrix = new int *[vertex];
    for (int i = 0; i < vertex; i++)
      matrix[i] = new int[vertex];

    for (int i = 0; i < vertex; i++)
      for (int j = 0; j < vertex; j++)
        matrix[i][j] = 0;
  }

  void fill_graph() {
    int temp = connections;

    if (density < 1) {
      while (temp) {
        int i = rand() % vertex;
        int j = rand() % vertex;
          if (j > i && !matrix[i][j]) {
            temp--;
            matrix[i][j] = 1 + rand() % 500;
          }
          else if (i > j && !matrix[j][i]) {
            temp--;
            matrix[j][i] = 1 + rand() % 500;
          }
      }
    }
    else {
      for (int i = 0; i < vertex; i++)
        for (int j = 0; j < vertex; j++)
          if (j > i)
            matrix[i][j] = 1 + rand() % 500;
    }

    int con_new = 0;
    for (int i = 0; i < vertex; i++) {
      for (int j = 0; j < vertex; j++) {
        if (matrix[i][j] != 0)
          con_new++;
      }
    }
    connections = con_new;
  }

  void remove_all() {
    for (int i = 0; i < vertex; i++)
      for (int j = 0; j < vertex; j++)
        matrix[i][j] = 0;
  }

  void show_variables() {
    cout << "Twoj graf:" << endl;
    cout << vertex << " wierzcholkow" << endl;
    cout << density << " wypelnienia" << endl;
    cout << connections << " polaczen" << endl;
  }

  void save_name(char *name) {
    fstream plik;
    plik.open(name, ios::out);
    if (plik.good()) {
      for (int i = 0; i < vertex; i++) {
        for (int j = 0; j < vertex; j++) {
          plik << matrix[i][j] << " ";
        }
        plik << "\n";
      }
      std::cout << "Zapisano pomyslnie" << std::endl;
    } else
      std::cout << "Blad zapisu" << std::endl;

    plik.close();
  }

  void read() {
    vector<int> get;
    fstream plik;
    int temp;
    plik.open("dane.txt", ios::in);
    if (plik.good()) {
      do {
        plik >> temp;
        get.push_back(temp);
      } while (!plik.eof());

      std::cout << "Odczytano pomyslnie" << std::endl;
    } else
      std::cout << "Blad odczytu" << std::endl;

    plik.close();
    get.pop_back();

    int number = get.size();
    int elements = sqrt(number);

    delete matrix;
    matrix = new int *[elements];
    for (int i = 0; i < elements; i++)
      matrix[i] = new int[elements];

    for (int i = 0; i < elements; i++)
      for (int j = 0; j < elements; j++)
        matrix[i][j] = get[elements * i + j];

    number = 0;
    for (int i = 0; i < elements; i++)
      for (int j = 0; j < elements; j++)
        if (matrix[i][j])
          number++;

    connections = number;
    vertex = elements;
    density = connections * 2;
    density /= vertex * (vertex - 1);
  }

  void quicksort_node(vector<node> &tab, int first, int last) {
    int i = first;
    int j = last;
    int temp;

    int pivot = tab[(first + last) / 2].len;

    do {
      while (tab[i].len < pivot)
        i++;

      while (tab[j].len > pivot)
        j--;

      if (i <= j) {
        temp = tab[i].nr1;
        tab[i].nr1 = tab[j].nr1;
        tab[j].nr1 = temp;

        temp = tab[i].nr2;
        tab[i].nr2 = tab[j].nr2;
        tab[j].nr2 = temp;

        temp = tab[i].len;
        tab[i].len = tab[j].len;
        tab[j].len = temp;

        i++;
        j--;
      }
    } while (i <= j);

    if (first < j)
      quicksort_node(tab, first, j);
    if (i < last)
      quicksort_node(tab, i, last);
  }

  void sort_node(vector<node> &tab) {
    if (tab.size())
      quicksort_node(tab, 0, tab.size() - 1);
  }

  int dijkstra(int vert) {
    // lista odleglosci
    vector<int> len;

    for (int i = 0; i < vertex; i++) {
      len.push_back(1000000); // nieskonczonosc
    }
    len[vert] = 0;

    // kolejka priorytetowa wierzcholkow, bedzie sortowana wg odleglosci
    vector<node> prior;
    node temp;

    for (int i = 0; i < vertex; i++) {
      temp.len = len[i];
      temp.nr1 = i;
      temp.nr2 = -1;
      prior.push_back(temp);
    }
    sort_node(prior);

    do {
      temp = prior[0];
      prior.erase(prior.begin());

      for (int i = 0; i < vertex; i++)
      {
        if (matrix[i][temp.nr1])
          if ((len[temp.nr1] + matrix[i][temp.nr1]) < len[i]) {
            len[i] = len[temp.nr1] + matrix[i][temp.nr1];
          }

        if (matrix[temp.nr1][i])
          if ((len[temp.nr1] + matrix[temp.nr1][i]) < len[i]) {
            len[i] = len[temp.nr1] + matrix[temp.nr1][i];
          }
      }

    } while (prior.size());

    return 0;
  }
};

#endif
