#include <gtest/gtest.h>

#include <queue>

#include "../Libs/Container/Headers/s21_queue.h"

TEST(QueueTest, Constructor_default_1) {
  s21::Queue<int> s21_queue;
  std::queue<int> std_queue;
  EXPECT_EQ(s21_queue.size(), std_queue.size());
}
TEST(QueueTest, Constructor_initializer_list_1) {
  s21::Queue<int> s21_queue{1, 2, 4};
  EXPECT_EQ(s21_queue.size(), 3);
  EXPECT_EQ(s21_queue.front(), 1);
  EXPECT_EQ(s21_queue.back(), 4);
}

TEST(QueueTest, Constructor_initializer_list_2) {
  std::initializer_list<int> b;
  s21::Queue<int> s21_queue{b};
  std::queue<int> std_queue{b};
  EXPECT_EQ(s21_queue.size(), std_queue.size());
}

TEST(QueueTest, Constructor_copy_1) {
  std::initializer_list<int> il1 = {1, 2, 3};
  s21::Queue<int> s21_queue{il1};
  s21::Queue<int> s21_queue_copy{s21_queue};
  std::queue<int> std_queue{il1};
  std::queue<int> std_queue_copy{std_queue};
  EXPECT_EQ(s21_queue_copy.size(), std_queue_copy.size());
  EXPECT_EQ(s21_queue_copy.front(), std_queue_copy.front());
  EXPECT_EQ(s21_queue_copy.back(), std_queue_copy.back());
}

TEST(QueueTest, Constructor_move_1) {
  std::initializer_list<int> il1 = {1, 2, 3};
  s21::Queue<int> s21_queue{il1};
  s21::Queue<int> s21_queue_move{s21_queue};
  std::queue<int> std_queue{il1};
  std::queue<int> std_queue_move{std_queue};
  EXPECT_EQ(s21_queue_move.size(), std_queue_move.size());
  EXPECT_EQ(s21_queue_move.front(), std_queue_move.front());
  EXPECT_EQ(s21_queue_move.back(), std_queue_move.back());
}

TEST(QueueTest, Opertator_move_1) {
  std::initializer_list<int> il1 = {1, 2, 3};
  std::initializer_list<int> il2 = {4, 5, 6, 7};
  s21::Queue<int> s21_queue{il1};
  s21::Queue<int> s21_queue_move{il2};
  s21_queue = std::move(s21_queue_move);
  std::queue<int> std_queue{il1};
  std::queue<int> std_queue_move{il2};
  std_queue = std::move(std_queue_move);
  EXPECT_EQ(s21_queue.size(), std_queue.size());
  EXPECT_EQ(s21_queue.front(), std_queue.front());
  EXPECT_EQ(s21_queue.back(), std_queue.back());
}

TEST(QueueTest, Opertator_move_2) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};
  std::initializer_list<int> il2 = {1, 2, 3};
  s21::Queue<int> s21_queue{il1};
  s21::Queue<int> s21_queue_move{il2};
  s21_queue = std::move(s21_queue_move);
  std::queue<int> std_queue{il1};
  std::queue<int> std_queue_move{il2};
  std_queue = std::move(std_queue_move);
  EXPECT_EQ(s21_queue.size(), std_queue.size());
  EXPECT_EQ(s21_queue.front(), std_queue.front());
  EXPECT_EQ(s21_queue.back(), std_queue.back());
}

TEST(QueueTest, Opertator_move_3) {
  std::initializer_list<int> il1;
  std::initializer_list<int> il2 = {4, 5, 6, 7};
  s21::Queue<int> s21_queue{il1};
  s21::Queue<int> s21_queue_move{il2};
  s21_queue = std::move(s21_queue_move);
  std::queue<int> std_queue{il1};
  std::queue<int> std_queue_move{il2};
  std_queue = std::move(std_queue_move);
  EXPECT_EQ(s21_queue.size(), std_queue.size());
  EXPECT_EQ(s21_queue.front(), std_queue.front());
  EXPECT_EQ(s21_queue.back(), std_queue.back());
}

TEST(QueueTest, Front_1) {
  s21::Queue<int> my_queue{99, 2, 3, 4, 5};
  std::initializer_list<int> il = {99, 1, 3, 7, 20};
  std::queue<int> std_queue{il};
  EXPECT_EQ(my_queue.front(), std_queue.front());
}

TEST(QueueTest, Front_2) {
  std::initializer_list<int> il1;
  s21::Queue<int> s21_queue{il1};
  EXPECT_THROW(s21_queue.front(), std::runtime_error);
}

TEST(QueueTest, Back_1) {
  s21::Queue<int> my_queue{1, 2, 3, 3, 4, 99};
  std::initializer_list<int> il = {99, 1, 3, 5, 4, 7, 99};
  std::queue<int> std_queue{il};
  EXPECT_EQ(my_queue.back(), std_queue.back());
}

TEST(QueueTest, Back_2) {
  std::initializer_list<int> il1;
  s21::Queue<int> s21_queue{il1};
  EXPECT_THROW(s21_queue.back(), std::runtime_error);
}

TEST(QueueTest, Empty_1) {
  s21::Queue<int> my_queue;
  std::queue<int> std_queue;
  EXPECT_EQ(my_queue.empty(), std_queue.empty());
  my_queue.push(2354);
  std_queue.push(2354);
  EXPECT_EQ(my_queue.empty(), std_queue.empty());
}

TEST(QueueTest, Empty_2) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};
  s21::Queue<int> s21_queue{il1};
  std::queue<int> std_queue{il1};
  EXPECT_EQ(s21_queue.empty(), std_queue.empty());
}

