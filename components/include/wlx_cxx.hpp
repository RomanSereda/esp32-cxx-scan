#ifndef ESP_WLX_CXX_HPP_
#define ESP_WLX_CXX_HPP_

#include "esp_wifi.h"
#include <map>
#include <memory>

namespace wlx_cxx {
class wifi
{
public:
    void init();
    void create_sta();
    void scan(const uint16_t size = 64);
    void destroy();

    void print();

private:
    esp_netif_t *esp_netif = nullptr;
    std::map<uint32_t, std::shared_ptr<wifi_ap_record_t>> m_scan_data;
};  
}

#endif //ESP_WLX_CXX_HPP_