/*-
 * Copyright (c) 2020 The Johns Hopkins University Applied Physics
 * Laboratory LLC
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <string>

#include <kami/agent.h>
#include <kami/config.h>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <CLI/App.hpp>
#include <CLI/Config.hpp>
#include <CLI/Formatter.hpp>

using namespace kami;
using namespace std;

int main(int argc, char **argv) {
    string ident = "unit-kami-agentid";
    CLI::App app{ident};
    auto console = spdlog::stdout_color_st(ident);
    string logLevelOption = "info";

    app.add_option("-l", logLevelOption, "Set the logging level")->check(CLI::IsMember(SPDLOG_LEVEL_NAMES));
    CLI11_PARSE(app, argc, argv);

    console->set_level(spdlog::level::from_str(logLevelOption));
    console->info("Compiled with Kami/{}, log level {}", kami::version.to_string(), logLevelOption);

    AgentID testAgentID;
    console->debug("Successfully created AgentID with ID {}", testAgentID.to_string());
}
