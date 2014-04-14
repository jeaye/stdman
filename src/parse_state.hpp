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

struct parse_state
{
  std::string const name{ "cppman" };
  std::string const version{ "1.0.0" };
  std::string const creation_date{ "April 11, 2014" };

  std::string prog;
  std::string input_file, output_file;
  std::string tmp_file{ ".tmp.html" }, output_dir{ "./man/" };
  std::string html;
  std::string plain;
  std::vector<std::string> lines;
};
