#ifndef GRAF_LISTA_H_
#define GRAF_LISTA_H_

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
  vector<vector<int> > list;
  vector<vector<int> > wage;

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
    vector<int> temp;

    for (int i = 0; i < vertex; i++)
      wage.push_back(temp);

    for (int i = 0; i < vertex; i++)
      list.push_back(temp);
  }

  void fill_graph() {
    int temp = connections;
    int **matrix;
    matrix = new int *[list.size()];
    for (int i = 0; i < vertex; i++)
      matrix[i] = new int[vertex]{0};

    if (density < 1) {
      while (temp) {
        int i = rand() % vertex;
        int j = rand() % vertex;
        if (i != j) {
          if (j > i && !matrix[i][j]) {
            temp--;
            matrix[i][j] = 1 + rand() % 500;
          } else if (i > j && !matrix[j][i]) {
            temp--;
            matrix[j][i] = 1 + rand() % 500;
          }
        }
      }
    } else {
      for (int i = 0; i < vertex; i++)
        for (int j = 0; j < vertex; j++)
          if (j > i)
            matrix[i][j] = 1 + rand() % 500;
    }

    int con_new = 0;
    for (int i = 0; i < vertex; i++)
      for (int j = 0; j < vertex; j++) {
        if (matrix[i][j]) {
          con_new++;
          list[i].push_back(j);
          list[j].push_back(i);
          wage[i].push_back(matrix[i][j]);
          wage[j].push_back(matrix[i][j]);
        }
      }
    connections = con_new;
    for (int i = 0; i < vertex; i++)
      delete matrix[i];

    delete matrix;
  }

    void remove_all() {
      for (unsigned int i = 0; i < list.size(); i++) {
        list[i].clear();
        wage[i].clear();
      }
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
        for (unsigned int j = 0; j < list[i].size(); j++) {
          plik << i << " " << list[i][j] << " " << wage[i][j] << endl;
        }
      }

      cout << "Zapisano pomyslnie" << endl;
    } else
      cout << "Blad zapisu" << endl;

    plik.close();
  }

  void read() {
    vector<int> get;
    fstream plik;
    int temp;

    plik.open("dane_lista.txt", ios::in);
    if (plik.good()) {
      do {
        plik >> temp;
        get.push_back(temp);
      } while (!plik.eof());

      std::cout << "Odczytano pomyslnie" << std::endl;
    } else
      std::cout << "Blad odczytu" << std::endl;

    plik.close();

    connections = get.size() / 5;

    for (int i = 0; i < vertex; i++)
      for (unsigned int j = 0; j < list[i].size(); j++) {
        list[i].clear();
        wage[i].clear();
      }

    if (!(get.size() % 3))
      for (unsigned int i = 0; i < get.size(); i += 3) {
        unsigned int t1, t2, t3;
        t1 = get[i];
        t2 = get[i + 1];
        t3 = get[i + 2];

        while (list.size() < (t1 + 1)) {
          vector<int> v;
          list.push_back(v);
          wage.push_back(v);
        }

        list[t1].push_back(t2);
        wage[t1].push_back(t3);
      }

    vertex = list.size();
    density = connections * 2 / (vertex * (vertex - 1));
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

  void show_vector(vector<int> &v) {
    int k = v.size();

   for (int i = 0; i < k; i++)
      cout << i << ".  " << v[i] << endl;
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

    for (unsigned int i = 0; i < list.size(); i++) {
      temp.len = len[i];
      temp.nr1 = i;
      temp.nr2 = -1;
      prior.push_back(temp);
    }
    sort_node(prior);

    do {
      temp = prior[0];
      prior.erase(prior.begin());

      for (unsigned int i = 0; i < list[temp.nr1].size();
           i++)
      {
        if ((len[temp.nr1] + wage[temp.nr1][i]) < len[list[temp.nr1][i]])
          len[list[temp.nr1][i]] = len[temp.nr1] + wage[temp.nr1][i];
      }

    } while (prior.size());

    return 0;
  }
};

#endif
