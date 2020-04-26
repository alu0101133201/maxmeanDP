/*
 * Autor: Sergio Guera Arencibia
 * alu0101133201@ull.edu.es
 * Universidad de La Laguna
 * 22-04-20
 * Fichero que describe la clase abstracta multibooting.
 */

#pragma once

#include <iostream>
#include "Maxmeandp.hpp"

class MultiBooting : public Maxmeandp {
  private:
    // void generateRandom();
    
  public:
    MultiBooting(Graph workingGraph, int stopCriteria, int maxIterations,
        int typeLocal, int environment);
    ~MultiBooting();

    float solve();
};