/*-
 * TODO FILEHEADER
 */

#pragma once
#ifndef KAMI_MULTIGRID3D_HXX
#define KAMI_MULTIGRID3D_HXX

#include <kami/KAMI_EXPORT.h>
#include <kami/agent.h>
#include <kami/domain.h>
#include <kami/grid.h>
#include <kami/grid3d.h>
#include <kami/kami.h>

namespace kami {

class LIBKAMI_EXPORT MultiGrid3D : public Grid3D {
   public:
    MultiGrid3D(unsigned int, unsigned int, unsigned int, bool, bool, bool);

    bool addAgent(AgentID, GridCoord3D);
};

}  // namespace kami

#endif  // KAMI_MULTIGRID3D_HXX
