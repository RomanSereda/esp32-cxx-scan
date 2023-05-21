#ifndef ESP_WLX_CXX_HPP_
#define ESP_WLX_CXX_HPP_

#include <map>
#include <set>
#include <memory>
#include "time.h"
#include "esp_wifi.h"

namespace wlx_cxx {

struct ap_info_t
{
    using ptr = std::shared_ptr<ap_info_t>;
    wifi_ap_record_t ap;
    time_t timestamp;
};

class wifi
{
public:
    void init();
    void create_sta();
    void scan(const uint16_t max_records = 32);
    void destroy();

    void print();

private:
    esp_netif_t *m_esp_netif = nullptr;
    std::map<uint32_t, ap_info_t::ptr> m_scan_data;
    std::set<time_t> m_tses;
};  
}

#endif //ESP_WLX_CXX_HPP_