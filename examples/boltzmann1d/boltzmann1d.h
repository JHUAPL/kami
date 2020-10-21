/*-
 * TODO FILEHEADER
 */

#pragma once
#ifndef BOLTZMAN1D_HPP
#define BOLTZMAN1D_HPP

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
    BoltzmannWealthModel(unsigned int = 10, unsigned int = 10);
    ~BoltzmannWealthModel();

    void step();
    void run(unsigned int n);
    void prinfo(void) const;

    MoneyAgent *getAgentByID(AgentID agentID) const;

   private:
    map<AgentID, MoneyAgent *> agentList;
    RandomScheduler *sched;
    MultiGrid1D *world;
    unsigned int stepCount;
};

#endif  // BOLTZMAN1D_HPP
