#include <cstdlib>
#include <thread>
#include "esp_log.h"
#include "gpio_cxx.hpp"

extern "C" void app_main(void)
{
    try {
        /* This line may throw an exception if the pin number is invalid.
         * Alternatively to 4, choose another output-capable pin. */
        idf::GPIO_Output gpio(idf::GPIONum(4));

        while (true) {
            printf("LED ON\n");
            gpio.set_high();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            printf("LED OFF\n");
            gpio.set_low();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } catch (idf::GPIOException &e) {
        printf("GPIO exception occurred: %s\n", esp_err_to_name(e.error));
        printf("stopping.\n");
    }
}
