/*
 * Autor: Sergio Guera Arencibia
 * alu0101133201@ull.edu.es
 * Universidad de La Laguna
 * 22-04-20
 * Fichero que describe la clase abstracta maxmeandp. Esta 
 * sera la clase padre de diferentes clases que implementarán
 * un algoritmo de resolución para el problema
 */

#include "Maxmeandp.hpp"






Maxmeandp::Maxmeandp(Graph myGraph):
  iterationsWithOutImprove(0) {
  workingGraph = myGraph;
}

Maxmeandp::~Maxmeandp() {};

std::vector<int> Maxmeandp::getBestSolution() {
  return(bestSolution);
}

int Maxmeandp::getBestSoluctionValue() {
  return(bestSolutionValue);
}

float Maxmeandp::md(float numerator) {
  return(numerator / (float)bestSolution.size());
}

bool Maxmeandp::isInSolution(int node) {
  for (size_t iter = 0; iter < bestSolution.size(); iter++) {
    if (bestSolution[iter] == node) 
      return true;
  }
  return false;
}

float Maxmeandp::getSolutionValue() {
  return(bestSolutionValue);
}

std::vector<int> Maxmeandp::getSolution() {
  return(bestSolution);
}

float Maxmeandp::mdFromSet(std::vector<int> nodeSet) {
  float ValueSum = 0;

  for (size_t iter = 0; iter < nodeSet.size(); iter++) {
    for (size_t secondIter = iter + 1; secondIter < nodeSet.size(); secondIter++) {
      ValueSum += workingGraph.at(nodeSet[iter], nodeSet[secondIter]);
    }
  }
  return ValueSum / nodeSet.size();
}

float Maxmeandp::mdaddNode(float currentValue, std::vector<int> nodeSet, int node) {
  float addingNumerator = 0;
  for (int nodeIter = 0; nodeIter < nodeSet.size(); nodeIter++) {
    if (nodeSet[nodeIter] != node)
      addingNumerator += workingGraph.at(nodeSet[nodeIter], node);
  }
  return (((currentValue * (nodeSet.size() - 1)) + addingNumerator) / nodeSet.size());
}


float Maxmeandp::mdsubNode(float currentValue, std::vector<int> nodeSet, int node) {
  float addingNumerator = 0;
  for (int nodeIter = 0; nodeIter < nodeSet.size(); nodeIter++) {
      addingNumerator += workingGraph.at(nodeSet[nodeIter], node);
  }
  return (((currentValue * (nodeSet.size() + 1)) - addingNumerator) / nodeSet.size());
}


float Maxmeandp::getMax(void) {
  bestSolution.clear();
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
  return maxValue / 2.0;
}

void Maxmeandp::generateRandom() {
  int solutionSize = (rand() % (workingGraph.getNumberOfNodes() - 2)) + 2;
  bestSolution.clear();
  
  for (int nodeIter = 0; nodeIter < solutionSize; nodeIter++) {
    int randomNumber = rand() % workingGraph.getNumberOfNodes();
    if (!isInSolution(randomNumber))
      bestSolution.push_back(randomNumber);
  }
  bestSolutionValue = mdFromSet(bestSolution);
}

bool Maxmeandp::stopCriteria(int currentIterations) {
  switch(stopCriteria_) {
    case (ITERACIONES):
      if (currentIterations >= iterationLimit)
        return true;
      break;
    case (SINMEJORA):
      if (iterationsWithOutImprove >= iterationLimit)
        return true;
      break;
    default:
      throw "Caso inválido\n";
      break;
  }
  return false;
}

void Maxmeandp::greedyLocalSearch() {
  std::vector<int> newSolution;
  std::vector<int> currentSolution = bestSolution;
  float currentValue = bestSolutionValue;
  float auxValue;
  bool updateFlag;

  do {
    updateFlag = false;
    for (int nodeIter = 0; nodeIter < workingGraph.getNumberOfNodes(); nodeIter++) {
      newSolution = generateNeighbour(nodeIter);
      auxValue = mdFromSet(newSolution);

      if (auxValue > currentValue) {
        currentSolution = newSolution;
        currentValue = auxValue;
        updateFlag = true;
      }
    }
    bestSolution = currentSolution;
    bestSolutionValue = currentValue;
  } while (updateFlag);
}


void Maxmeandp::postProcessing() {
  switch (localType) {
    case (GREEDY):
      greedyLocalSearch();
      break;
    case (ANXIOUS):
      anxiousLocalSearch();
      break;
    default:
      throw "Invalid case - postProcessing\n";
  }
}

void Maxmeandp::anxiousLocalSearch() {
  std::vector<int> newSolution;
  float auxValue;

  for (int nodeIter = 0; nodeIter < workingGraph.getNumberOfNodes(); nodeIter++) {
    newSolution = generateNeighbour(nodeIter);
    auxValue = mdFromSet(newSolution);

    if (auxValue > bestSolutionValue) {
      bestSolution = newSolution;
      bestSolutionValue = auxValue;
      break;
    }
  }
}

std::vector<int> Maxmeandp::generateNeighbour(int node) {
  std::vector<int> neighbourSolution = bestSolution;

  switch(envirnomentType){
    case (OPEN):
      if (!isInSolution(node)) {
        neighbourSolution.push_back(node);
      }
      break;
    case (CLOSE):
      if (isInSolution(node)) {
        for (auto iter = neighbourSolution.begin(); iter <= neighbourSolution.end(); iter++) {
          if (*iter == node) {
            neighbourSolution.erase(iter);
            break;
          }
        }  
      }
      break;
    default:
      throw "Invalid case\n";
  }
  return neighbourSolution;
}


std::ostream& Maxmeandp::write(std::ostream& os) {
  os << "Maxmeandp aplicado sobre la siguiente matriz: \n";
  workingGraph.write(std::cout);
  os << "\nEl mejor valor obtenido es: " << bestSolutionValue << "\n";
  os << "El cjto de nodos solución es: ";
  for (size_t iter = 0; iter < bestSolution.size(); iter++) {
    os << bestSolution[iter] << " ";
  }
  os << "\n";
  return os;
}