TEST(QueueTest, Size_1) {
  s21::Queue<int> my_queue{1, 2, 3, 4, 5, 6, 7, 8};
  std::initializer_list<int> il = {1, 2, 3, 4, 5, 6, 7, 8};
  std::queue<int> std_queue{il};
  EXPECT_EQ(my_queue.size(), std_queue.size());
}

TEST(QueueTest, Push_1) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};
  s21::Queue<int> s21_queue{il1};
  std::queue<int> std_queue{il1};
  s21_queue.push(1);
  std_queue.push(1);
  EXPECT_EQ(s21_queue.size(), std_queue.size());
  EXPECT_EQ(s21_queue.front(), std_queue.front());
  EXPECT_EQ(s21_queue.back(), std_queue.back());
}

TEST(QueueTest, Pop_1) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};
  s21::Queue<int> s21_queue{il1};
  std::queue<int> std_queue{il1};
  s21_queue.pop();
  std_queue.pop();
  EXPECT_EQ(s21_queue.size(), std_queue.size());
  EXPECT_EQ(s21_queue.front(), std_queue.front());
  EXPECT_EQ(s21_queue.back(), std_queue.back());
}

TEST(QueueTest, Swap_1) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};
  std::initializer_list<int> il2 = {1, 2, 3};
  s21::Queue<int> s21_queue{il1};
  s21::Queue<int> s21_queue_swap{il2};
  std::queue<int> std_queue{il1};
  std::queue<int> std_queue_swap{il2};
  s21_queue.swap(s21_queue_swap);
  std_queue.swap(std_queue_swap);
  EXPECT_EQ(s21_queue.size(), std_queue.size());
  EXPECT_EQ(s21_queue.front(), std_queue.front());
  EXPECT_EQ(s21_queue.back(), std_queue.back());
  EXPECT_EQ(s21_queue_swap.size(), std_queue_swap.size());
  EXPECT_EQ(s21_queue_swap.front(), std_queue_swap.front());
  EXPECT_EQ(s21_queue_swap.back(), std_queue_swap.back());
}

TEST(QueueTest, Swap_2) {
  std::initializer_list<int> il1 = {1, 2, 3};
  std::initializer_list<int> il2 = {4, 5, 6, 7};
  s21::Queue<int> s21_queue{il1};
  s21::Queue<int> s21_queue_swap{il2};
  std::queue<int> std_queue{il1};
  std::queue<int> std_queue_swap{il2};
  s21_queue.swap(s21_queue_swap);
  std_queue.swap(std_queue_swap);
  EXPECT_EQ(s21_queue.size(), std_queue.size());
  EXPECT_EQ(s21_queue.front(), std_queue.front());
  EXPECT_EQ(s21_queue.back(), std_queue.back());
  EXPECT_EQ(s21_queue_swap.size(), std_queue_swap.size());
  EXPECT_EQ(s21_queue_swap.front(), std_queue_swap.front());
  EXPECT_EQ(s21_queue_swap.back(), std_queue_swap.back());
}

TEST(QueueTest, Swap_3) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};
  std::initializer_list<int> il2;
  s21::Queue<int> s21_queue{il1};
  s21::Queue<int> s21_queue_swap{il2};
  std::queue<int> std_queue{il1};
  std::queue<int> std_queue_swap{il2};
  s21_queue.swap(s21_queue_swap);
  std_queue.swap(std_queue_swap);
  EXPECT_EQ(s21_queue.size(), std_queue.size());
  EXPECT_EQ(s21_queue_swap.size(), std_queue_swap.size());
}

TEST(QueueTest, Swap_4) {
  std::initializer_list<int> il1;
  std::initializer_list<int> il2 = {4, 5, 6, 7};
  s21::Queue<int> s21_queue{il1};
  s21::Queue<int> s21_queue_swap{il2};
  std::queue<int> std_queue{il1};
  std::queue<int> std_queue_swap{il2};
  s21_queue.swap(s21_queue_swap);
  std_queue.swap(std_queue_swap);
  EXPECT_EQ(s21_queue.size(), std_queue.size());
  EXPECT_EQ(s21_queue_swap.size(), std_queue_swap.size());
}

TEST(QueueTest, Swap_5) {
  std::initializer_list<int> il1;
  std::initializer_list<int> il2;
  s21::Queue<int> s21_queue{il1};
  s21::Queue<int> s21_queue_swap{il2};
  std::queue<int> std_queue{il1};
  std::queue<int> std_queue_swap{il2};
  s21_queue.swap(s21_queue_swap);
  std_queue.swap(std_queue_swap);
  EXPECT_EQ(s21_queue.size(), std_queue.size());
  EXPECT_EQ(s21_queue_swap.size(), std_queue_swap.size());
}

TEST(QueueTest, Swap_6) {
  std::initializer_list<int> il1 = {4, 5, 6, 7};
  std::initializer_list<int> il2 = {4, 5, 6, 7};
  s21::Queue<int> s21_queue{il1};
  s21::Queue<int> s21_queue_swap{il2};
  std::queue<int> std_queue{il1};
  std::queue<int> std_queue_swap{il2};
  s21_queue.swap(s21_queue_swap);
  std_queue.swap(std_queue_swap);
  EXPECT_EQ(s21_queue.size(), std_queue.size());
  EXPECT_EQ(s21_queue.front(), std_queue.front());
  EXPECT_EQ(s21_queue.back(), std_queue.back());
  EXPECT_EQ(s21_queue_swap.size(), std_queue_swap.size());
  EXPECT_EQ(s21_queue_swap.front(), std_queue_swap.front());
  EXPECT_EQ(s21_queue_swap.back(), std_queue_swap.back());
}