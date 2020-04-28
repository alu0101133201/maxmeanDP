/*
 * Autor: Sergio Guera Arencibia
 * alu0101133201@ull.edu.es
 * Universidad de La Laguna
 * 22-04-20
 * Fichero que implementa la clase de la modificación
 * un algoritmo VNS
 */

#include "VNS.hpp"

#include "mod.hpp"

// ----------- MODIFICACIÓN ---------------
// ----------------------------------------

bool isInVector(int node, std::vector<int>& myVector) {
  for (size_t iter = 0; iter < myVector.size(); iter++) {
    if (myVector[iter] == node) 
      return true;
  }
  return false;
}


Mod::Mod(Graph workingGraph, int numberOfCardinality, int stopCriteria, int maxIterations,
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

void Mod::shake(std::vector<int> currentSolution, float currentValue, int numberOfChanges) {
  std::vector<int> candidates;
  std::vector<int> shakeSolution = currentSolution;
  float shakeValue = currentValue;
  std::vector<int> swappedNodes(shakeSolution.size(), -1);
  int swapped = 0;

  for (int candidateIter = 0 ; candidateIter < workingGraph.getNumberOfNodes(); candidateIter++) {
    if (!isInVector(candidateIter, currentSolution)) {
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

float Mod::mainLoopSolution(std::vector<int>& currentSolution, float& currentValue) {
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
  return(bestSolutionValue);
}

Mod::~Mod() {}

float Mod::solve() {
  int iterator = 0;
  std::vector<int> bestModSolution;
  float bestModValue = FLT_MIN;
  
  do {
    std::vector<int> auxSolution;
    float auxValue;
    
    // Obtenemos la solución inicial con GRASP
    myGrasp.solve();
    auxSolution = myGrasp.getBestSolution();
    auxValue = myGrasp.getBestSoluctionValue();

    // Aplicamos la búsqueda por los diferentes entornos, diversificando e intensificando
    mainLoopSolution(auxSolution, auxValue);
    // Actualizamos si es necesario
    if (bestSolutionValue > bestModValue) {
      bestModSolution = bestSolution;
      bestModValue = bestSolutionValue;
    } 
    iterator++;
    // Condición de parada del pseudocódigo : 5 iteraciones
  } while(iterator < 5);

  bestSolution = bestModSolution;
  bestSolutionValue = bestModValue;
  // Devolvemos la mejor Solución
  return bestModValue;
}