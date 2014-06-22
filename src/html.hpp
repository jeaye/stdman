/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing in LICENSE file, or at:
    http://www.opensource.org/licenses/MIT

  File: html.hpp
  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <string>
#include <fstream>
#include <stdexcept>

#include "str.hpp"
#include "parse_state.hpp"

class html
{
  public:
    void operator ()(parse_state &state)
    {
      /* Read whole file. */
      std::string &html(state.html);
      {
        std::ifstream ifs{ state.input_file };
        if(!ifs.is_open())
        { throw std::runtime_error("cannot open file: " + state.input_file); }
        ifs.seekg(0, std::ios::end);
        html.resize(ifs.tellg());
        ifs.seekg(0, std::ios::beg);
        ifs.read(&html[0], html.size());
      }

      /* Delete unused header/footer. */
      auto const beg(str::find(html, "<!-- content -->"));
      html.erase(0, beg);
      auto const end(str::find(html, "<!-- /content -->"));
      html.erase(end);

      /* Delete unused sections. */
      str::erase(html, "<!-- printfooter -->", "<!-- /printfooter -->");
      str::erase(html, "<!-- tagline -->", "<!-- bodycontent -->");
      str::erase(html, "<!-- /firstHeading -->", R"raw(<table class="t-dcl-begin">)raw");

      /* Add some extra line breaks in these spans. */
      str::replace(html, "<span>", "<span><br/>");
      str::replace(html, "\u00a0", " "); /* NBSP sucks */

      std::ofstream ofs{ state.tmp_file };
      if(!ofs.is_open())
      { throw std::runtime_error("failed to open file for writing: " + state.tmp_file); }
      ofs << html << std::endl;
    }
};
