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
      auto const beg(find(html, "<!-- content -->"));
      html.erase(0, beg);
      auto const end(find(html, "<!-- /content -->"));
      html.erase(end);

      /* Delete unused sections. */
      erase(html, "<!-- printfooter -->", "<!-- /printfooter -->");
      erase(html, "<!-- tagline -->", "<!-- bodycontent -->");
      erase(html, "<!-- /firstHeading -->", R"raw(<table class="t-dcl-begin">)raw");

      /* Add some extra line breaks in these spans. */
      str::replace(html, "<span>", "<span><br/>");

      std::ofstream ofs{ state.tmp_file };
      if(!ofs.is_open())
      { throw std::runtime_error("failed to open file for writing: " + state.tmp_file); }
      ofs << html << std::endl;
    }

  private:
    static size_t find(std::string const &s, std::string const &term)
    {
      auto const it(s.find(term));
      if(it == std::string::npos)
      { throw std::runtime_error("malformed data: " + term); }
      return it;
    }
    static void erase(std::string &html, std::string const &begin, std::string const &end)
    {
      auto const it(find(html, begin));
      auto const it2(find(html, end));
      html.erase(html.begin() + it, html.begin() + it2);
    }
};
