#ifndef TESTER_TEST_HARNESS_H
#define TESTER_TEST_HARNESS_H

#include "toolchain/TestPair.h"
#include "toolchain/ToolChain.h"

#include "json.hpp"

#include <string>
#include <vector>

// Convenience.
using JSON = nlohmann::json;

namespace tester {

// Test file typedefs.
typedef std::vector<TestPair> TestList;
typedef std::map<std::string, TestList> TestSet;

// Class that manages finding tests and running them.
class TestHarness {
public:
  // No default constructor.
  TestHarness() = delete;

  // Construct the Tester with a parsed JSON file.
  explicit TestHarness(const JSON &json);

  // Run the found tests.
  void runTests();

private:
  // Runs a single test.
  void runTest(const TestPair &tp);

private:
  ToolChain toolchain;
  TestSet tests;
};

} // End namespace tester

#endif //TESTER_TESTER_H
