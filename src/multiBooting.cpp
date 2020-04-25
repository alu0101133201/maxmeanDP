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

void MultiBooting::generateRandom() {
  int solutionSize = (rand() % (workingGraph.getNumberOfNodes() - 2)) + 2;
  bestSolution.clear();
  
  for (int nodeIter = 0; nodeIter < solutionSize; nodeIter++) {
    int randomNumber = rand() % workingGraph.getNumberOfNodes();
    if (!isInSolution(randomNumber))
      bestSolution.push_back(randomNumber);
  }
  bestSolutionValue = mdFromSet(bestSolution);
}

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