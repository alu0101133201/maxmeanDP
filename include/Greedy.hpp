/*
 * Autor: Sergio Guera Arencibia
 * alu0101133201@ull.edu.es
 * Universidad de La Laguna
 * 22-04-20
 * Fichero que describe las clases que implementarán
 * los planteamientos greedy del algorimot maxmeandp
 */

#pragma once

#include <climits>
#include <stdlib.h>
#include <time.h>      

#include "Graph.hpp"
#include "Maxmeandp.hpp"

class FirstGreedy : public Maxmeandp{
  private:
    int getConnectedMax(void);
    int getMax(void);

  public:
    FirstGreedy(Graph);
    ~FirstGreedy();

    float solve();
};

class SecondGreedy : public Maxmeandp{
  public:
    SecondGreedy(Graph);
    ~SecondGreedy();
    
    float solve();
};