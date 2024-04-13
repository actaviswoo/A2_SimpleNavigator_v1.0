#include "../Headers/s21_graph_algorithms.h"

namespace s21 {

template <typename T>
T GraphAlgorithm::FirstSearchInit(Graph &graph, int start_vertex) {
  fsSize_ = graph.GetSize();
  if (fsSize_ == 0) {
    throw std::exception();
  }
  if (start_vertex > fsSize_ || start_vertex <= 0) {
    throw std::out_of_range("");
  }
  fsResult_ = std::vector<int>();
  fsVisited_ = std::vector<bool>(fsSize_ + 1, false);
  fsMatrix_ = graph.GetAdjacencyMatrix();
  T container;
  return container;
}

std::vector<int> GraphAlgorithm::DepthFirstSearch(Graph &graph,
                                                  int start_vertex) {
  s21::Stack<int> stack = FirstSearchInit<s21::Stack<int>>(graph, start_vertex);
  stack.push(start_vertex);
  while (!stack.empty()) {
    int current_vertex = stack.top();
    stack.pop();
    if (!fsVisited_[current_vertex]) {
      fsResult_.push_back(current_vertex);
      fsVisited_[current_vertex] = true;
    }
    for (int i = fsSize_ - 1; i >= 0; i--) {
      if (fsMatrix_[current_vertex - 1][i] && !fsVisited_[i + 1]) {
        stack.push(i + 1);
      }
    }
  }
  return fsResult_;
}

std::vector<int> GraphAlgorithm::BreadthFirstSearch(Graph &graph,
                                                    int start_vertex) {
  s21::Queue<int> queue = FirstSearchInit<s21::Queue<int>>(graph, start_vertex);
  queue.push(start_vertex);
  while (!queue.empty()) {
    int current_vertex = queue.front();
    queue.pop();
    if (!fsVisited_[current_vertex]) {
      fsResult_.push_back(current_vertex);
      fsVisited_[current_vertex] = true;
    }
    for (int i = 0; i < fsSize_; i++) {
      if (fsMatrix_[current_vertex - 1][i] && !fsVisited_[i + 1]) {
        queue.push(i + 1);
      }
    }
  }
  return fsResult_;
}

int GraphAlgorithm::GetShortestPathBetweenVertices(Graph &graph, int vertex1,
                                                   int vertex2) {
  if (graph.GetAdjacencyMatrix().empty()) {
    throw std::exception();
  }
  if (vertex1 > graph.GetSize() || vertex1 <= 0 || vertex2 > graph.GetSize() ||
      vertex2 <= 0) {
    throw std::out_of_range("");
  }
  --vertex1;
  --vertex2;
  if (vertex1 < 0 || vertex1 >= graph.GetSize() || vertex2 < 0 ||
      vertex2 >= graph.GetSize()) {
    throw std::out_of_range("");
  }
  std::vector<int> min_paths;
  std::vector<int> checked_v;
  for (int i = 0; i < graph.GetSize(); ++i) {
    min_paths.push_back(imax_);
    checked_v.push_back(0);
  }
  int begin_index = vertex1;
  min_paths[begin_index] = 0;
  int temp, minindex, min;
  do {
    minindex = imax_;
    min = imax_;
    for (int i = 0; i < graph.GetSize(); ++i) {
      if ((checked_v[i] == 0) && (min_paths[i] < min)) {
        min = min_paths[i];
        minindex = i;
      }
    }
    if (minindex != imax_) {
      for (int i = 0; i < graph.GetSize(); ++i) {
        if (graph[minindex][i] > 0) {
          temp = min + graph[minindex][i];
          if (temp < min_paths[i]) min_paths[i] = temp;
        }
      }
      checked_v[minindex] = 1;
    }
  } while (minindex < imax_ && checked_v[vertex2] == 0);
  return min_paths[vertex2];
}

std::vector<std::vector<int>>
GraphAlgorithm::GetShortestPathsBetweenAllVertices(Graph &graph) {
  if (graph.GetAdjacencyMatrix().empty()) {
    throw std::exception();
  }
  std::vector<std::vector<int>> matrix = graph.GetAdjacencyMatrix();
  for (int k = 0; k < graph.GetSize(); ++k)
    for (int i = 0; i < graph.GetSize(); ++i)
      for (int j = 0; j < graph.GetSize(); ++j) {
        if (i != j && matrix[i][j] == 0) matrix[i][j] = imax_;
        if (matrix[i][j] > (matrix[i][k] + matrix[k][j]) &&
            (matrix[k][j] != imax_ && matrix[i][k] != imax_))
          matrix[i][j] = matrix[i][k] + matrix[k][j];
      }
  for (int i = 0; i < graph.GetSize(); ++i)
    for (int j = 0; j < graph.GetSize(); ++j)
      if (matrix[i][j] == imax_) matrix[i][j] = 0;
  return matrix;
}

std::vector<std::vector<int>> GraphAlgorithm::GetLeastSpanningTree(
    Graph &graph) {
  if (graph.GetAdjacencyMatrix().empty()) {
    throw std::exception();
  }
  std::vector<std::vector<int>> matrix(graph.GetSize(),
                                       std::vector<int>(graph.GetSize()));
  int cur_edge = 0;
  std::vector<bool> selected = std::vector<bool>(graph.GetSize());
  selected[0] = true;
  int x;
  int y;
  while (cur_edge < graph.GetSize() - 1) {
    int min = imax_;
    x = 0;
    y = 0;
    for (int i = 0; i < graph.GetSize(); ++i) {
      if (selected[i]) {
        for (int j = 0; j < graph.GetSize(); ++j) {
          if (!selected[j] && graph[i][j] && min > graph[i][j]) {
            min = graph[i][j];
            x = i;
            y = j;
          }
        }
      }
    }
    matrix[x][y] = graph[x][y];
    selected[y] = true;
    ++cur_edge;
  }
  return matrix;
}

TsmResult GraphAlgorithm::SolveTravelingSalesmanProblem(
    Graph &graph, Tsp::Algorithm algorithm) {
  Tsp tsp;
  TsmResult result;
  if (algorithm == Tsp::Algorithm::Ant) {
    result = tsp.AntAlgorithm(graph);
  } else if (algorithm == Tsp::Algorithm::BruteForce) {
    result = tsp.BruteForceAlgorithm(graph);
  } else if (algorithm == Tsp::Algorithm::BranchAndBound) {
    result = tsp.BranchAndBoundAlgorithm(graph);
  }
  return result;
}

}  // namespace s21
