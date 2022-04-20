//
// Created by Simone on 13/04/2022.
//

#pragma once


namespace eloquent {

    /**
     * Print a message forever
     * @tparam Printer
     * @tparam Message
     * @param printer
     * @param message
     * @param interval
     */
    template<class Printer, typename Message>
    void abort(Printer &printer, Message message, uint16_t interval = 1000) {
        while (true) {
            printer.print(message);
            printer.print('\n');
            delay(interval);
        }
    }
}