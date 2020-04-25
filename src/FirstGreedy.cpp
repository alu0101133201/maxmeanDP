/*
 * Autor: Sergio Guera Arencibia
 * alu0101133201@ull.edu.es
 * Universidad de La Laguna
 * 22-04-20
 * Fichero que implementa las clases que implementarán
 * los planteamientos greedy del algorimot maxmeandp
 */

#include "FirstGreedy.hpp"

FirstGreedy::FirstGreedy(Graph workingGraph):
    Maxmeandp(workingGraph) {
  srand (time(NULL));
}

float FirstGreedy::getBestMean(void) {

  if (bestSolution.size() == 0) {
    return(getMax());
  } else {
    std::vector<int> bestSolutionAux = bestSolution;
    float bestValue = FLT_MIN;
    int bestNode;


    for (int nodeIter = 0; nodeIter < workingGraph.getNumberOfNodes(); nodeIter++) {
      if (!isInSolution(nodeIter)) {
        float currentValue;

        bestSolutionAux.push_back(nodeIter);
        currentValue = mdaddNode(bestSolutionValue, bestSolutionAux, nodeIter);

        if (bestValue < currentValue) {
          bestValue = currentValue;
          bestNode = nodeIter;
        } else if (currentValue == bestValue) {
          int randomNumber = rand() % 2;
          if (randomNumber == 1) {
            bestValue = currentValue;
            bestNode = nodeIter;
          }
        }
        bestSolutionAux.pop_back();
      }
    }

  bestSolution.push_back(bestNode);
  return bestValue;
  }
}

float FirstGreedy::solve() {
  bestSolutionValue = getBestMean();  
  float auxBestSolutionValue = bestSolutionValue;
  std::vector<int> auxSolution;

  do {
    auxSolution = bestSolution;
    float currentMean = getBestMean();

    if (bestSolutionValue >= currentMean) {
      bestSolution = auxSolution;
    } else {
      bestSolutionValue = currentMean;
    }
  } while((auxSolution != bestSolution) && (bestSolution.size() != workingGraph.getNumberOfNodes()));
  return auxBestSolutionValue;
}
