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



class VNS : public Maxmeandp { 
  private:
    Grasp myGrasp;

  void shake(std::vector<int> currentSolution, float currentValue, int numberOfChanges);
  void mainVNS(std::vector<int>& currentSolution, float& currentValue);

  public:
    VNS(Graph workingGraph, int numberOfCardinality, int stopCriteria, int maxIterations,
        int typeLocal, int environment);
    ~VNS();

    float solve();
};