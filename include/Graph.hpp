/*
 * Autor: Sergio Guera Arencibia
 * alu0101133201@ull.edu.es
 * Universidad de La Laguna
 * 22-04-20
 * Fichero que describe la clase grafo
 */

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// Clase que implementa un grafo básico
class Graph {
  private:
    std::vector<float> adjacencyMatrix; // Matriz de adyacencia
    int numberOfNodes;  // Número de nodos

    // Método que lee la matriz del fichero
    void build(std::string fileName);
    // Setter de la matriz
    void setData(int i, int j, float data);

  public:
    Graph();
    Graph(std::string fileName);
    ~Graph();

    // Getter del atributo getNumberOfNodes
    int getNumberOfNodes(void);
    // Getter de un elemento de la matriz
    float at(int i, int j);
    // Método de impresión de la matriz
    std::ostream& write(std::ostream& os);
};

