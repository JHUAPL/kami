/*-
 * Copyright (c) 2020 The Johns Hopkins University Applied Physics
 * Laboratory LLC
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <algorithm>
#include <memory>
#include <optional>
#include <random>
#include <utility>
#include <vector>

#include <kami/model.h>
#include <kami/random.h>
#include <kami/sequential.h>

namespace kami {

    RandomScheduler::RandomScheduler(std::shared_ptr<std::ranlux24> rng) {
        this->_rng = std::move(rng);
    }

    std::optional<std::unique_ptr<std::vector<AgentID>>>
    RandomScheduler::step(std::shared_ptr<Model> model, std::unique_ptr<std::vector<AgentID>> agent_list) {
        if (_rng == nullptr)
            return std::nullopt;

        shuffle(agent_list->begin(), agent_list->end(), *_rng);
        return std::move(this->SequentialScheduler::step(model, std::move(agent_list)));
    }

    std::shared_ptr<std::ranlux24> RandomScheduler::set_rng(std::shared_ptr<std::ranlux24> rng) {
        this->_rng = std::move(rng);
        return _rng;
    }

    std::shared_ptr<std::ranlux24> RandomScheduler::get_rng() { return (this->_rng); }

}  // namespace kami
