/*
 * Autor: Sergio Guera Arencibia
 * alu0101133201@ull.edu.es
 * Universidad de La Laguna
 * 22-04-20
 * Fichero que describe las clases que implementarán
 * los planteamientos greedy del algoritmo maxmeandp
 */

#pragma once

#include <stdlib.h>
#include <time.h>      

#include "Graph.hpp"
#include "Maxmeandp.hpp"

// Clase que implementa el primer algoritmo voraz
class FirstGreedy : public Maxmeandp {
  private:
    // Método que obtiene la arista con mayor afinidad del grafo
    float getBestMean(void);

  public:
    FirstGreedy(Graph);
    ~FirstGreedy();

    // Algoritmo principal de resolución
    float solve();
};
