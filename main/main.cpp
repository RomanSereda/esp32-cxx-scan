#include "nvs_cxx.hpp"
#include "wlx_cxx.hpp"

extern "C" void app_main(void)
{
    nvs_cxx::init();

    wlx_cxx::wifi wifi;

    wifi.init();
    wifi.create_sta();

    wifi.scan();
    wifi.print();
}
