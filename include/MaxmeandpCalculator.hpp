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

#include <iostream>

#include "FirstGreedy.hpp"
#include "SecondGreedy.hpp"
#include "Maxmeandp.hpp"
#include "Graph.hpp"

// Clase contexto que implementará el patrón estrategia
class MaxmeandpCalculator {
  private:
    Maxmeandp* algorithm;

  public:
    MaxmeandpCalculator(Maxmeandp*);
    ~MaxmeandpCalculator();

    // Método que nos permite cambiar la estrategia
    void setStrategy(Maxmeandp*);
    // Método principal de resolución
    float solve();

    // Método básico de impresion
    std::ostream& write(std::ostream& os);
};
