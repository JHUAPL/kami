/*-
 * TODO FILEHEADER
 */

#pragma once
#ifndef KAMI_SOLOGRID2D_H
#define KAMI_SOLOGRID2D_H

#include <kami/KAMI_EXPORT.h>
#include <kami/agent.h>
#include <kami/domain.h>
#include <kami/grid.h>
#include <kami/grid2d.h>
#include <kami/kami.h>
#include <vector>

namespace kami {

class LIBKAMI_EXPORT SoloGrid2D : public Grid2D {
   public:
    SoloGrid2D(unsigned int, unsigned int, bool, bool);

    bool addAgent(AgentID, GridCoord2D);
};

}  // namespace kami

#endif  // KAMI_SOLOGRID2D_H
