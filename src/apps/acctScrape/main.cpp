/*-------------------------------------------------------------------------
 * This source code is confidential proprietary information which is
 * copyright (c) 2018, 2019 TrueBlocks, LLC (http://trueblocks.io)
 * All Rights Reserved
 *------------------------------------------------------------------------*/
#include "etherlib.h"
#include "options.h"

//-----------------------------------------------------------------------
int main(int argc, const char* argv[]) {
    nodeNotRequired();
    namesNotRequired();
    acctlib_init(defaultQuitHandler);

    COptions options;
    if (!options.prepareArguments(argc, argv))
        return 0;

    for (auto command : options.commandLines) {
        if (!options.parseArguments(command))
            continue;

        // Clean the staging folder since we want to start with clean scrapes for both
        // never scraped or unfinished (partial) scrapes
        cleanMonitorStage();

        if (options.visitTypes & VIS_FINAL)
            forEveryFileInFolder(indexFolder_finalized, visitFinalIndexFiles, &options);

        if (options.visitTypes & VIS_STAGING)
            forEveryFileInFolder(indexFolder_staging, visitStagingIndexFiles, &options);

        if (options.visitTypes & VIS_UNRIPE)
            forEveryFileInFolder(indexFolder_unripe, visitUnripeIndexFiles, &options);

        for (auto monitor : options.monitors) {
            monitor.moveToProduction();
            LOG4(monitor.address, " freshened to ", monitor.nextBlockAsPerMonitor());
        }
    }

    if (options.stats.nFiles != options.stats.nSkipped) {
        ostringstream header;
        header << options.stats.Format(substitute(STR_DISPLAY_ACCTSCRAPESTATS, "{", "{p:"));

        ostringstream data;
        data << options.stats.Format(STR_DISPLAY_ACCTSCRAPESTATS);

        LOG_INFO(header.str());
        LOG_INFO(data.str());

        header << endl;
        data << endl;

        string_q statsFile = configPath("performance_scraper.txt");
        if (!fileExists(statsFile))
            stringToAsciiFile(statsFile, header.str());
        appendToAsciiFile(statsFile, data.str());
    }

    acctlib_cleanup();
    return 0;
}
