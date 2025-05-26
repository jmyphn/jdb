#include <iostream>
#include "include/common/db_instance.hpp"

int main() {
  db::DbInstance db_instance("example.db");
  std::cout << "Hello World!" << std::endl;
  return 0;
}