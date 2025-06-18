#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <thread>

constexpr size_t N = 1000; // Size of the matrices
constexpr size_t NUM_CORES = 8; // Number of cores to use

int main() {
  //TIME THE PROGRAM
  auto start = std::chrono::high_resolution_clock::now();

  std::vector<std::vector<int>> matrix1(N, std::vector<int>(N));
  std::vector<std::vector<int>> matrix2(N, std::vector<int>(N));

  // Fill with random numbers
  std::mt19937 rng(time(0));
  std::uniform_int_distribution<int> dist(1, 700);

  // Initialize matrix1 and matrix2 with random values
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      matrix1[i][j] = dist(rng);
      matrix2[i][j] = dist(rng);
    }
  }

  std::vector<std::vector<int>> matrix2_T(N, std::vector<int>(N));
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      matrix2_T[j][i] = matrix2[i][j];
    }
  }

  size_t rows1 = matrix1.size();
  size_t cols1 = matrix1[0].size();
  size_t cols2 = matrix2[0].size();

  std::vector<std::vector<int>> result(rows1, std::vector<int>(cols2, 0));

  auto worker = [&](size_t start_row, size_t end_row) {
    for (size_t i = start_row; i < end_row; ++i) {
      for (size_t j = 0; j < N; ++j) {
        int sum = 0;
        for (size_t k = 0; k < N; ++k) {
          sum += matrix1[i][k] * matrix2_T[j][k];
        }
        result[i][j] = sum;
      }
    }
  };

  std::vector<std::thread> threads;
  size_t rows_per_thread = N / NUM_CORES;
  for (size_t t = 0; t < NUM_CORES; ++t) {
    size_t start_row = t * rows_per_thread;
    size_t end_row = (t == NUM_CORES - 1) ? N : start_row + rows_per_thread;
    threads.emplace_back(worker, start_row, end_row);
  }

  // Join threads
  for (auto& th : threads) {
    th.join();
  }


  /*std::cout << "Result of matrix multiplication:\n";
  for (const auto& row : result) {
    for (const auto& val : row) {
      std::cout << val << " ";
    }
    std::cout << "\n";
  }*/

  //TIME THE PROGRAM
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  std::cout << "Elapsed time: " << elapsed.count() << " seconds\n";

  return 0;
}