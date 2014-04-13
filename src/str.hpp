/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing in LICENSE file, or at:
    http://www.opensource.org/licenses/MIT

  File: str.hpp
  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

#include <string>
#include <algorithm>

namespace str
{
  void replace(std::string &str, std::string const &from, std::string const &to)
  {
    if(from.empty() || str.empty())
    { return; }

    for(size_t start_pos{}; (start_pos = str.find(from, start_pos)) != std::string::npos; )
    {
      str.replace(start_pos, from.length(), to);
      start_pos += to.length(); /* In case 'to' contains 'from', like replacing 'x' with 'yx'. */
    }
  }

  static std::string& ltrim(std::string &s)
  {
    auto const found(std::find_if_not(s.begin(), s.end(), [](char const c)
    { return std::isspace(c); }));

    s.erase(s.begin(), found);
    return s;
  }
  static std::string& rtrim(std::string &s)
  {
    auto const found(std::find_if_not(s.rbegin(), s.rend(), [](char const c)
    { return std::isspace(c); }));

    s.erase(found.base(), s.end());
    return s;
  }
  static std::string& trim(std::string &s)
  { return rtrim(ltrim(s)); }
}
