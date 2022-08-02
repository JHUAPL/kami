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

#pragma once
#ifndef KAMI_MODEL_H
#define KAMI_MODEL_H

#include <memory>

#include <kami/domain.h>
#include <kami/kami.h>
#include <kami/population.h>
#include <kami/scheduler.h>

namespace kami {

/**
 * An abstract for generic models
 */
    class LIBKAMI_EXPORT Model : public std::enable_shared_from_this<Model> {
    protected:
        std::shared_ptr<Domain> _domain = nullptr;
        std::shared_ptr<Population> _pop = nullptr;
        std::shared_ptr<Scheduler> _sched = nullptr;

    public:
        /**
         * Execute a fixed number of time-steps for the model.
         *
         * This function should execute a fixed number of time-steps for the model.
         *
         * @param[in] n the number of time steps to execute.
         */
        virtual void run(unsigned int n) = 0;

        /**
         * Execute a single time-step for the model.
         *
         * This function should step the model instance.  Any activities that the
         * model should perform as part of its time step should be in this function.
         */
        virtual void step() = 0;

        /**
         * @brief Get the `Domain` associated with this model
         */
        std::shared_ptr<Domain> get_domain();

        /**
         * @brief Add a `Domain` to this scheduler
         *
         * @details This method will associate a model with the
         * scheduler.
         */
        void set_domain(std::shared_ptr<Domain> domain);

        /**
         * @brief Get the `Population` associated with this model
         */
        std::shared_ptr<Population> get_population();

        /**
         * @brief Add a `Model` to this scheduler
         *
         * @details This method will associate a model with the
         * scheduler.
         */
        void set_population(std::shared_ptr<Population> population);

        /**
         * @brief Get the `Scheduler` associated with this model
         */
        std::shared_ptr<Scheduler> get_scheduler();

        /**
         * @brief Add a `Model` to this scheduler
         *
         * @details This method will associate a model with the
         * scheduler.
         */
        void set_scheduler(std::shared_ptr<Scheduler> scheduler);
    };

}  // namespace kami

#endif  // KAMI_MODEL_H
