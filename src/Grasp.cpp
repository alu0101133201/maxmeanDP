/*
 * Autor: Sergio Guera Arencibia
 * alu0101133201@ull.edu.es
 * Universidad de La Laguna
 * 22-04-20
 * Fichero que implementa la clase que implementará
 * el algoritmo GRASP
 */

#include "Grasp.hpp"

Grasp::Grasp(Graph workingGraph, int numberOfCardinality, int stopCriteria, int maxIterations,
    int typeLocal, int environment):
    Maxmeandp(workingGraph),
    cardinality(numberOfCardinality) {
  // Condición de parada
  stopCriteria_ = stopCriteria;
  iterationLimit = maxIterations;

  // Búsqueda local
  localType = typeLocal;
  envirnomentType = environment;

  srand (time(NULL));
  LRC.resize(0);
}

Grasp::~Grasp() {}

void Grasp::addLRC(int node, float value, int& minNode, float& min) {
  std::pair<int, float> dummy(node, value);

  if (LRC.size() < cardinality) {
    if (value < min){
      min = value;
      minNode = node;
    }
    LRC.push_back(dummy);
  } else {
    if (value > min) {
      float newMin = LRC[0].second;
      int newMinIndex = 0;

      for (int minIter = 0; minIter < LRC.size(); minIter++) {
        if (LRC[minIter].first == minNode) {
          LRC[minIter].first = node; 
          LRC[minIter].second = value;
        }
        if (LRC[minIter].second < newMin) {
          newMin = LRC[minIter].second;
          newMinIndex = minIter;
        } else if (LRC[minIter].second == newMin) {
          int randomNumber = rand() % 2;
          if (randomNumber == 1) {
            newMinIndex = minIter;
          }
        }
      }     
      minNode = LRC[newMinIndex].first;
      min = LRC[newMinIndex].second;
    }
  }
}

void Grasp::buildLRC() {
  LRC.clear();
  float lrcMin = FLT_MAX;
  int minNode = -1;

  if (bestSolution.size() == 0) {
    throw "Intentando crear LRC con el conjunto de solución vacío\n";
  }
  for (int nodeIter = 0; nodeIter < workingGraph.getNumberOfNodes(); nodeIter++) {
    if (!isInSolution(nodeIter)) {
      float currentValue;

      bestSolution.push_back(nodeIter);
      currentValue = mdaddNode(bestSolutionValue, bestSolution, nodeIter);
      addLRC(nodeIter, currentValue, minNode, lrcMin);
      bestSolution.pop_back();
    }
  }
}

// void Grasp::preprocessing() {

// }

void Grasp::postProcessing() {
  switch (localType) {
    case (GREEDY):
      greedyLocalSearch();
      break;
    case (ANXIOUS):
      anxiousLocalSearch();
      break;
    default:
      throw "Invalid case\n";
  }
}

float Grasp::construct() {
  bestSolutionValue = getMax();
  std::vector<int> auxSolution; 
  float auxBestSolutionValue = bestSolutionValue;

  do {
    auxSolution = bestSolution;
    buildLRC();
    int randomNumber = rand() % cardinality;
    auxBestSolutionValue = LRC[randomNumber].second;
    if (auxBestSolutionValue > bestSolutionValue) {
      bestSolution.push_back(LRC[randomNumber].first);
      bestSolutionValue = LRC[randomNumber].second;
    }

  } while(auxSolution != bestSolution);
  return bestSolutionValue;
}

float Grasp::solve() {
  int iteration = 0;
  std::vector<int> bestGraspSolution;
  float bestGraspValue = FLT_MIN;
  // preprocessing();

  do {
    construct();
    postProcessing();

    if (bestSolutionValue > bestGraspValue) {
      bestGraspValue = bestSolutionValue;
      bestGraspSolution = bestSolution;
      iterationsWithOutImprove = 0;
    } else {
      iterationsWithOutImprove++;
    }
    iteration++;
  } while(!stopCriteria(iteration));

  bestSolutionValue = bestGraspValue;
  bestSolution = bestGraspSolution;


  return bestSolutionValue;
}