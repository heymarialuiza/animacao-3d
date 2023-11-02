//[]---------------------------------------------------------------[]
//|                                                                 |
//| Copyright (C) 2022 Paulo Pagliosa.                              |
//|                                                                 |
//| This software is provided 'as-is', without any express or       |
//| implied warranty. In no event will the authors be held liable   |
//| for any damages arising from the use of this software.          |
//|                                                                 |
//| Permission is granted to anyone to use this software for any    |
//| purpose, including commercial applications, and to alter it and |
//| redistribute it freely, subject to the following restrictions:  |
//|                                                                 |
//| 1. The origin of this software must not be misrepresented; you  |
//| must not claim that you wrote the original software. If you use |
//| this software in a product, an acknowledgment in the product    |
//| documentation would be appreciated but is not required.         |
//|                                                                 |
//| 2. Altered source versions must be plainly marked as such, and  |
//| must not be misrepresented as being the original software.      |
//|                                                                 |
//| 3. This notice may not be removed or altered from any source    |
//| distribution.                                                   |
//|                                                                 |
//[]---------------------------------------------------------------[]
//
// OVERVIEW: Exception
// ========
// Source file for common exceptions.
//
// Author: Paulo Pagliosa
// Last revision: 14/12/2022

#include "core/Exception.h"
#include <cstdarg>
#include <cstdio>

namespace cg
{ // begin namespace cg

void
runtimeError(const char* format, ...)
{
  constexpr auto bufferSize = 4096;
  char buffer[bufferSize];
  va_list args;

  va_start(args, format);
  std::vsnprintf(buffer, bufferSize, format, args);
  throw std::runtime_error{buffer};
}

std::logic_error
bad_invocation(const char* c, const char* f)
{
  constexpr auto maxLen = 128;
  char buffer[maxLen];

  snprintf(buffer, maxLen, "%s::%s() invoked", c, f);
  return std::logic_error{buffer};
}

} // begin namespace cg
