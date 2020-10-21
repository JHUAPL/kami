/*-
 * TODO FILEHEADER
 */

#include "boltzmann2d.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <spdlog/stopwatch.h>
#include <stdlib.h>

#include <CLI/App.hpp>
#include <CLI/Config.hpp>
#include <CLI/Formatter.hpp>
#include <iostream>
#include <kami/agent.h>
#include <kami/config.h>
#include <kami/grid2d.h>
#include <kami/kami.h>
#include <kami/multigrid2d.h>
#include <map>

using namespace kami;
using namespace std;

MultiGrid2D *MoneyAgent::world = nullptr;
BoltzmannWealthModel *MoneyAgent::model = nullptr;
shared_ptr<spdlog::logger> console;

template <>
struct fmt::formatter<AgentID> : fmt::formatter<string> {
    auto format(AgentID agentID, format_context &ctx) {
        return format_to(ctx.out(), "{}", agentID.toString());
    }
};

template <>
struct fmt::formatter<GridCoord2D> : fmt::formatter<string> {
    auto format(GridCoord2D coord, format_context &ctx) {
        return format_to(ctx.out(), "{}", coord.toString());
    }
};

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

void MoneyAgent::setWorld(MultiGrid2D *w) {
    world = w;
}

void MoneyAgent::setModel(class BoltzmannWealthModel *m) {
    model = m;
}

void MoneyAgent::moveAgent() {
    auto agentID = this->getAgentID();
    auto moveList = world->getNeighborhood(agentID, GridNeighborhoodType::Moore, false);
    auto newLocation = moveList[static_cast<unsigned int>(rand()) % moveList.size()];

    console->trace("Moving Agent {} to location {}", agentID, newLocation);
    world->moveAgent(agentID, newLocation);
}

int MoneyAgent::getWealth() {
    return agentWealth;
}

void MoneyAgent::setWealth(int newWealth) {
    agentWealth = newWealth;
}

void MoneyAgent::giveMoney() {
    AgentID agentID = getAgentID();
    GridCoord2D location = world->getLocationByAgent(agentID);
    vector<AgentID> *cellMates = world->getCellContents(location);

    if (cellMates->size() > 1) {
        AgentID otherAgentID = cellMates->at(static_cast<unsigned int>(rand()) % cellMates->size());
        auto otherAgent = model->getAgentByID(otherAgentID);

        console->trace("Agent {} giving unit of wealth to agent {}", agentID, otherAgentID);
        otherAgent->agentWealth += 1;
        agentWealth -= 1;
    }
}

void MoneyAgent::prinfo(void) const {
    AgentID agentID = getAgentID();
    GridCoord2D location = world->getLocationByAgent(agentID);

    console->trace("Agent state for agent {}, step {}, wealth {}, location {}", agentID, stepCounter, agentWealth, location);
}

BoltzmannWealthModel::BoltzmannWealthModel(unsigned int numberAgents, unsigned int lengthX, unsigned int lengthY, unsigned int seed) {
    world = new MultiGrid2D(lengthX, lengthY, true, true);
    if(seed == 0) 
        sched = new RandomScheduler(this);
    else
        sched = new RandomScheduler(this, seed);

    stepCount = 0;
    MoneyAgent::setWorld(world);
    MoneyAgent::setModel(this);

    for (unsigned int i = 0; i < numberAgents; i++) {
        MoneyAgent *newAgent = new MoneyAgent();

        agentList.insert(pair<AgentID, MoneyAgent *>(newAgent->getAgentID(), newAgent));
        sched->addAgent(newAgent->getAgentID());
        world->addAgent(newAgent->getAgentID(),
                        GridCoord2D(rand() % static_cast<int>(lengthX),
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
    console->trace("Model state step {}", stepCount);
    for (auto agent = agentList.begin(); agent != agentList.end(); ++agent) {
        agent->second->prinfo();
    }
}

MoneyAgent *BoltzmannWealthModel::getAgentByID(AgentID agentID) const {
    MoneyAgent *agentPair = agentList.at(agentID);

    return agentPair;
}

int main(int argc, char **argv) {
    string ident = "boltzmann2d";
    CLI::App app{ident};
    string logLevelOption = "info";
    unsigned int xSize = 10, ySize = 10, agentCount = xSize * ySize, maxSteps = 100, seed = 0;

    app.add_option("-c", agentCount, "Set the number of agents")->check(CLI::PositiveNumber);
    app.add_option("-l", logLevelOption, "Set the logging level")->check(CLI::IsMember(SPDLOG_LEVEL_NAMES));
    app.add_option("-n", maxSteps, "Set the number of steps to run the model")->check(CLI::PositiveNumber);
    app.add_option("-s", seed, "Set the RNG seed")->check(CLI::NonNegativeNumber);
    app.add_option("-x", xSize, "Set the number of colums")->check(CLI::PositiveNumber);
    app.add_option("-y", ySize, "Set the number of rows")->check(CLI::PositiveNumber);
    CLI11_PARSE(app, argc, argv);

    console = spdlog::stdout_color_st(ident);
    console->set_level(spdlog::level::from_str(logLevelOption));
    console->info("Compiled with Kami/{}, log level {}", KAMI_VERSION_STRING, logLevelOption);
    console->info("Starting Boltzmann Wealth Model with {} agents on a {}x{}-unit grid for {} steps", agentCount, xSize, ySize, maxSteps);

    BoltzmannWealthModel model(agentCount, xSize, ySize, seed);

    spdlog::stopwatch sw;
    for (int i = 0; i < maxSteps; i++) {
        console->trace("Initiating model step {}", i);
        model.step();
    }
    console->info("Boltzman Wealth Model simulation complete, requiring {} ", sw);

    model.prinfo();
}
