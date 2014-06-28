/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing in LICENSE file, or at:
    http://www.opensource.org/licenses/MIT

  File: render.hpp
  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <string>
#include <memory>
#include <array>
#include <unistd.h>

#include "parse_state.hpp"
#include "str.hpp"

class render
{
  public:
    void operator ()(parse_state &state)
    {
      /* Render the stripped html to plain text. */
      state.plain = execute("elinks -dump 1 -dump-width 90 -no-numbering -no-references "
                            "-dump-charset UTF-8 -force-html "
                            + state.tmp_file);

      /* Cleanup a bit. */
      str::replace(state.plain, "[edit]", "");
      str::replace(state.plain, "Run this code", "\n// Run this code");
      str::replace(state.plain, "\u200b", ""); /* I don't know why these show up... */
      str::replace(state.plain, "•", "*");
      str::replace(state.plain, "\u00a0", " "); /* NBSP sucks */
      str::replace(state.plain, "(constructor)", "constructor  ");
      str::replace(state.plain, "(destructor)", "destructor  ");
      str::replace(state.plain, "\\", "\\\\");
    }

  private:
    static std::string execute(std::string const &cmd)
    {
      std::unique_ptr<FILE, decltype(&pclose)> const pipe{ popen(cmd.c_str(), "r"),
                                                           &pclose };
      if(!pipe)
      { throw std::runtime_error("failed to execute command: " + cmd); }

      std::string output;
      char *res{};
      std::array<char, 2048> data;
      while((res = ::fgets(data.data(), data.size(), pipe.get())))
      { output += res; }
      return output;
    }
};
