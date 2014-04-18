/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing in LICENSE file, or at:
    http://www.opensource.org/licenses/MIT

  File: parse_state.hpp
  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <string>
#include <vector>
#include <unistd.h>

struct parse_state
{
  std::string const name{ "stdman" };
  std::string const version{ "1.0.0" };
  std::string const creation_date{ __DATE__ }; /* Relies on `make generate` for usage. */

  std::string prog;
  std::string input_file, output_file;
  std::string tmp_file{ "tmp/" + std::to_string(getpid()) + ".tmp.html" };
  std::string output_dir{ "./man/" };
  std::string html;
  std::string plain;
  std::vector<std::string> lines;
  bool verbose{ true };
};
