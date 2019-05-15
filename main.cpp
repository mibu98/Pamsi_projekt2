//#include "graf_lista.h"
#include "graf_macierz.h"

// by zmienic reprezentacje grafu, nalezy odkomentowac jedno z powyzszych i zakomentowac drugie, TAK SAMO w pliku "menu.h"

#include "menu.h"

//WYKONAL: Michal Burda 241484
//Graf na ocene 5 - z badaniem algorytmu Dijkstry


struct pomiar {
  int v; //ilosc wierzcholkow
  float d; //gestosc
  double t; // czas
};

int main() {
  srand(time(NULL));

  // czesc poswiecona badaniu grafu w menu

  int vertex = 100;
  float density = 0.5;
  graph graf(vertex, density);
  menu(graf);


  { //czesc poswiecona badaniu algorytmu Dijkstry
    int times = 0;
    clock_t t1, t2;
    float dens[4] = {0.25, 0.5, 0.75, 1};
    int vert[5] = {50, 100, 200, 300, 500};

    vector<pomiar> dane;
    vector<int> how_long;

    for(int i = 0; i < 5; i++)//vert
    for(int j = 0; j < 4; j++)//dens
    {
    do {

      graph graf(vert[i], dens[j]);
      graf.fill_graph();

        int wierzcholek = rand() % vert[i];
        t1 = t2 = clock();
        graf.dijkstra(wierzcholek);
        t2 = clock();
        how_long.push_back(t2-t1);
        times++;

    } while (times < 100);

    double average = 0;

    for (int a = 0; a < times; a++)
      average += how_long[a]/(double)CLOCKS_PER_SEC;  // Do pomiaru czasu

    how_long.clear();
    pomiar temp;
    temp.t = average;
    temp.d = dens[j];
    temp.v = vert[i];
    dane.push_back(temp);
    times=0;
     }

     for(unsigned int b = 0; b < dane.size(); b++)
     {
       cout << "Wierzcholki \t" << dane[b].v << "; \tGestosc \t" << dane[b].d << "; \tCzas \t" << dane[b].t << endl;
     }
  }

  return 0;
}
