#pragma once

#include <unordered_map>
#include <cstdint>
#include <cstddef>

struct RouteEntry {
    uint16_t destination_id;
    uint16_t next_hop_id;
    uint8_t hop_count;
    int8_t link_quality_rssi;
    uint32_t last_updated_ms;
};

class RoutingEngine {
private:
    uint16_t local_node_id;
    std::unordered_map<uint16_t, RouteEntry> routing_table;

public:
    explicit RoutingEngine(uint16_t node_id);

    void process_beacon(uint16_t sender_id, uint16_t dest_id, uint8_t hops, int8_t rssi, uint32_t current_time);
    bool get_next_hop(uint16_t destination_id, uint16_t& next_hop_out);
    void prune_stale_routes(uint32_t current_time, uint32_t timeout_ms = 10000);
    void clear_table();
    
    const std::unordered_map<uint16_t, RouteEntry>& get_table() const;
};

#ifndef ROUTING_ENGINE_H
#define ROUTING_ENGINE_H

#include <cstdint>
#include <vector>

// Timer thresholds in milliseconds
constexpr uint32_t HEARTBEAT_INTERVAL_MS = 2000; // Broadcast heartbeat every 2000ms
constexpr uint32_t TIMEOUT_THRESHOLD_MS  = 6000; // Purge node after 6000ms of inactivity

struct NeighborNode {
    uint8_t  node_id;
    uint32_t last_seen_ms;
    bool     is_active;
};

#endif
