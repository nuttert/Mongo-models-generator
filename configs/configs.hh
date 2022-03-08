#pragma once
#include "Configs/configs-list.hpp"
#include "configs_manager.hh"
#include <utils/singleton.hh>

inline configs::ConfigManager& config_manager() {
    using Configs = utils::Single<configs::ConfigManager>;
    static Configs tp;
    return *Configs::instance();
}
