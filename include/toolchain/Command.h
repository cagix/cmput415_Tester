#ifndef TESTER_COMMAND_H
#define TESTER_COMMAND_H

#include "json.hpp"

#include "Colors.h"
#include "ExecutionState.h"
#include "toolchain/ExecutionState.h"

#include <filesystem>
#include <future>
#include <iostream>
#include <string>
#include <vector>

// Convenience.
using JSON = nlohmann::json;
namespace fs = std::filesystem;

namespace tester {

// A class representing a command in a toolchain.
class Command {
public:
  // No default constructor.
  Command() = delete;

  // Construct a command from JSON set up.
  Command(const JSON& json, int64_t timeout);

  // Copy constructor is default copy.
  Command(const Command& command) = default;

  // Destructor for removing temporary files
  ~Command() {}

  // Execute the command.
  ExecutionOutput execute(const ExecutionInput& ei) const;

  // Get the command name.
  std::string getName() const { return name; }

  // Ostream operator.
  friend std::ostream& operator<<(std::ostream&, const Command&);

  // TODO: move back to private
  std::string buildCommand(const ExecutionInput& input, const ExecutionOutput& output) const;

private:
  // Resolves magic parameters to values.
  fs::path resolveArg(const ExecutionInput& ei, const ExecutionOutput& eo, std::string arg) const;

  // Resolves magic exe parameters to value.
  fs::path resolveExe(const ExecutionInput& ei, const ExecutionOutput& eo, std::string exe) const;

private:
  // Command info.
  std::string name;
  fs::path exePath;
  fs::path runtimePath;
  std::vector<std::string> args;

  // Every command produces a file descriptor for each of these paths
  fs::path errPath;
  fs::path outPath;

  // The command can supply a output file to use instead of stdout/err 
  std::optional<fs::path> outputFile;

  // Uses runtime and uses input stream.
  bool usesRuntime, usesInStr;

  // Allow return with non-zero exit code.
  bool allowError;

  // Set up info.
  int64_t timeout;
};

} // End namespace tester

#endif // TESTER_COMMAND_H
