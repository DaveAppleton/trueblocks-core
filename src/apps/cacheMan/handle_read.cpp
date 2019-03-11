/*-------------------------------------------------------------------------
 * This source code is confidential proprietary information which is
 * Copyright (c) 2017 by Great Hill Corporation.
 * All Rights Reserved
 *------------------------------------------------------------------------*/
#include "options.h"

//-------------------------------------------------------------------------
bool COptions::handleRead(const string_q& msg, size_t filesToUse, CAcctCacheItemArray& dataArray) const {

    dataArray.reserve(2000000); // just a guess, but makes the read very much faster
    for (uint32_t fn = 0 ; fn < filesToUse ; fn++) {
        cerr << "\t" << msg << " cache: " << cTeal << monitors[fn].name << cOff << "...";
        CArchive txCache(READING_ARCHIVE);
        if (!txCache.Lock(monitors[fn].name, modeReadOnly, LOCK_NOWAIT))
            return usage("Could not open file: " + monitors[fn].name + ". Quitting.");
        uint64_t nRead = 0;
        while (!txCache.Eof() && !shouldQuit()) {
            CAcctCacheItem item;
            txCache >> item.blockNum >> item.transIndex;
            if (item.blockNum > 0) {
                dataArray.push_back(item);
                nRead++;
                cerr << (!(nRead % 10000) ? "." : "");
            }
        }
        txCache.Release();
        cerr << cYellow << nRead << cOff << " existing records read.\n";
    }
    return !shouldQuit();
}

