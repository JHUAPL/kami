/*-
 * Copyright (c) 2022 The Johns Hopkins University Applied Physics
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

#include <memory>
#include <utility>

#include <kami/error.h>
#include <kami/model.h>
#include <kami/scheduler.h>

namespace kami {

    std::shared_ptr<Domain> Model::get_domain() {
        if (_domain == nullptr)
            throw error::ResourceNotAvailable("Domain not found in model");
        return _domain;
    }

    std::shared_ptr<Domain> Model::set_domain(std::shared_ptr<Domain> domain) {
        _domain = std::move(domain);
        return _domain;
    }

    std::shared_ptr<Population> Model::get_population() {
        if (_pop == nullptr)
            throw error::ResourceNotAvailable("Population not found in model");
        return _pop;
    }

    std::shared_ptr<Population> Model::set_population(std::shared_ptr<Population> population) {
        _pop = std::move(population);
        return _pop;
    }

    std::shared_ptr<Scheduler> Model::get_scheduler() {
        if (_sched == nullptr)
            throw error::ResourceNotAvailable("Scheduler not found in model");
        return _sched;
    }

    std::shared_ptr<Scheduler> Model::set_scheduler(std::shared_ptr<Scheduler> scheduler) {
        _sched = std::move(scheduler);
        return _sched;
    }

    std::shared_ptr<Model> Model::step() {
        _sched->step(shared_from_this());
        return shared_from_this();
    }

}  // namespace kami
