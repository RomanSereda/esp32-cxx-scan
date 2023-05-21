#include "wlx_cxx.hpp"
#include <cstring>
#include "esp_log.h"

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
    m_esp_netif = esp_netif_create_default_wifi_sta();
    assert(m_esp_netif);

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
}

void wifi::scan(const uint16_t max_records)
{
    uint16_t records_count = max_records; 
    std::unique_ptr<wifi_ap_record_t[]> records(new wifi_ap_record_t[max_records]);

    uint16_t ap_count = 0;
    ESP_ERROR_CHECK(esp_wifi_scan_start(NULL, true));
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&records_count, records.get()));
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));

    time_t timestamp;
    time(&timestamp);
    m_tses.insert(timestamp);

    auto thin_out_scan_data = [&]()->bool {
        if(m_tses.empty()) return true;
        if(m_scan_data.empty()) {
            m_tses.clear();
            return true;
        }

        auto min_ts = *m_tses.begin();

        bool is_anyone_erased = false;
        for (auto it = m_scan_data.begin(); it != m_scan_data.end(); it++){
            if(it->second->timestamp == min_ts){
                it = m_scan_data.erase(it);
                is_anyone_erased = true;
            }
        }

        m_tses.erase(min_ts);
        return is_anyone_erased;
    };

    if(m_scan_data.size() > max_records * 1.5)
        while(!thin_out_scan_data()){};

    for(int i = 0; (i < records_count) && (i < ap_count); ++i){
        auto& record = records[i];
        uint32_t& id = *(uint32_t*)&record.ssid;

        auto it = m_scan_data.find(id);
        if(it == m_scan_data.end())
           m_scan_data.insert({id, ap_info_t::ptr(new ap_info_t({record, timestamp}))});
        else
        {
            it->second->timestamp = timestamp;
            it->second->ap.rssi = record.rssi;
        }
    }
}

void wifi::destroy()
{
    ESP_ERROR_CHECK(esp_wifi_stop());
    esp_netif_destroy(m_esp_netif);
}

void wifi::print()
{
    for(auto it = m_scan_data.begin(); it != m_scan_data.end(); ++it)
    {
        uint8_t* bssid = &it->second->ap.bssid[0];
        printf("%02x:%02x:%02x:%02x:%02x:%02x %idBm %s\n", 
            bssid[0],bssid[1],bssid[2],bssid[3],bssid[4],bssid[5],
            it->second->ap.rssi,
            it->second->ap.ssid);
    }
}
    
}