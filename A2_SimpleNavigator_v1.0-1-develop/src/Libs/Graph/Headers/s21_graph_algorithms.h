#ifndef A2_SIMPLENAVIGATOR_SRC_LIBS_GRAPH_HEADERS_S21_GRAPH_ALGORITHMS_H
#define A2_SIMPLENAVIGATOR_SRC_LIBS_GRAPH_HEADERS_S21_GRAPH_ALGORITHMS_H
#include <limits>

#include "../../Container/Headers/s21_queue.h"
#include "../../Container/Headers/s21_stack.h"
#include "../../TSP/Headers/s21_tsp.h"
#include "s21_graph.h"

namespace s21 {

class GraphAlgorithm {
 public:
  enum FirstSearch { Depth, Breadth };
  GraphAlgorithm() {}
  ~GraphAlgorithm() {}
  std::vector<int> DepthFirstSearch(Graph &graph, int start_vertex);
  std::vector<int> BreadthFirstSearch(Graph &graph, int start_vertex);
  int GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
  std::vector<std::vector<int>> GetShortestPathsBetweenAllVertices(
      Graph &graph);
  std::vector<std::vector<int>> GetLeastSpanningTree(Graph &graph);
  TsmResult SolveTravelingSalesmanProblem(Graph &graph,
                                          Tsp::Algorithm algorithm);

 private:
  const int imax_ = std::numeric_limits<int>::max();
  template <typename T>
  T FirstSearchInit(Graph &graph, int start_vertex);
  int fsSize_;
  std::vector<int> fsResult_;
  std::vector<bool> fsVisited_;
  std::vector<std::vector<int>> fsMatrix_;
};
}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_SRC_LIBS_GRAPH_HEADERS_S21_GRAPH_ALGORITHMS_H