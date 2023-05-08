#include <cstdlib>
#include <thread>
#include "esp_log.h"
#include "nvs_cxx.hpp"

extern "C" void app_main(void)
{
    cxx::init();
}
