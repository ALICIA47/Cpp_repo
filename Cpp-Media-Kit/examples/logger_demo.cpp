#include "cmedia/logger.h"

int main() {
    auto& logger = cmedia::Logger::instance();

    logger.setLogFile("app.log");

    logger.debug("debug message");
    logger.info("program started");
    logger.warn("this is a warning");
    logger.error("something went wrong");

    return 0;
}