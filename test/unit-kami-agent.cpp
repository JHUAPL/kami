/*-
 * TODO FILEHEADER
 */

#include <spdlog/spdlog.h>

#include <CLI/App.hpp>
#include <CLI/Config.hpp>
#include <CLI/Formatter.hpp>
#include <kami/agent.hpp>
#include <kami/config.hpp>

#include "spdlog/sinks/stdout_color_sinks.h"

using namespace kami;
using namespace std;

int main(int argc, char **argv) {
    string ident = "unit-kami-agent";
    CLI::App app{ident};
    auto console = spdlog::stdout_color_st(ident);
    bool debugFlag;

    app.add_option("-d,--debug", debugFlag, "A help string");
    CLI11_PARSE(app, argc, argv);

    if (debugFlag == true)
        console->set_level(spdlog::level::debug);

    console->debug("Compiled with Kami/{}.{}.{}", KAMI_VERSION_MAJOR, KAMI_VERSION_MINOR, KAMI_VERSION_PATCH);

    Agent testAgent;
    console->debug("Successfully created Agent with ID {}", testAgent.getAgentID().toString());
}
