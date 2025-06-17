#include <iostream>
#include <memory>

template<typename T>
struct Test {
  T value; 
  
  /*NOTE TO SELF: auto doesn't work, because it has to be a type, not a value. 
  auto would work if we defined it in the struct like: auto value = 23; 
  That's why we use T value rather then auto value*/

  Test(T val) : value(val) {} // Constructor to initialize value

  void display() const {
	  std::cout << "Value: " << value << std::endl;
  }
};

int main() {
  //testing the -> syntax in c++
  std::unique_ptr<Test<int>> testPtr = std::make_unique<Test<int>>(42);  // Dynamically allocate a Test<int> object (using int)
  std::unique_ptr<Test<float>> testPtrfloat = std::make_unique<Test<float>>(42.12f);
  std::unique_ptr<Test<char>> testPtrchar = std::make_unique<Test<char>>('A');

  testPtr->display();  // Using -> to access member function
  testPtrfloat->display();
  testPtrchar->display();

  // No need for delete for unique_ptr as it automatically manages memory
  return 0;
}
