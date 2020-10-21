/*-
 * TODO FILEHEADER
 */

#pragma once
#ifndef KAMI_MULTIGRID2D_HXX
#define KAMI_MULTIGRID2D_HXX

#include <kami/KAMI_EXPORT.h>
#include <kami/agent.h>
#include <kami/domain.h>
#include <kami/grid.h>
#include <kami/grid2d.h>
#include <kami/kami.h>

namespace kami {

class KAMI_EXPORT MultiGrid2D : public Grid2D {
   public:
    MultiGrid2D(unsigned int, unsigned int, bool, bool);

    bool addAgent(AgentID, GridCoord2D);
};

}  // namespace kami

#endif  // KAMI_MULTIGRID2D_HXX
