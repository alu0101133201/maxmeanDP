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

float Maxmeandp::mdFromSet(std::vector<int> nodeSet) {
  float ValueSum = 0;

  // std::cout << "\n\n";
  // for (int i = 0; i < nodeSet.size(); i++)
  //   std::cout << nodeSet[i] << " ";
  for (size_t iter = 0; iter < nodeSet.size(); iter++) {
    for (size_t secondIter = iter + 1; secondIter < nodeSet.size(); secondIter++) {
      ValueSum += workingGraph.at(nodeSet[iter], nodeSet[secondIter]);
    }
  }
  return ValueSum / nodeSet.size();
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
}

void Maxmeandp::anxiousLocalSearch() {
  std::vector<int> newSolution;
  float auxValue;
  std::cout << "EN LA ANSIOSAA:\n";
  for (int i = 0; i < bestSolution.size(); i++)
    std::cout << bestSolution[i] << " ";

  for (int nodeIter = 0; nodeIter < workingGraph.getNumberOfNodes(); nodeIter++) {
    newSolution = generateNeighbour(nodeIter);
    auxValue = mdFromSet(newSolution);

    std::cout << "\nBest mean: " << bestSolutionValue << " media veina: " << auxValue << "\n";
    for (int i = 0; i < newSolution.size(); i++)
      std::cout << newSolution[i] << " ";

    if (auxValue > bestSolutionValue) {
      bestSolution = newSolution;
      bestSolutionValue = auxValue;
      std::cout << "ESTOY ACTUALIZANDO\n";
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