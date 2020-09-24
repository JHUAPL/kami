/*-
 * TODO FILEHEADER
 */

#include "boltzmann1d.hpp"

#include <stdlib.h>

#include <iostream>
#include <kami/kami.hpp>
#include <kami/multigrid1d.hpp>
#include <map>

kami::MultiGrid1D *MoneyAgent::world = nullptr;
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

void MoneyAgent::setWorld(kami::MultiGrid1D *w) {
    world = w;
}

void MoneyAgent::setModel(class BoltzmannWealthModel *m) {
    model = m;
}

void MoneyAgent::moveAgent() {
    auto agentID = this->getAgentID();
    auto moveList = world->getNeighborhood(agentID, false);
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
    kami::GridCoord1D location = world->getLocationByAgent(agentID);
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
    kami::GridCoord1D location = world->getLocationByAgent(agentID);

    std::cout << "  agent: " << agentID << " step: " << stepCounter << " wealth: " << agentWealth << " location: " << location << std::endl;
}

BoltzmannWealthModel::BoltzmannWealthModel(unsigned int numberAgents, unsigned int lengthX) {
    world = new kami::MultiGrid1D(lengthX, true);
    sched = new kami::RandomScheduler(this);

    stepCount = 0;
    MoneyAgent::setWorld(world);
    MoneyAgent::setModel(this);

    for (unsigned int i = 0; i < numberAgents; i++) {
        MoneyAgent *newAgent = new MoneyAgent();

        agentList.insert(std::pair<kami::AgentID, MoneyAgent *>(newAgent->getAgentID(), newAgent));
        sched->addAgent(newAgent->getAgentID());
        world->addAgent(newAgent->getAgentID(),
                        kami::GridCoord1D(rand() % static_cast<int>(lengthX)));
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
    BoltzmannWealthModel model(16, 16);

    for (int i = 0; i < 100; i++) {
        model.step();
    }

    model.prinfo();
}
