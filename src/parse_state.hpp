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

#define STR_(x) #x
#define STR(x) STR_(x)

struct parse_state
{
  std::string const name{ "stdman" };
  std::string const version{ STR(STDMAN_VERSION) };

  std::string prog;
  std::string input_file, output_file;
  std::string tmp_file{ "tmp/" + std::to_string(getpid()) + ".tmp.html" };
  std::string output_dir{ "./man/" };
  std::string html;
  std::string plain;
  std::vector<std::string> lines;
  bool verbose{ true };
};
