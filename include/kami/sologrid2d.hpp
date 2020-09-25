/*-
 * TODO FILEHEADER
 */

#pragma once
#ifndef KAMI_SOLOGRID2D_HPP
#define KAMI_SOLOGRID2D_HPP

#include <kami/agent.hpp>
#include <kami/domain.hpp>
#include <kami/grid.hpp>
#include <kami/grid2d.hpp>
#include <kami/kami.hpp>
#include <vector>

namespace kami {

class KAMI_EXPORT SoloGrid2D : public Grid2D {
   public:
    SoloGrid2D(unsigned int, unsigned int, bool, bool);

    bool addAgent(AgentID, GridCoord2D);
};

}  // namespace kami

#endif  // KAMI_SOLOGRID2D_HPP
