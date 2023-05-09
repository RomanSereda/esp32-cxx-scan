#include "nvs_cxx.hpp"
#include "wlx_cxx.hpp"

static wlx_cxx::wifi wifi;

extern "C" void app_main(void)
{
    nvs_cxx::init();

    wifi.init();
    wifi.create_sta();



}
