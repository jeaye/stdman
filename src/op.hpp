/*
  Copyright © 2014 Jesse 'Jeaye' Wilkerson
  See licensing in LICENSE file, or at:
    http://www.opensource.org/licenses/MIT

  File: op.hpp
  Author: Jesse 'Jeaye' Wilkerson
*/

#pragma once

template <typename Op, typename State, typename... Args>
void op(State &state, Args &&... args)
{
  Op o{};
  o(state, std::forward<Args>(args)...);
}
