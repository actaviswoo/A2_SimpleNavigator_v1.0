#ifndef A2_SIMPLENAVIGATOR_SRC_LIBS_GRAPH_HEADERS_S21_GRAPH_H
#define A2_SIMPLENAVIGATOR_SRC_LIBS_GRAPH_HEADERS_S21_GRAPH_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace s21 {
class Graph {
 public:
  Graph() {}
  ~Graph() {}

  bool LoadGraphFromFile(std::string filename);
  bool ExportGraphToDot(std::string filename);
  const std::vector<std::vector<int>>& GetAdjacencyMatrix() const;
  int GetSize() const;

  const std::vector<int>& operator[](int index) const;

 private:
  std::vector<std::vector<int>> adjacencyMatrix_;
  int size_ = 0;
};
}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_SRC_LIBS_GRAPH_HEADERS_S21_GRAPH_H