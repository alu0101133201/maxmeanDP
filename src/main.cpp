/*
 * Autor: Sergio Guera Arencibia
 * alu0101133201@ull.edu.es
 * Universidad de La Laguna
 * 22-04-20
 * Fichero que implementa el programa principal que realizará las 
 * ejecuciones de los diferentes algoritmos y realizará su estudio
 */

#include <iostream> 
#include <string>

#include "Graph.hpp"
#include "FirstGreedy.hpp"
#include "SecondGreedy.hpp"
#include "Maxmeandp.hpp"
#include "MaxmeandpCalculator.hpp"

int main(int argc, char *argv[]) {

  try {
    if (argc <= 1) {
      throw "Argumentos suministrados insuficientes\n";
    }
    std::string fileName(argv[1]);
    std::string base_filename = fileName.substr(fileName.find_last_of("/") + 1);

      Graph firstGraph(fileName);
      Maxmeandp* alg1 = new FirstGreedy(firstGraph);
      Maxmeandp* alg2 = new SecondGreedy(firstGraph);
      MaxmeandpCalculator algorithmInterface(alg1);
      algorithmInterface.solve();
      algorithmInterface.write(std::cout);
      // algorithmInterface.setStrategy(alg2);
      // algorithmInterface.solve();    
      
  } catch(const char* e) {
    std::cout << e;
    return(1);
  }
  return (0);
}