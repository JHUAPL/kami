/*-
 * TODO FILEHEADER
 */

#pragma once
#ifndef KAMI_MULTIGRID1D_HXX
#define KAMI_MULTIGRID1D_HXX

#include <kami/KAMI_EXPORT.h>
#include <kami/agent.h>
#include <kami/domain.h>
#include <kami/grid.h>
#include <kami/grid1d.h>
#include <kami/kami.h>

namespace kami {

class LIBKAMI_EXPORT MultiGrid1D : public Grid1D {
   public:
    MultiGrid1D(unsigned int, bool);

    bool addAgent(AgentID, GridCoord1D);
};

}  // namespace kami

#endif  // KAMI_MULTIGRID1D_HXX
