/*-
 * TODO FILEHEADER
 */

#pragma once
#ifndef BOLTZMAN1D_HPP
#define BOLTZMAN1D_HPP

#include <iostream>
#include <kami/agent.hpp>
#include <kami/kami.hpp>
#include <kami/multigrid1d.hpp>
#include <kami/random.hpp>
#include <map>
#include <random>

class MoneyAgent : public kami::Agent {
   public:
    MoneyAgent();
    ~MoneyAgent();

    void step();

    static void setWorld(kami::MultiGrid1D *w);
    static void setModel(class BoltzmannWealthModel *m);

    void moveAgent();

    int getWealth();
    void setWealth(int newWealth);
    void giveMoney();

    void prinfo(void) const;

   private:
    static kami::MultiGrid1D *world;
    static BoltzmannWealthModel *model;
    static std::random_device *rd;
    static std::mt19937 *rng;
    int stepCounter;
    int agentWealth;
};

class BoltzmannWealthModel : public kami::Model {
   public:
    BoltzmannWealthModel(unsigned int = 10, unsigned int = 10);
    ~BoltzmannWealthModel();
    void step();
    void run(unsigned int n);
    void prinfo(void) const;

    MoneyAgent *getAgentByID(kami::AgentID agentID) const;

   private:
    std::map<kami::AgentID, MoneyAgent *> agentList;
    kami::RandomScheduler *sched;
    kami::MultiGrid1D *world;
    unsigned int stepCount;
};

#endif  // BOLTZMAN1D_HPP
