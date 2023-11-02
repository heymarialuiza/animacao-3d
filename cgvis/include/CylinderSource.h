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
// OVERVIEW: CylinderSource.h
// ========
// Class definition for vis cylinder source.
//
// Author: Paulo Pagliosa
// Last revision: 11/03/2022

#ifndef __CylinderSource_h
#define __CylinderSource_h

#include "Source.h"
#include "TriCellMesh.h"

namespace cg::vis
{ // begin namespace cg::vis


/////////////////////////////////////////////////////////////////////
//
// CylinderSource: vis cylinder source class
// ==============
class CylinderSource: public Source<TriCellMesh>
{
public:
  static constexpr auto maxResolution = 32;

  static Reference<CylinderSource> New()
  {
    return new CylinderSource;
  }

  void setResolution(int resolution)
  {
    resolution = math::clamp(resolution, 3, maxResolution);
    if (resolution != _resolution)
    {
      _resolution = resolution;
      this->modified();
    }
  }

private:
  int _resolution{16};

  void execute() override;

}; // CylinderSource

} // end namespace cg::vis

#endif // __CylinderSource_h
