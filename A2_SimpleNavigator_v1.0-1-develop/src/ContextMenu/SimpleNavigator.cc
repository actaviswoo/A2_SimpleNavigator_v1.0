#include "SimpleNavigator.h"

namespace s21 {

const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string BLACK = "\033[30m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string PURPLE = "\033[35m";
const std::string WHITE = "\033[37m";

class LoadGraphCommand : public Command {
 private:
  Graph& graph_;
  std::istream& input_;

 public:
  LoadGraphCommand(Graph& graph, std::istream& input)
      : graph_(graph), input_(input) {}

  void execute() override {
    std::string filename;
    std::cout << YELLOW << "input filename\n--> " << RESET;
    input_ >> filename;
    if (graph_.LoadGraphFromFile(filename)) {
      std::cout << GREEN << "graph loaded" << RESET << std::endl;
    } else {
      std::cout << RED << "can't load" << RESET << std::endl;
    }
  }
};

class ExportGraphCommand : public Command {
 private:
  Graph& graph_;
  std::istream& input_;

 public:
  ExportGraphCommand(Graph& graph, std::istream& input)
      : graph_(graph), input_(input) {}

  void execute() override {
    std::string filename;
    std::cout << YELLOW << "input filename\n--> " << RESET;
    input_ >> filename;
    if (graph_.ExportGraphToDot(filename)) {
      std::cout << GREEN << "graph exported" << RESET << std::endl;
    } else {
      std::cout << RED << "can't export" << RESET << std::endl;
    }
  }
};

class FirstSearchCommand : public Command {
 private:
  Graph& graph_;
  GraphAlgorithm& graphAlgorithm_;
  std::istream& input_;
  GraphAlgorithm::FirstSearch fisrtSearch_;

 public:
  FirstSearchCommand(Graph& graph, GraphAlgorithm& graphAlgorithm,
                     std::istream& input,
                     GraphAlgorithm::FirstSearch fisrtSearch)
      : graph_(graph),
        graphAlgorithm_(graphAlgorithm),
        input_(input),
        fisrtSearch_(fisrtSearch) {}

  void execute() override {
    int start_vertex;
    std::cout << YELLOW << "input start vertex\n--> " << RESET;
    input_ >> start_vertex;
    try {
      std::vector<int> result;
      if (fisrtSearch_ == GraphAlgorithm::FirstSearch::Breadth) {
        result = graphAlgorithm_.BreadthFirstSearch(graph_, start_vertex);
      } else if (fisrtSearch_ == GraphAlgorithm::FirstSearch::Depth) {
        result = graphAlgorithm_.DepthFirstSearch(graph_, start_vertex);
      }
      if (result.empty()) {
        std::cout << RED << "solution not found" << RESET << std::endl;
        return;
      }
      std::cout << GREEN << "result vector\n[ ";
      for (auto i : result) {
        std::cout << i << " ";
      }
      std::cout << "]\n" << RESET;
    } catch (const std::out_of_range& e) {
      std::cout << RED << "start vertex out of range" << RESET << std::endl;
    } catch (const std::exception& e) {
      std::cout << RED << "graph empty" << RESET << std::endl;
    }
  }
};

class SolveTravelingSalesmanProblemCommand : public Command {
 private:
  Graph& graph_;
  GraphAlgorithm& graphAlgorithm_;
  Tsp::Algorithm algorithm_;

 public:
  SolveTravelingSalesmanProblemCommand(Graph& graph,
                                       GraphAlgorithm& graphAlgorithm,
                                       Tsp::Algorithm algorithm)
      : graph_(graph), graphAlgorithm_(graphAlgorithm), algorithm_(algorithm) {}

  void execute() override {
    try {
      TsmResult result =
          graphAlgorithm_.SolveTravelingSalesmanProblem(graph_, algorithm_);
      if (result.vertices.empty()) {
        std::cout << RED << "solution not found" << RESET << std::endl;
        return;
      }
      std::cout << GREEN << "vertices\n[ ";
      for (int i = 0; i < (int)result.vertices.size(); i++) {
        std::cout << result.vertices[i] + 1 << " ";
      }
      std::cout << "]\ndistance\n[ " << result.distance << " ]" << RESET
                << std::endl;
    } catch (const std::exception& e) {
      std::cout << RED << "graph empty" << RESET << std::endl;
    }
  }
};

class GetShortestPathBetweenVerticesCommand : public Command {
 private:
  Graph& graph_;
  GraphAlgorithm& graphAlgorithm_;
  std::istream& input_;

 public:
  GetShortestPathBetweenVerticesCommand(Graph& graph,
                                        GraphAlgorithm& graphAlgorithm,
                                        std::istream& input)
      : graph_(graph), graphAlgorithm_(graphAlgorithm), input_(input) {}

  void execute() override {
    try {
      int vertex1;
      std::cout << YELLOW << "input vertex1\n--> " << RESET;
      input_ >> vertex1;
      int vertex2;
      std::cout << YELLOW << "input vertex2\n--> " << RESET;
      input_ >> vertex2;
      int result = graphAlgorithm_.GetShortestPathBetweenVertices(
          graph_, vertex1, vertex2);
      std::cout << GREEN << "result\n[ " << result << " ]" << RESET
                << std::endl;
    } catch (const std::out_of_range& e) {
      std::cout << RED << "incorrect vertices" << RESET << std::endl;
    } catch (const std::exception& e) {
      std::cout << RED << "graph empty" << RESET << std::endl;
    }
  }
};

class GetShortestPathsBetweenAllVerticesCommand : public Command {
 private:
  Graph& graph_;
  GraphAlgorithm& graphAlgorithm_;

 public:
  GetShortestPathsBetweenAllVerticesCommand(Graph& graph,
                                            GraphAlgorithm& graphAlgorithm)
      : graph_(graph), graphAlgorithm_(graphAlgorithm) {}

  void execute() override {
    try {
      std::vector<std::vector<int>> result =
          graphAlgorithm_.GetShortestPathsBetweenAllVertices(graph_);
      if (result.empty()) {
        std::cout << RED << "solution not found" << RESET << std::endl;
        return;
      }
      std::cout << GREEN << "result vertors" << std::endl;
      for (int i = 0; i < (int)result.size(); i++) {
        printf("%3d[", i + 1);
        for (int j = 0; j < (int)result[i].size(); j++) {
          printf("%4d ", result[i][j]);
        }
        std::cout << "]" << std::endl;
      }
    } catch (const std::exception& e) {
      std::cout << RED << "graph empty" << RESET << std::endl;
    }
  }
};

class GetLeastSpanningTreeCommand : public Command {
 private:
  Graph& graph_;
  GraphAlgorithm& graphAlgorithm_;

 public:
  GetLeastSpanningTreeCommand(Graph& graph, GraphAlgorithm& graphAlgorithm)
      : graph_(graph), graphAlgorithm_(graphAlgorithm) {}

  void execute() override {
    try {
      std::vector<std::vector<int>> result =
          graphAlgorithm_.GetLeastSpanningTree(graph_);
      if (result.empty()) {
        std::cout << RED << "solution not found" << RESET << std::endl;
        return;
      }
      std::cout << GREEN << "result vertors" << std::endl;
      for (int i = 0; i < (int)result.size(); i++) {
        printf("%3d[", i + 1);
        for (int j = 0; j < (int)result[i].size(); j++) {
          printf("%4d ", result[i][j]);
        }
        std::cout << "]" << std::endl;
      }
    } catch (const std::exception& e) {
      std::cout << RED << "graph empty" << RESET << std::endl;
    }
  }
};

class SolveTravelingSalesmanProblemTestSpeedCommand : public Command {
 private:
  Graph& graph_;
  GraphAlgorithm& graphAlgorithm_;
  std::istream& input_;

 public:
  SolveTravelingSalesmanProblemTestSpeedCommand(Graph& graph,
                                                GraphAlgorithm& graphAlgorithm,
                                                std::istream& input)
      : graph_(graph), graphAlgorithm_(graphAlgorithm), input_(input) {}

  void execute() override {
    try {
      int n;
      std::cout << YELLOW << "input count of iteration\n--> " << RESET;
      input_ >> n;
      TsmResult result;
      auto start = std::chrono::high_resolution_clock::now();
      for (int i = 0; i < n; i++) {
        result = graphAlgorithm_.SolveTravelingSalesmanProblem(
            graph_, Tsp::Algorithm::Ant);
      }
      auto end = std::chrono::high_resolution_clock::now();
      std::cout << GREEN << "time of AntAlgoritm [ "
                << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                         start)
                       .count()
                << " ]" << std::endl;
      start = std::chrono::high_resolution_clock::now();
      for (int i = 0; i < n; i++) {
        result = graphAlgorithm_.SolveTravelingSalesmanProblem(
            graph_, Tsp::Algorithm::BruteForce);
      }
      end = std::chrono::high_resolution_clock::now();
      std::cout << GREEN << "time of BruteForceAlgorithm [ "
                << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                         start)
                       .count()
                << " ]" << std::endl;
      start = std::chrono::high_resolution_clock::now();
      for (int i = 0; i < n; i++) {
        result = graphAlgorithm_.SolveTravelingSalesmanProblem(
            graph_, Tsp::Algorithm::BranchAndBound);
      }
      end = std::chrono::high_resolution_clock::now();
      std::cout << GREEN << "time of BranchAndBoundAlgorithm [ "
                << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                         start)
                       .count()
                << " ]" << std::endl;
    } catch (const std::exception& e) {
      std::cout << RED << "graph empty" << RESET << std::endl;
    }
  }
};

