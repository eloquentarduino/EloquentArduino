#pragma once


#define retry(condition, times) \
    ([]() {\
        for (uint16_t i = 0; i < times; i++)\
            if (condition)\
                return true;\
        return false;\
    })