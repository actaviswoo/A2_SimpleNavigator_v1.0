#include <gtest/gtest.h>

#include <random>

#include "s21_test.h"

bool AreMatricesEqual(const std::vector<std::vector<int>>& matrix1,
                      const std::vector<std::vector<int>>& matrix2) {
  if (matrix1.size() != matrix2.size()) {
    return false;
  }
  for (size_t i = 0; i < matrix1.size(); ++i) {
    if (matrix1[i].size() != matrix2[i].size()) {
      return false;
    }

    for (size_t j = 0; j < matrix1[i].size(); ++j) {
      if (matrix1[i][j] != matrix2[i][j]) {
        return false;
      }
    }
  }
  return true;
}

bool AreVectorsEqual(const std::vector<int>& vec1,
                     const std::vector<int>& vec2) {
  if (vec1.size() != vec2.size()) {
    return false;
  }
  for (size_t i = 0; i < vec1.size(); ++i) {
    if (vec1[i] != vec2[i]) {
      return false;
    }
  }
  return true;
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