void SimpleNavigator::start() {
  std::cout << YELLOW << menu_ << RESET << std::endl;
  commands_.push_back(
      std::make_shared<LoadGraphCommand>(graph_, std::cin));  // 0
  commands_.push_back(
      std::make_shared<ExportGraphCommand>(graph_, std::cin));  // 1
  commands_.push_back(std::make_shared<FirstSearchCommand>(
      graph_, graphAlgorithm_, std::cin,
      GraphAlgorithm::FirstSearch::Depth));  // 2
  commands_.push_back(std::make_shared<FirstSearchCommand>(
      graph_, graphAlgorithm_, std::cin,
      GraphAlgorithm::FirstSearch::Breadth));  // 3
  commands_.push_back(std::make_shared<GetShortestPathBetweenVerticesCommand>(
      graph_, graphAlgorithm_, std::cin));  // 4
  commands_.push_back(
      std::make_shared<GetShortestPathsBetweenAllVerticesCommand>(
          graph_, graphAlgorithm_));  // 5
  commands_.push_back(std::make_shared<GetLeastSpanningTreeCommand>(
      graph_, graphAlgorithm_));  // 6
  commands_.push_back(std::make_shared<SolveTravelingSalesmanProblemCommand>(
      graph_, graphAlgorithm_, Tsp::Algorithm::Ant));  // 7
  commands_.push_back(std::make_shared<SolveTravelingSalesmanProblemCommand>(
      graph_, graphAlgorithm_, Tsp::Algorithm::BruteForce));  // 8
  commands_.push_back(std::make_shared<SolveTravelingSalesmanProblemCommand>(
      graph_, graphAlgorithm_, Tsp::Algorithm::BranchAndBound));  // 9
  commands_.push_back(
      std::make_shared<SolveTravelingSalesmanProblemTestSpeedCommand>(
          graph_, graphAlgorithm_, std::cin));  // 10
  int choice = 0;
  do {
    std::cout << YELLOW << "make your choice\n--> " << RESET;
    std::cin >> choice;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(32767, '\n');
    } else if (choice >= 0 && choice < (int)commands_.size()) {
      std::cin.ignore(32767, '\n');
      commands_[choice]->execute();
    }
  } while (choice != 11);
};

}  // namespace s21