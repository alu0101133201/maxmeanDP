/*
 * Autor: Sergio Guera Arencibia
 * alu0101133201@ull.edu.es
 * Universidad de La Laguna
 * 22-04-20
 * Fichero que describe la clase que implementará
 * el algoritmo GRASP
 */

#pragma once

#include <cfloat>
#include <stdlib.h>
#include <time.h>   

#include "Graph.hpp"
#include "Maxmeandp.hpp"

class Grasp : public Maxmeandp {
  private:
    std::vector<int> LRC;
    int cardinality;

    float construct();
    void buildLRC();

  public:
    Grasp(Graph, int);
    ~Grasp();

    float solve();
};