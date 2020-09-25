/*-
 * TODO FILEHEADER
 */

#pragma once
#ifndef KAMI_MULTIGRID1D_HPP
#define KAMI_MULTIGRID1D_HPP

#include <kami/agent.hpp>
#include <kami/domain.hpp>
#include <kami/grid.hpp>
#include <kami/grid1d.hpp>
#include <kami/kami.hpp>

namespace kami {

class KAMI_EXPORT MultiGrid1D : public Grid1D {
   public:
    MultiGrid1D(unsigned int, bool);

    bool addAgent(AgentID, GridCoord1D);
};

}  // namespace kami

#endif  // KAMI_MULTIGRID1D_HPP
