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

void wifi::scan(const uint16_t max_wifi_records)
{
    uint16_t wifi_records_count = max_wifi_records; 
    std::unique_ptr<wifi_ap_record_t[]> wifi_records(new wifi_ap_record_t[max_wifi_records]);

    uint16_t ap_count = 0;
    ESP_ERROR_CHECK(esp_wifi_scan_start(NULL, true));
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&wifi_records_count, wifi_records.get()));
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));

    for(int i = 0; (i < wifi_records_count) && (i < ap_count); ++i)
    {
        auto ptr = wifi_ap_record_ptr(new wifi_ap_record_t(wifi_records[i]));
        m_scan_data.insert({(*(uint32_t*)&ptr->bssid), ptr});
    }
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
        ESP_LOGI(TAG, "%s\n", it->second->ssid);
    }
}
    
}