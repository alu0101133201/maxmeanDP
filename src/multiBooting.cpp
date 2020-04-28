/*
 * Autor: Sergio Guera Arencibia
 * alu0101133201@ull.edu.es
 * Universidad de La Laguna
 * 22-04-20
 * Fichero que implemento la clase abstracta multibooting.
 */

#include "multiBooting.hpp"

MultiBooting::MultiBooting(Graph workingGraph, int stopCriteria, int maxIterations,
        int typeLocal, int environment):
  Maxmeandp(workingGraph) {
  // Condición de parada
  stopCriteria_ = stopCriteria;
  iterationLimit = maxIterations;

  // Búsqueda local
  localType = typeLocal;
  envirnomentType = environment;
  srand(time(NULL));
}

MultiBooting::~MultiBooting() {}

float MultiBooting::solve() {
  int iteration = 0;
  std::vector<int> bestMultiBootSolution;
  float bestMultiBootValue = FLT_MIN;

  do {
    generateRandom();
    postProcessing();

    if (bestSolutionValue > bestMultiBootValue) {
      bestMultiBootValue = bestSolutionValue;
      bestMultiBootSolution = bestSolution;
      iterationsWithOutImprove = 0;
    } else {
      iterationsWithOutImprove++;
    }
    iteration++;
  } while(!stopCriteria(iteration));
  
  bestSolution = bestMultiBootSolution;
  bestSolutionValue = bestMultiBootValue;
  return bestSolutionValue;
}