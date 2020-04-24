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
  float minValue = FLT_MAX;
  int minNode = -1;
  
  size_t nodeIter = 0;
  for (int currentNode = bestSolution[nodeIter]; nodeIter != bestSolution.size();
      currentNode = bestSolution[++nodeIter]) {
    for (int jIter = 0; jIter < workingGraph.getNumberOfNodes(); jIter++) {
      if ((workingGraph.at(currentNode, jIter) < minValue) && (isInSolution(jIter))) {
        minValue = workingGraph.at(currentNode, jIter);

        // Selección aleatoria de uno de los dos nodos
        int randomNumber = rand() % 2;
        if (randomNumber == 1) {
          minNode = currentNode;
        } else {
          minNode = jIter;
        }
      } else if ((workingGraph.at(currentNode, jIter) == minValue) && (isInSolution(jIter))) {
        int randomNumber = rand() % 3;
        if (randomNumber == 1) {
          minNode = currentNode;
        } else if (randomNumber == 2){
          minNode = jIter;
        }
      }
    }
  }
  for (std::vector<int>::iterator iter = bestSolution.begin(); iter <= bestSolution.end(); iter++) {
    if (*iter == minNode) {
      bestSolution.erase(iter);
    }
  }
  return minValue;
}
