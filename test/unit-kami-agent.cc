/*-
 * TODO FILEHEADER
 */

#include <kami/agent.h>
#include <kami/config.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <CLI/App.hpp>
#include <CLI/Config.hpp>
#include <CLI/Formatter.hpp>
#include <string>

using namespace kami;
using namespace std;

class TestAgent : public Agent {
    void step(){};
};

int main(int argc, char **argv) {
    string ident = "unit-kami-agent";
    CLI::App app{ident};
    auto console = spdlog::stdout_color_st(ident);
    string logLevelOption = "info";

    app.add_option("-l", logLevelOption, "Set the logging level")
        ->check(CLI::IsMember(SPDLOG_LEVEL_NAMES));
    CLI11_PARSE(app, argc, argv);

    console->set_level(spdlog::level::from_str(logLevelOption));
    console->info("Compiled with Kami/{}, log level {}", KAMI_VERSION_STRING,
                  logLevelOption);

    TestAgent test_agent;
    console->debug("Successfully created Agent with ID {}",
                   test_agent.get_agent_id().to_string());
}
