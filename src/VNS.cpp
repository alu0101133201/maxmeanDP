/*
 * Autor: Sergio Guera Arencibia
 * alu0101133201@ull.edu.es
 * Universidad de La Laguna
 * 22-04-20
 * Fichero que describe la clase que implementará
 * un algoritmo VNS
 */

#include "VNS.hpp"


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

float VNS::shake(std::vector<int>& currentSolution, float currentValue, int numberOfChanges) {
  std::vector<int> candidates;
  std::vector<int> shakeSolution = currentSolution;
  float shakeValue = currentValue;
  std::vector<int> swappedNodes(shakeSolution.size(), -1);

  for (int candidateIter = 0 ; candidateIter < workingGraph.getNumberOfNodes(); candidateIter++) {
    if (!myGrasp.isInSolution(candidateIter)) {
      candidates.push_back(candidateIter);
    }
  }
  for (int swapIteration = 0; swapIteration < numberOfChanges; swapIteration++) {
    int randomNumber = rand() % currentSolution.size();
    std::vector<int>::iterator toSwap = candidates.begin();
    std::advance(toSwap, (rand() % candidates.size()));

    if (swappedNodes[randomNumber] != 1) {
      shakeSolution[randomNumber] = *toSwap;
      swappedNodes[randomNumber] = 1;
      candidates.erase(toSwap);
    } else {
      swapIteration--;
    }
  }
  // OJOOO CON LA FUNCIÓN OBJETIVO - ARREGLAR
  shakeValue = mdFromSet(bestSolution);
  // bestSolution = shakeSolution;
  // bestSolutionValue = shakeValue;
  // postProcessing();
  // shakeValue = bestSolutionValue;
  // shakeSolution = bestSolution;
}


void VNS::mainVNS(std::vector<int>& currentSolution, float currentValue) {
  for (int environment = 1; environment < 4; environment++) {
    // std::cout << "Antes del shake: " << currentValue << "\n";
    // for(int i=0; i < currentSolution.size(); i++)
    //   std::cout << currentSolution[i] << " ";
    shake(currentSolution, currentValue, environment);

    // std::cout << "Después del shake: " << bestSolutionValue << "\n";
    // for(int i=0; i < bestSolution.size(); i++)
    //   std::cout << bestSolution[i] << " ";

    if (bestSolutionValue > currentValue) {
      environment = 0;
      currentSolution = bestSolution;
      currentValue = bestSolutionValue;
    }
  }
  bestSolutionValue = currentValue,
  bestSolution = currentSolution;
}

float VNS::solve() {
  int iterator = 0;
  std::vector<int> bestVNSSolution;
  float bestVNSValue = FLT_MIN;
  
  do {
    std::vector<int> auxSolution;
    float auxValue;
    
    // A partir de GRASP
    // myGrasp.solve();
    // auxSolution = myGrasp.getBestSolution();
    // auxValue = myGrasp.getBestSoluctionValue();

    // A partir de soluciones ranodm
    generateRandom();
    auxSolution = bestSolution;
    auxValue = bestSolutionValue;
    // postProcessing();
    mainVNS(auxSolution, auxValue);

    if (bestSolutionValue > bestVNSValue) {
      bestVNSSolution = bestSolution;
      bestVNSValue = bestVNSValue;
      iterationsWithOutImprove = 0;
    } else {
      iterationsWithOutImprove++;
    }

    iterator++;
  } while(!stopCriteria(iterator));
  return bestVNSValue;
}

