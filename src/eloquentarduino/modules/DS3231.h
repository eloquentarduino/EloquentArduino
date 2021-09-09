#pragma once

#include <RTClibExtended.h>


namespace Eloquent {

    /**
     * Utility wrapper around RTC_DS3231
     */
    class DS3231 : public RTC_DS3231 {
    public:
        /**
         *
         */
        void begin() {
            RTC_DS3231::begin();
            read();
        }

        /**
         *
         */
        void read() {
            current = now();

            if (current.year() <= 2000 || current.year() > 2050) {
                RTC_DS3231::adjust(DateTime(__DATE__, __TIME__));
                current = now();
            }
        }

        /**
         *
         * @param dt
         */
        void adjust(const DateTime &dt) {
            RTC_DS3231::adjust(dt);
            read();
        }

        /**
         *
         * @return
         */
        String timestamp() {
            return String(current.unixtime());
        }

        /**
         *
         * @return
         */
        String date() {
            return pad(current.year()) + '-' + pad(current.month()) + '-' + pad(current.day());
        }

        /**
         *
         * @return
         */
        String time() {
            return pad(current.hour()) + ':' + pad(current.minute()) + ':' + pad(current.second());
        }

        /**
         *
         * @return
         */
        String datetime() {
            return date() + " " + time();
        }

    private:
        DateTime current;

        String pad(int n) {
            return String(n < 10 ? "0" : "") + String(n);
        }
    };


    DS3231 ds3231;
}