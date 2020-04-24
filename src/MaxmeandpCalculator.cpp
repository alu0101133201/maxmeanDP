/*
 * Autor: Sergio Guera Arencibia
 * alu0101133201@ull.edu.es
 * Universidad de La Laguna
 * 22-04-20
 * Fichero que implementa la clase abstracta maxmeandp. Esta 
 * sera la clase padre de diferentes clases que implementarán
 * un algoritmo de resolución para el problema
 */

#include "MaxmeandpCalculator.hpp"

MaxmeandpCalculator::MaxmeandpCalculator(Maxmeandp* initialStrategy):
    algorithm(initialStrategy) {}

MaxmeandpCalculator::~MaxmeandpCalculator() {}

void MaxmeandpCalculator::setStrategy(Maxmeandp* newStrategy) {
  algorithm = newStrategy;
}

float MaxmeandpCalculator::solve(void) {
  return(algorithm->solve());
}

std::ostream& MaxmeandpCalculator::write(std::ostream& os) {
  algorithm->write(os);
  return os;
}