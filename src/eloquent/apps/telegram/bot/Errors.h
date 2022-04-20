//
// Created by Simone on 20/04/2022.
//

#pragma once

namespace Eloquent {
    namespace Apps {
        namespace Telegram {
            enum class TelegramBotError {
                OK,
                INIT_ERROR,
                CONNECTION_ERROR,
                REQUEST_ERROR,
                EMPTY_PAYLOAD_ERROR
            };
        }
    }
}