/*-
 * TODO FILEHEADER
 */

#pragma once
#ifndef KAMI_MULTIGRID3D_HPP
#define KAMI_MULTIGRID3D_HPP

#include <kami/agent.hpp>
#include <kami/domain.hpp>
#include <kami/grid.hpp>
#include <kami/grid3d.hpp>
#include <kami/kami.hpp>

namespace kami {

class KAMI_EXPORT MultiGrid3D : public Grid3D {
   public:
    MultiGrid3D(unsigned int, unsigned int, unsigned int, bool, bool, bool);

    bool addAgent(AgentID, GridCoord3D);
};

}  // namespace kami

#endif  // KAMI_MULTIGRID3D_HPP
