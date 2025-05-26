#pragma once
#include <string>

namespace db {
  class DbInstance {
    public:
      std::string db_file_name;
      explicit DbInstance(const std::string& db_file_name);
      ~DbInstance() = default;
  };
} // namespace db