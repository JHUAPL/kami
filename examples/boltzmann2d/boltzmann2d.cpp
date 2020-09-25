/*-
 * TODO FILEHEADER
 */

#include "boltzmann2d.hpp"

#include <stdlib.h>

#include <iostream>
#include <kami/kami.hpp>
#include <kami/grid2d.hpp>
#include <kami/multigrid2d.hpp>
#include <map>

kami::MultiGrid2D *MoneyAgent::world = nullptr;
BoltzmannWealthModel *MoneyAgent::model = nullptr;

MoneyAgent::MoneyAgent() {
    stepCounter = 0;
    agentWealth = 1;
}

void MoneyAgent::step() {
    stepCounter++;

    moveAgent();
    if (agentWealth > 0)
        giveMoney();
}

void MoneyAgent::setWorld(kami::MultiGrid2D *w) {
    world = w;
}

void MoneyAgent::setModel(class BoltzmannWealthModel *m) {
    model = m;
}

void MoneyAgent::moveAgent() {
    auto agentID = this->getAgentID();
    auto moveList = world->getNeighborhood(agentID, kami::GridNeighborhoodType::Moore, false);
    auto newLocation = moveList[static_cast<unsigned int>(rand()) % moveList.size()];

    world->moveAgent(agentID, newLocation);
}

int MoneyAgent::getWealth() {
    return agentWealth;
}

void MoneyAgent::setWealth(int newWealth) {
    agentWealth = newWealth;
}

void MoneyAgent::giveMoney() {
    kami::AgentID agentID = getAgentID();
    kami::GridCoord2D location = world->getLocationByAgent(agentID);
    std::vector<kami::AgentID> *cellMates = world->getCellContents(location);

    if (cellMates->size() > 1) {
        kami::AgentID otherAgentID = cellMates->at(static_cast<unsigned int>(rand()) % cellMates->size());
        auto otherAgent = model->getAgentByID(otherAgentID);

        otherAgent->agentWealth += 1;
        agentWealth -= 1;
    }
}

void MoneyAgent::prinfo(void) const {
    kami::AgentID agentID = getAgentID();
    kami::GridCoord2D location = world->getLocationByAgent(agentID);

    std::cout << "  agent: " << agentID << " step: " << stepCounter << " wealth: " << agentWealth << " location: " << location << std::endl;
}

BoltzmannWealthModel::BoltzmannWealthModel(unsigned int numberAgents, unsigned int lengthX, unsigned int lengthY) {
    world = new kami::MultiGrid2D(lengthX, lengthY, true, true);
    sched = new kami::RandomScheduler(this);

    stepCount = 0;
    MoneyAgent::setWorld(world);
    MoneyAgent::setModel(this);

    for (unsigned int i = 0; i < numberAgents; i++) {
        MoneyAgent *newAgent = new MoneyAgent();

        agentList.insert(std::pair<kami::AgentID, MoneyAgent *>(newAgent->getAgentID(), newAgent));
        sched->addAgent(newAgent->getAgentID());
        world->addAgent(newAgent->getAgentID(),
                        kami::GridCoord2D(rand() % static_cast<int>(lengthX),
                                          rand() % static_cast<int>(lengthY)));
    }
}

BoltzmannWealthModel::~BoltzmannWealthModel() {
    for (auto agentPair = agentList.begin(); agentPair != agentList.end(); agentPair++) {
        delete agentPair->second;
    }

    delete sched;
    delete world;
}

void BoltzmannWealthModel::step() {
    stepCount++;
    sched->step();
}

void BoltzmannWealthModel::run(unsigned int n) {
    for (unsigned int i = 0; i < n; i++)
        step();
}

void BoltzmannWealthModel::prinfo(void) const {
    std::cout << " step: " << stepCount << std::endl
              << " agentinfo: " << std::endl;
    for (auto agent = agentList.begin(); agent != agentList.end(); ++agent) {
        agent->second->prinfo();
    }
}

MoneyAgent *BoltzmannWealthModel::getAgentByID(kami::AgentID agentID) const {
    MoneyAgent *agentPair = agentList.at(agentID);

    return agentPair;
}

int main(void) {
    BoltzmannWealthModel model(100, 10, 10);

    for (int i = 0; i < 100; i++) {
        model.step();
    }

    model.prinfo();
}