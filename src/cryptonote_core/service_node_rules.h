#pragma once

namespace service_nodes {

inline uint64_t get_staking_requirement_lock_blocks(cryptonote::network_type nettype)
{
switch(nettype) {
    case cryptonote::TESTNET: return 1440;
    case cryptonote::FAKECHAIN: return 30;
    default: return 20160;
}
}

inline uint64_t get_min_node_contribution(size_t hf_version, uint64_t staking_requirement, uint64_t total_reserved)
{
  return hf_version > 9 ? std::min(staking_requirement - total_reserved, staking_requirement / MAX_NUMBER_OF_CONTRIBUTORS_V2) : std::min(staking_requirement - total_reserved, staking_requirement / MAX_NUMBER_OF_CONTRIBUTORS);
}

uint64_t get_staking_requirement(cryptonote::network_type nettype, uint64_t height);

uint64_t portions_to_amount(uint64_t portions, uint64_t staking_requirement);

/// Check if portions are sufficiently large (except for the last) and add up to the required amount
bool check_service_node_portions(const std::vector<uint64_t>& portions, const uint64_t min_portions = MIN_PORTIONS);
// Returns lowest x such that (staking_requirement * x/STAKING_PORTIONS) >= amount
uint64_t get_portions_to_make_amount(uint64_t staking_requirement, uint64_t amount);

bool get_portions_from_percent_str(std::string cut_str, uint64_t& portions);
}
