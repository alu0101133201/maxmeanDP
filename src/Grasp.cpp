/*
 * Autor: Sergio Guera Arencibia
 * alu0101133201@ull.edu.es
 * Universidad de La Laguna
 * 22-04-20
 * Fichero que implementa la clase que implementará
 * el algoritmo GRASP
 */

#include "Grasp.hpp"

Grasp::Grasp(Graph workingGraph, int numberOfCardinality):
    Maxmeandp(workingGraph),
    cardinality(numberOfCardinality) {
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
      int newMin = LRC[0].second;
      for (int minIter = 0; minIter < LRC.size(); minIter++) {
        if (LRC[minIter].first == minNode) {
          LRC[minNode].first = node; 
          LRC[minNode].second = value;
        }
        if (LRC[minIter].second < newMin) {
          newMin = LRC[minIter].first;
        }
      }     
      minNode = LRC[newMin].first;
      min = LRC[newMin].second;
    }
  }
}

void Grasp::buildLRC() {
  LRC.resize(0);
  float lrcMin = FLT_MAX;
  int minNode = -1;

  if (bestSolution.size() == 0) {
    getMax();
  }
  for (int nodeIter = 0; nodeIter < workingGraph.getNumberOfNodes(); nodeIter++) {
    if (!isInSolution(nodeIter)) {
      float currentValue;

      bestSolution.push_back(nodeIter);
      currentValue = mdFromSet(bestSolution);
      addLRC(nodeIter, currentValue, minNode, lrcMin);
      bestSolution.pop_back();
    }
  }
}

float Grasp::construct() {
  buildLRC();
  for (int i = 0; i < LRC.size(); i++)
    std::cout << "-- " << LRC[i].first <<  " - " << LRC[i].second << "|";
  std::cout << "\n";
  return 1.0;
}

float Grasp::solve() {
 construct();
  return 1.0;
}