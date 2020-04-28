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

// Clase que implementa un algoritmo multiarranque
class MultiBooting : public Maxmeandp {    
  public:
    MultiBooting(Graph workingGraph, int stopCriteria, int maxIterations,
        int typeLocal, int environment);
    ~MultiBooting();

    // Método básico de resolución 
    float solve();
};