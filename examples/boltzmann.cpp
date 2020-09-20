/*-
 * TODO FILEHEADER
 */

#include "boltzmann.hpp"

#include <iostream>
#include <kami/kami.hpp>
#include <kami/multigrid2d.hpp>
#include <kami/random.hpp>
#include <map>

std::random_device *MoneyAgent::rd = nullptr;
std::mt19937 *MoneyAgent::rng = nullptr;
kami::MultiGrid2D *MoneyAgent::world = nullptr;
BoltzmannWealthModel *MoneyAgent::model = nullptr;

MoneyAgent::MoneyAgent() {
    rd = new std::random_device();
    rng = new std::mt19937{(*rd)()};

    stepCounter = 0;
    agentWealth = 1;
}

MoneyAgent::~MoneyAgent() {
    delete rng;
    delete rd;
};

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
    auto moveList = world->getNeighborhood(agentID, kami::NeighborhoodType::Moore, false);

    std::uniform_int_distribution<unsigned long> dist(0, moveList.size() - 1);
    auto newLocation = moveList[dist(*rng)];

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
    kami::MultiGrid2DCoord location = world->getLocationByAgent(agentID);
    std::vector<kami::AgentID> *cellMates = world->getCellContents(location);

    if (cellMates->size() > 1) {
        std::uniform_int_distribution<unsigned long> dist(0, cellMates->size() - 1);
        kami::AgentID otherAgentID = cellMates->at(dist(*rng));
        auto otherAgent = model->getAgentByID(otherAgentID);

        otherAgent->agentWealth += 1;
        agentWealth -= 1;
    }
}

void MoneyAgent::prinfo(void) const {
    kami::AgentID agentID = getAgentID();
    kami::MultiGrid2DCoord location = world->getLocationByAgent(agentID);

    std::cout << "  agent: " << agentID << " step: " << stepCounter << " wealth: " << agentWealth << " location: " << location << std::endl;
}

BoltzmannWealthModel::BoltzmannWealthModel(unsigned int numberAgents, unsigned int width, unsigned int height) {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::minstd_rand rng(static_cast<unsigned int>(seed));
    std::uniform_int_distribution<unsigned long> distWidth(0, width - 1);
    std::uniform_int_distribution<unsigned long> distHeight(0, height - 1);
    world = new kami::MultiGrid2D(width, height, true, true);
    sched = new kami::RandomScheduler(this);

    stepCount = 0;
    MoneyAgent::setWorld(world);
    MoneyAgent::setModel(this);

    for (unsigned int i = 0; i < numberAgents; i++) {
        MoneyAgent *newAgent = new MoneyAgent();
        agentList.insert(std::pair<kami::AgentID, MoneyAgent *>(newAgent->getAgentID(), newAgent));
        sched->addAgent(newAgent->getAgentID());
        world->addAgent(newAgent->getAgentID(), static_cast<int>(distWidth(rng)), static_cast<int>(distHeight(rng)));
    }
}

BoltzmannWealthModel::~BoltzmannWealthModel() {
    for (auto agent = agentList.begin(); agent != agentList.end(); ++agent) {
        world->deleteAgent(agent->first);
        sched->deleteAgent(agent->first);
        agentList.erase(agent);
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
    BoltzmannWealthModel model(10000, 100, 100);

    for (int i = 0; i < 100; i++) {
        model.step();
    }

    // model.prinfo();
}
