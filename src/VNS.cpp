/*
 * Autor: Sergio Guera Arencibia
 * alu0101133201@ull.edu.es
 * Universidad de La Laguna
 * 22-04-20
 * Fichero que describe la clase que implementará
 * un algoritmo VNS
 */

#include "VNS.hpp"

bool inVector(int node, std::vector<int>& myVector) {
  for (size_t iter = 0; iter < myVector.size(); iter++) {
    if (myVector[iter] == node) 
      return true;
  }
  return false;
}

VNS::VNS(Graph workingGraph, int numberOfCardinality, int stopCriteria, int maxIterations,
    int typeLocal, int environment) :
    Maxmeandp(workingGraph),
    myGrasp(workingGraph, numberOfCardinality, stopCriteria, maxIterations,
    typeLocal, environment) {

  // Condición de parada
  stopCriteria_ = stopCriteria;
  iterationLimit = maxIterations;

   // Búsqueda local
  localType = typeLocal;
  envirnomentType = environment;
}

VNS::~VNS() {}

void VNS::shake(std::vector<int> currentSolution, float currentValue, int numberOfChanges) {
  std::vector<int> candidates;
  std::vector<int> shakeSolution = currentSolution;
  float shakeValue = currentValue;
  std::vector<int> swappedNodes(shakeSolution.size(), -1);
  int swapped = 0;

  for (int candidateIter = 0 ; candidateIter < workingGraph.getNumberOfNodes(); candidateIter++) {
    if (!inVector(candidateIter, currentSolution)) {     // NO USO EL MYGRASP YA esther <3
      candidates.push_back(candidateIter);
    }
  }

  for (int swapIteration = 0; swapIteration < numberOfChanges; swapIteration++) {
    int randomNumber = rand() % currentSolution.size();
    std::vector<int>::iterator toSwap;

    if ((candidates.size() != 0) && (swapped != swappedNodes.size())) {
      toSwap = candidates.begin();
      std::advance(toSwap, (rand() % candidates.size()));
    } else {
      break;
    }
    if (swappedNodes[randomNumber] != 1) {
      shakeSolution[randomNumber] = *toSwap;
      swapped++;
      swappedNodes[randomNumber] = 1;
      candidates.erase(toSwap);
    } else {
      swapIteration--;
    }
  }
  shakeValue = mdFromSet(shakeSolution);

  bestSolution = shakeSolution;
  bestSolutionValue = shakeValue;
  postProcessing();
}


void VNS::mainVNS(std::vector<int>& currentSolution, float& currentValue) {
  
  for (int environment = 1; environment < 4; environment++) {
    shake(currentSolution, currentValue, environment); 
    if (bestSolutionValue > currentValue) {
      environment = 0;
      currentValue = bestSolutionValue;
      currentSolution = bestSolution;
    }
  }
  bestSolution = currentSolution;
  bestSolutionValue = currentValue;
}

float VNS::solve() {
  int iterator = 0;
  std::vector<int> bestVNSSolution;
  float bestVNSValue = FLT_MIN;
  
  do {
    std::vector<int> auxSolution;
    float auxValue;
    
    // A partir de GRASP
    myGrasp.solve();
    auxSolution = myGrasp.getBestSolution();
    auxValue = myGrasp.getBestSoluctionValue();
    // A partir de soluciones ranodm
    // generateRandom();
    // auxSolution = bestSolution;
    // auxValue = bestSolutionValue;

    mainVNS(auxSolution, auxValue);
    if (bestSolutionValue > bestVNSValue) {
      bestVNSSolution = bestSolution;
      bestVNSValue = bestSolutionValue;
      iterationsWithOutImprove = 0;
    } else {
      iterationsWithOutImprove++;
    }

    iterator++;
  } while(!stopCriteria(iterator));

  bestSolution = bestVNSSolution;
  bestSolutionValue = bestVNSValue;
  return bestVNSValue;
}

