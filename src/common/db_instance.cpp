#include "common/db_instance.hpp"
#include <iostream>
#include <string>

namespace db {
  DbInstance::DbInstance(const std::string& db_file_name) {
    this->db_file_name = db_file_name;
    std::cout << db_file_name << " database instance created." << std::endl;
  }
}