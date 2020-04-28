/*
 * Autor: Sergio Guera Arencibia
 * alu0101133201@ull.edu.es
 * Universidad de La Laguna
 * 22-04-20
 * Fichero que describe la clase que implementará
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


// Clase que implementa un algoritmo de resolución VNS
class VNS : public Maxmeandp { 
  private:
    Grasp myGrasp;  // Atributo Grasp para la generación de soluciones iniciales

  // Método que nos genera una solución en el anillo del entorno
  void shake(std::vector<int> currentSolution, float currentValue, int numberOfChanges);
  // Método que nos genera una solución mendiante VNS
  void mainVNS(std::vector<int>& currentSolution, float& currentValue);

  public:
    VNS(Graph workingGraph, int numberOfCardinality, int stopCriteria, int maxIterations,
        int typeLocal, int environment);
    ~VNS();

    // Método principal de resolución
    float solve();
};