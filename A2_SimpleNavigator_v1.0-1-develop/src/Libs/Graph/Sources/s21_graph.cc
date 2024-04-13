#include "../Headers/s21_graph.h"
namespace s21 {

bool Graph::LoadGraphFromFile(std::string filename) {
  std::ifstream file(filename);
  if (!file.is_open()) return false;
  file >> size_;
  if (file.fail() || size_ <= 0) {
    file.close();
    return false;
  }
  std::vector<std::vector<int>> matrix(size_, std::vector<int>(size_));
  for (int i = 0; i < size_; i++) {
    for (int j = 0; j < size_; j++) {
      file >> matrix[i][j];
      if (file.fail()) {
        file.close();
        return false;
      }
    }
  }
  adjacencyMatrix_ = std::move(matrix);
  file.close();
  return true;
}

bool Graph::ExportGraphToDot(std::string filename) {
  if (adjacencyMatrix_.empty()) return false;
  std::ofstream file;
  file.open(filename);
  if (file.is_open()) {
    std::filesystem::path filePath = filename;
    std::string name = filePath.stem().string();
    file << "digraph " << name << " {\n";
    for (int i = 0; i < size_; ++i) {
      for (int j = 0; j < size_; ++j) {
        if (adjacencyMatrix_[i][j] != 0) {
          file << " " << (char)('a' + i) << " -- " << (char)('a' + j)
               << " [weight=\"" << adjacencyMatrix_[i][j] << "\"];\n";
        }
      }
    }
    file << "}";
    file.close();
    return true;
  }
  file.close();
  return false;
}

const std::vector<std::vector<int>>& Graph::GetAdjacencyMatrix() const {
  return adjacencyMatrix_;
}

int Graph::GetSize() const { return size_; }

const std::vector<int>& Graph::operator[](int index) const {
  return adjacencyMatrix_[index];
}

}  // namespace s21