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
  inline void replace(std::string &str, std::string const &from, std::string const &to)
  {
    if(from.empty() || str.empty())
    { return; }

    for(size_t start_pos{}; (start_pos = str.find(from, start_pos)) != std::string::npos; )
    {
      str.replace(start_pos, from.length(), to);
      start_pos += to.length();
    }
  }

  inline std::string& ltrim(std::string &s)
  {
    auto const found(std::find_if_not(s.begin(), s.end(), [](char const c)
    { return std::isspace(c); }));

    s.erase(s.begin(), found);
    return s;
  }

  inline std::string& rtrim(std::string &s)
  {
    auto const found(std::find_if_not(s.rbegin(), s.rend(), [](char const c)
    { return std::isspace(c); }));

    s.erase(found.base(), s.end());
    return s;
  }

  inline std::string& trim(std::string &s)
  { return rtrim(ltrim(s)); }

  inline size_t find(std::string const &s, std::string const &term)
  {
    auto const it(s.find(term));
    if(it == std::string::npos)
    { throw std::runtime_error("malformed data: " + term); }
    return it;
  }

  inline void erase(std::string &s, std::string const &begin, std::string const &end)
  {
    auto const it(find(s, begin));
    auto const it2(find(s, end));
    s.erase(s.begin() + it, s.begin() + it2);
  }
}
