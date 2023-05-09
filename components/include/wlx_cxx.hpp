#ifndef ESP_WLX_CXX_HPP_
#define ESP_WLX_CXX_HPP_

#include "esp_wifi.h"

namespace wlx_cxx {
class wifi
{
public:
    void init();
    void create_sta();

    void destroy();

private:
    esp_netif_t *esp_netif = nullptr;

};  
}

#endif //ESP_WLX_CXX_HPP_