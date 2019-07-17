#pragma once

#include <SPIFFS.h>


/**
 * Run function for each file in directory
 * @param dirname
 * @param handler
 */
void walk_dir(String dirname, void (*handler)(File)) {
    File dir = SPIFFS.open(dirname);
    File file;

    while (file = dir.openNextFile()) {
        handler(file);
        file.close();
    }

    dir.close();
}