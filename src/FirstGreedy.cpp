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

float FirstGreedy::getMax(void) {
  float maxValue = FLT_MIN;
  int maxI = -1;
  int maxJ = -1;

  for (int iIter = 0; iIter < workingGraph.getNumberOfNodes(); iIter++) {
    for (int jIter = iIter; jIter < workingGraph.getNumberOfNodes(); jIter++) {
      if (workingGraph.at(iIter, jIter) > maxValue) {
        maxValue = workingGraph.at(iIter, jIter);
        maxI = iIter;
        maxJ = jIter;
      } else if (workingGraph.at(iIter, jIter) == maxValue) {
        int randomNumber = rand() % 2;
        if (randomNumber == 1) {
          maxValue = workingGraph.at(iIter, jIter);
          maxI = iIter;
          maxJ = jIter;  
        }
      }
    }
  }
  bestSolution.push_back(maxI);
  bestSolution.push_back(maxJ);
  return maxValue;
}

float FirstGreedy::getConnectedMax(void) {
  float maxValue = FLT_MIN;
  int maxJ = -1;
  int maxI = -1;

  if (bestSolution.size() == 0) {
    return(getMax());
  } else {
    size_t currentNode = 0;
    for (int iIter = bestSolution[currentNode]; currentNode != bestSolution.size();
        iIter = bestSolution[++currentNode]) {
      for (int jIter = 0; jIter < workingGraph.getNumberOfNodes(); jIter++) {
        if ((workingGraph.at(iIter, jIter) > maxValue) && (!isInSolution(jIter))) {
          maxValue = workingGraph.at(iIter, jIter);
          maxJ = jIter;
          maxI = iIter;
        } else if ((workingGraph.at(iIter, jIter) == maxValue) && (!isInSolution(jIter))) {
          int randomNumber = rand() % 2;
          if (randomNumber == 1) {
            maxValue = workingGraph.at(iIter, jIter);
            maxI = iIter;
            maxJ = jIter;  
          }
        }
      }
    }
  }
  for (size_t iter = 0; iter < bestSolution.size(); iter++) {
    if (bestSolution[iter] != maxI) {
      maxValue += workingGraph.at(bestSolution[iter], maxJ);
    }
  }
  bestSolution.push_back(maxJ);
  return maxValue;
}

float FirstGreedy::solve() {
  float sumValue = getConnectedMax();  
  float auxBestSolutionValue = bestSolutionValue;
  bestSolutionValue = sumValue / 2;  // Numerador
  std::vector<int> auxSolution;
  do {
    auxSolution = bestSolution;
    sumValue += getConnectedMax();    
    auxBestSolutionValue = md(sumValue);
    if (auxBestSolutionValue >= bestSolutionValue)
      bestSolutionValue = auxBestSolutionValue;
    else 
      bestSolution = auxSolution;
  } while((auxSolution != bestSolution) && (bestSolution.size() != workingGraph.getNumberOfNodes()));

  return auxBestSolutionValue;
}