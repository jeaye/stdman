/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing in LICENSE file, or at:
    http://www.opensource.org/licenses/MIT

  File: groff_section.hpp
  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

namespace groff_detail
{
  void section(std::vector<std::string> &lines)
  {
    for(auto &l : lines)
    {
      if
      (
       l.find("Contents") != std::string::npos ||
       l.find("Template parameters") != std::string::npos ||
       l.find("Type requirements") != std::string::npos ||
       l.find("Specializations") != std::string::npos ||
       l.find("Member types") != std::string::npos ||
       l.find("Member functions") != std::string::npos ||
       l.find("Member classes") != std::string::npos ||
       l.find("Element access") != std::string::npos ||
       l.find("Getting the result") != std::string::npos ||
       l.find("State") != std::string::npos ||
       l.find("Iterators") != std::string::npos ||
       l.find("Capacity") != std::string::npos ||
       l.find("Operations") != std::string::npos ||
       l.find("Search") != std::string::npos ||
       l.find("Member constants") != std::string::npos ||
       l.find("Constants") != std::string::npos ||
       l.find("Non-member functions") != std::string::npos ||
       l.find("Input/output") != std::string::npos ||
       l.find("Numeric conversions") != std::string::npos ||
       l.find("Literals") != std::string::npos ||
       l.find("Helper classes") != std::string::npos ||
       l.find("Helper types") != std::string::npos ||
       l.find("Parameters") != std::string::npos ||
       l.find("Return value") != std::string::npos ||
       l.find("Exceptions") != std::string::npos ||
       l.find("Example") != std::string::npos ||
       l.find("Complexity") != std::string::npos ||
       l.find("Notes") != std::string::npos ||
       l.find("Modifiers") != std::string::npos ||
       l.find("Lookup") != std::string::npos ||
       l.find("Observers") != std::string::npos ||
       l.find("Output:") != std::string::npos ||
       l.find("Possible output:") != std::string::npos ||
       l.find("Complexity") != std::string::npos ||
       l.find("Possible implementation") != std::string::npos ||
       l.find("First version") != std::string::npos ||
       l.find("Second version") != std::string::npos ||
       l.find("See also") != std::string::npos
      )
      {
        if(l.find("•") == std::string::npos)
        {
          std::string tmp{ l };
          str::trim(tmp);

          /* Lower case means false positive. */
          if(std::isupper(tmp[0]))
          { str::trim(l); } /* Move back to column 0 for sectioning. */
        }
      }

      if(l.size() && !std::isspace(l[0]) && l[0] != '.')
      { l = ".SH " + str::ltrim(l); }
    }
  }
}
