/*
 * Autor: Sergio Guera Arencibia
 * alu0101133201@ull.edu.es
 * Universidad de La Laguna
 * 22-04-20
 * Fichero que describe la clase de la modificación
 * un algoritmo VNS
 */

#pragma once

#include <cfloat>
#include <stdlib.h>
#include <time.h>  
#include <utility> 
#include <iterator>

#include "Graph.hpp"
#include "Grasp.hpp"
#include "Maxmeandp.hpp"

// ----------- MODIFICACIÓN ---------------
// ----------------------------------------

// Clase que implementa un algoritmo de resolución VNS
class Mod : public Maxmeandp { 
  private:
    Grasp myGrasp;  // Atributo Grasp para la generación de soluciones iniciales

    float mainLoopSolution(std::vector<int>& currentSolution, float& currentValue);
    // Nos generará la solución aleatoria en S'
    void shake(std::vector<int> currentSolution, float currentValue, int numberOfChanges);

  public:
    Mod(Graph workingGraph, int numberOfCardinality, int stopCriteria, int maxIterations,
        int typeLocal, int environment);
    ~Mod();

    // Método principal de resolución
    float solve();
};