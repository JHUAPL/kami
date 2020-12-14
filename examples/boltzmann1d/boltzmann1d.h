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
#ifndef BOLTZMAN1D_H
#define BOLTZMAN1D_H

#include <iostream>
#include <kami/agent.h>
#include <kami/kami.h>
#include <kami/multigrid1d.h>
#include <kami/random.h>
#include <map>

using namespace kami;
using namespace std;

class MoneyAgent : public Agent {
   public:
    MoneyAgent();

    void step();

    static void setWorld(MultiGrid1D *w);
    static void setModel(class BoltzmannWealthModel *m);

    void moveAgent();

    int getWealth();
    void setWealth(int newWealth);
    void giveMoney();

    void prinfo(void) const;

   private:
    static MultiGrid1D *world;
    static BoltzmannWealthModel *model;
    int stepCounter;
    int agentWealth;
};

class BoltzmannWealthModel : public Model {
   public:
    BoltzmannWealthModel(unsigned int numberAgents = 10, unsigned int lengthX = 10, unsigned int newSeed = 42);
    ~BoltzmannWealthModel();

    void step();
    void run(unsigned int n);
    void prinfo(void) const;
    int getSeed() const;

    MoneyAgent *getAgentByID(AgentID agentID) const;

   private:
    map<AgentID, MoneyAgent *> agentList;
    RandomScheduler *sched;
    MultiGrid1D *world;
    unsigned int stepCount;
};

#endif  // BOLTZMAN1D_H
