/*
 * Autor: Sergio Guera Arencibia
 * alu0101133201@ull.edu.es
 * Universidad de La Laguna
 * 22-04-20
 * Fichero que implementa las clases que implementarán
 * los planteamientos greedy del algorimot maxmeandp
 */

#include "SecondGreedy.hpp"


SecondGreedy::SecondGreedy(Graph workingGraph):
    Maxmeandp(workingGraph) {}

void SecondGreedy::buildInitialSolution(void) {
  for (int iter = 0; iter < workingGraph.getNumberOfNodes(); iter++)
    bestSolution.push_back(iter);
}

float SecondGreedy::solve() {
  buildInitialSolution();
  bestSolutionValue = mdFromSet(bestSolution);
  float auxBestSolutionValue = bestSolutionValue;
  std::vector<int> auxSolution;

  do {
    auxSolution = bestSolution;
    deleteWorstNode();
    auxBestSolutionValue = mdFromSet(bestSolution);
    if (auxBestSolutionValue >= bestSolutionValue)
      bestSolutionValue = auxBestSolutionValue;
    else 
      bestSolution = auxSolution;
  } while(auxSolution != bestSolution);

  return auxBestSolutionValue;
}

float SecondGreedy::deleteWorstNode() {
  int minValue = INT_MAX;
  int minJ = -1;
  int minI = -1;

  size_t currentNode = 0;
  for (int iIter = bestSolution[currentNode]; currentNode != bestSolution.size();
      iIter = bestSolution[++currentNode]) {
    for (int jIter = 0; jIter < workingGraph.getNumberOfNodes(); jIter++) {
      if ((workingGraph.at(iIter, jIter) < minValue) && (isInSolution(jIter))) {
        minValue = workingGraph.at(iIter, jIter);
        minJ = jIter;
        minI = iIter;
      } else if ((workingGraph.at(iIter, jIter) == minValue) && (isInSolution(jIter))) {
        int randomNumber = rand() % 2;
        if (randomNumber == 1) {
          minValue = workingGraph.at(iIter, jIter);
          minJ = jIter;
          minI = iIter; 
        }
      }
    }
  }
  for (auto iter = bestSolution.begin(); iter != bestSolution.end(); iter++) {
    if (*iter == minValue)
      bestSolution.erase(iter);
  }
  return minValue;
}
