#include "wlx_cxx.hpp"
#include <cstring>
#include "esp_log.h"

static const char *TAG = "wenvmitter";

namespace wlx_cxx {
void wifi::init()
{
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
}

void wifi::create_sta()
{
    esp_netif = esp_netif_create_default_wifi_sta();
    assert(esp_netif);

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
}

void wifi::scan(const uint16_t size)
{
    uint16_t size_buffer = size; 
    wifi_ap_record_t* ap_info_buffer = new wifi_ap_record_t[size];

    uint16_t ap_count = 0;
    ESP_ERROR_CHECK(esp_wifi_scan_start(NULL, true));
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&size_buffer, ap_info_buffer));
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));

    for(int i = 0; (i < size_buffer) && (i < ap_count); ++i)
    {
        auto ap_info = &ap_info_buffer[i];
        std::shared_ptr<wifi_ap_record_t> ptr = std::make_shared<wifi_ap_record_t>(*ap_info);
        uint32_t id = 0;
        memcpy(&id, (void*)&ap_info->bssid, sizeof(uint32_t));
        m_scan_data.insert(std::pair<uint32_t, std::shared_ptr<wifi_ap_record_t>>(id, ptr));
    }

    delete[] ap_info_buffer;
}

void wifi::destroy()
{
    ESP_ERROR_CHECK(esp_wifi_stop());
    esp_netif_destroy(esp_netif);
}

void wifi::print()
{
    for(auto it = m_scan_data.begin(); it != m_scan_data.end(); ++it)
    {
        esp_rom_printf("%s\n", it->second->ssid);
    }
}
    
}