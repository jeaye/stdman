/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing in LICENSE file, or at:
    http://www.opensource.org/licenses/MIT

  File: cmdline.hpp
  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

#include "parse_state.hpp"
#include "exception.hpp"

struct cmdline
{
  public:
    using iterator = std::vector<std::string>::iterator;

    void operator ()(parse_state &state, int argc, char **argv)
    {
      state.prog = argv[0];
      --argc, ++argv;
      if(argc == 0)
      { throw helper{ state.prog }; }

      std::vector<std::string> args;
      std::copy(argv, argv + argc, std::back_inserter(args));

      auto const end(args.end());
      for(auto i(args.begin()); i != end; ++i)
      {
        bool read{};
        read |= param_help(state, i, end);
        if(!read)
        { read |= param_version(state, i, end); }
        if(!read)
        { read |= param_output(state, i, end); }
        if(!read)
        { read |= param_input(state, i, end); }

        if(!read)
        { throw invalid_cmdline(state.prog, "unknown argument: " + *i); }
      }

      if(state.input_file.empty())
      { throw helper{ state.prog }; }
      std::cout << "input: " << state.input_file << std::endl;
    }
  private:
    static bool param_help(parse_state &state, iterator &arg, iterator const&)
    {
      if(*arg == "-h" || *arg == "--help")
      { throw helper{ state.prog }; }
      return false;
    }
    static bool param_version(parse_state &state, iterator &arg, iterator const&)
    {
      if(*arg == "-v" || *arg == "--version")
      {
        std::cout << state.name << ":" << state.version << std::endl;
        throw early_exit{};
      }
      return false;
    }
    static bool param_output(parse_state &state, iterator &arg, iterator const &end)
    {
      if(*arg == "-o" || *arg == "--output")
      {
        if((arg + 1) != end)
        {
          state.output_file = *++arg;
          return true;
        }
        else
        { throw invalid_cmdline{ state.prog, "-o/--output requires a parameter" }; }
      }
      else if(*arg == "-d" || *arg == "--directory")
      {
        if((arg + 1) != end)
        {
          state.output_dir = *++arg + "/";
          return true;
        }
        else
        { throw invalid_cmdline{ state.prog, "-d/--directory requires a parameter" }; }
      }
      return false;
    }
    static bool param_input(parse_state &state, iterator &arg, iterator const &end)
    {
      if(!state.input_file.empty()) /* Extra shit on the cmdline. */
      { throw invalid_cmdline{ state.prog, "superfluous argument: " + *arg }; }
      state.input_file = *arg;

      if(std::distance(arg, end) > 1)
      { throw invalid_cmdline{ state.prog, "input file must be specified last" }; }
      return true;
    }
};
