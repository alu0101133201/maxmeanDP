/*
 * Autor: Sergio Guera Arencibia
 * alu0101133201@ull.edu.es
 * Universidad de La Laguna
 * 22-04-20
 * Fichero que implementa las clases que implementarán
 * los planteamientos greedy del algorimot maxmeandp
 */

#include "Greedy.hpp"

FirstGreedy::FirstGreedy(Graph workingGraph):
    Maxmeandp(workingGraph) {}

SecondGreedy::SecondGreedy(Graph workingGraph):
    Maxmeandp(workingGraph) {}

int FirstGreedy::solve() {
  std::cout << "En el primero\n";
  return 5;
}

int SecondGreedy::solve() {
  std::cout << "En el segundo\n";
  return 1;
}