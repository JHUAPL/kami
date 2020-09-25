/*-
 * TODO FILEHEADER
 */

#pragma once
#ifndef KAMI_MULTIGRID2D_HPP
#define KAMI_MULTIGRID2D_HPP

#include <kami/KAMI_EXPORT.hpp>
#include <kami/agent.hpp>
#include <kami/domain.hpp>
#include <kami/grid.hpp>
#include <kami/grid2d.hpp>
#include <kami/kami.hpp>

namespace kami {

class KAMI_EXPORT MultiGrid2D : public Grid2D {
   public:
    MultiGrid2D(unsigned int, unsigned int, bool, bool);

    bool addAgent(AgentID, GridCoord2D);
};

}  // namespace kami

#endif  // KAMI_MULTIGRID2D_HPP
