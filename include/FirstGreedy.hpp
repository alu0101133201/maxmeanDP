/*
 * Autor: Sergio Guera Arencibia
 * alu0101133201@ull.edu.es
 * Universidad de La Laguna
 * 22-04-20
 * Fichero que describe las clases que implementarán
 * los planteamientos greedy del algoritmo maxmeandp
 */

#pragma once

#include <cfloat>
#include <stdlib.h>
#include <time.h>      

#include "Graph.hpp"
#include "Maxmeandp.hpp"

class FirstGreedy : public Maxmeandp{
  private:
    float getConnectedMax(void);
    float getMax(void);

  public:
    FirstGreedy(Graph);
    ~FirstGreedy();

    float solve();
};
