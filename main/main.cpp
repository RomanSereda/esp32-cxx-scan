#include "nvs_cxx.hpp"
#include "wlx_cxx.hpp"

wlx_cxx::wifi wifi;

extern "C" void app_main(void)
{
    nvs_cxx::init();

    wifi.init();
    wifi.create_sta();
    wifi.scan();
    wifi.print();
    wifi.destroy();
}
