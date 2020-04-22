/*
 * Autor: Sergio Guera Arencibia
 * alu0101133201@ull.edu.es
 * Universidad de La Laguna
 * 22-04-20
 * Fichero que describe la clase abstracta maxmeandp. Esta 
 * sera la clase padre de diferentes clases que implementarán
 * un algoritmo de resolución para el problema
 */

#pragma once

#include "Greedy.hpp"
#include "Maxmeandp.hpp"
#include "Graph.hpp"


class MaxmeandpCalculator {
  private:
    Maxmeandp* algorithm;

  public:
    MaxmeandpCalculator(Maxmeandp*);
    ~MaxmeandpCalculator();

    void setStrategy(Maxmeandp*);
    int solve();
};
