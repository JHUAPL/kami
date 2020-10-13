/*-
 * TODO FILEHEADER
 */

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <CLI/App.hpp>
#include <CLI/Config.hpp>
#include <CLI/Formatter.hpp>
#include <kami/agent.hpp>
#include <kami/config.hpp>
#include <string>

using namespace kami;
using namespace std;

int main(int argc, char **argv) {
    string ident = "unit-kami-agent";
    CLI::App app{ident};
    auto console = spdlog::stdout_color_st(ident);
    string logLevelOption = "info";

    app.add_option("-l", logLevelOption, "Set the logging level")->check(CLI::IsMember(SPDLOG_LEVEL_NAMES));
    CLI11_PARSE(app, argc, argv);

    console->set_level(spdlog::level::from_str(logLevelOption));
    console->info("Compiled with Kami/{}, log level {}", KAMI_VERSION_STRING, logLevelOption);

    Agent testAgent;
    console->debug("Successfully created Agent with ID {}", testAgent.getAgentID().toString());
}
