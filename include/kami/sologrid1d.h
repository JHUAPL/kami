/*-
 * TODO FILEHEADER
 */

#pragma once
#ifndef KAMI_SOLOGRID1D_HXX
#define KAMI_SOLOGRID1D_HXX

#include <kami/KAMI_EXPORT.h>
#include <kami/agent.h>
#include <kami/domain.h>
#include <kami/grid.h>
#include <kami/grid1d.h>
#include <kami/kami.h>

namespace kami {

class KAMI_EXPORT SoloGrid1D : public Grid1D {
   public:
    SoloGrid1D(unsigned int, bool);

    bool addAgent(AgentID, GridCoord1D);
};
}  // namespace kami

#endif  // KAMI_SOLOGRID1D_HXX
