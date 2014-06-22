/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing in LICENSE file, or at:
    http://www.opensource.org/licenses/MIT

  File: groff.hpp
  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <iterator>

#include "str.hpp"
#include "parse_state.hpp"
#include "groff_section.hpp"
#include "groff_highlight.hpp"

class groff
{
  public:
    void operator ()(parse_state &state)
    {
      state.lines = get_lines(state.plain);
      if(state.lines.size() < 2)
      { throw std::runtime_error("insufficient lines in plain render"); }

      std::string name{ state.lines[0] };
      str::replace(str::trim(name), " ", ""); /* Don't allow spaces in the filename. */
      if(state.output_file.empty())
      { state.output_file = state.output_dir + name + ".3"; }

      /* First two lines are always the same. */
      state.lines[0] = ".TH " + name + " 3 "
                       "\"" + state.creation_date + "\" \"" + state.version + "\" "
                       "\"C++ Standard Libary | http://cppreference.com\"";
      state.lines[1] = "Synopsis";

      groff_detail::section(state.lines);
      groff_detail::highlight(state.lines);

      /* Remove the contents section entirely */
      auto const contents(std::find_if(state.lines.begin(), state.lines.end(),
      [](std::string const &l)
      { return l.find(".SH Contents") != std::string::npos; }));
      if(contents != state.lines.end())
      {
        auto const next_section(std::find_if(contents + 1, state.lines.end(), 
        [](std::string const &l)
        { return l.find(".SH") != std::string::npos; }));
        if(next_section != state.lines.end())
        { state.lines.erase(contents, next_section); }
        else
        { state.lines.erase(contents, state.lines.end()); }
      }


      std::ofstream ofs{ state.output_file };
      if(state.verbose)
      { std::cout << "output: " << state.output_file << std::endl; }
      if(!ofs.is_open())
      { throw std::runtime_error("failed to open file for writing: " + state.output_file); }
      std::copy(std::begin(state.lines), std::end(state.lines),
                std::ostream_iterator<std::string>(ofs, "\n"));
    }

  private:
    std::vector<std::string> get_lines(std::string const &plain)
    {
      std::stringstream ss{ plain };
      std::vector<std::string> lines;
      std::string line;
      while(std::getline(ss, line))
      { lines.push_back(std::move(line)); }
      return lines;
    }
};
