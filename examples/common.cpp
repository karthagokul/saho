/*****************************************************************************
 * %FILENAME%
 *
 * Created: %DATE% %YEAR% by %USER%
 *
 * Copyright %YEAR% %USER%. All rights reserved.
 *
 * This file may be distributed under the terms of GNU Public License version
 * 3 (GPL v3) as defined by the Free Software Foundation (FSF). A copy of the
 * license should have been included with this file, or the project in which
 * this file belongs to. You may also find the details of GPL v3 at:
 * http://www.gnu.org/licenses/gpl-3.0.txt
 *
 * If you have any questions regarding the use of this file, feel free to
 * contact the author of this file, or the owner of the project in which
 * this file belongs to.
 *****************************************************************************/

#include <iostream>
#include "logger.h"

structlog LoggerConfig = {};
using namespace std;

int main()
{
    /*
     *The logger is a place holder, I do not like the implemntation , For first version its okay
     */
    std::shared_ptr<LogInterface> l=std::make_shared<BasicLogger>();
    LoggerConfig.headers = true;
    LoggerConfig.level = ALL_LOG_LEVEL;
    LoggerConfig.logInterface=l;

    //LOG_FUNCTION_NAME;
    Logger(DEBUG) << "Hello Debug!";
    Logger(WARN) << "Hello Warning!";
    Logger(INFO) << "Hello Info!";
    Logger(ERROR) << "Hello Error!";

    return 0;
}

