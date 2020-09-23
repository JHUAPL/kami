/*-
 * TODO FILEHEADER
 */

#pragma once
#ifndef KAMI_SOLOGRID1D_HPP
#define KAMI_SOLOGRID1D_HPP

#include <kami/agent.hpp>
#include <kami/domain.hpp>
#include <kami/grid.hpp>
#include <kami/grid1d.hpp>
#include <kami/kami.hpp>

namespace kami {

class SoloGrid1D : public Grid1D {
   public:
    SoloGrid1D(unsigned int, bool);

    bool addAgent(AgentID, GridCoord1D);
};
}  // namespace kami

#endif  // KAMI_SOLOGRID1D_HPP
