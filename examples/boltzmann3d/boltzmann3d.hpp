/*-
 * TODO FILEHEADER
 */

#pragma once
#ifndef BOLTZMAN3D_HPP
#define BOLTZMAN3D_HPP

#include <iostream>
#include <kami/agent.hpp>
#include <kami/kami.hpp>
#include <kami/multigrid3d.hpp>
#include <kami/random.hpp>
#include <map>
#include <random>

class MoneyAgent : public kami::Agent {
   public:
    MoneyAgent();

    void step();

    static void setWorld(kami::MultiGrid3D *w);
    static void setModel(class BoltzmannWealthModel *m);

    void moveAgent();

    int getWealth();
    void setWealth(int newWealth);
    void giveMoney();

    void prinfo(void) const;

   private:
    static kami::MultiGrid3D *world;
    static BoltzmannWealthModel *model;
    int stepCounter;
    int agentWealth;
};

class BoltzmannWealthModel : public kami::Model {
   public:
    BoltzmannWealthModel(unsigned int = 1000, unsigned int = 10, unsigned int = 10, unsigned int = 10);
    ~BoltzmannWealthModel();
    void step();
    void run(unsigned int n);
    void prinfo(void) const;

    MoneyAgent *getAgentByID(kami::AgentID agentID) const;

   private:
    std::map<kami::AgentID, MoneyAgent *> agentList;
    kami::RandomScheduler *sched;
    kami::MultiGrid3D *world;
    unsigned int stepCount;
};

#endif  // BOLTZMAN_HPP
