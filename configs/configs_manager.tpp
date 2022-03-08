#pragma once
#include <fstream>
#include <sstream>
#include "configs_manager.hh"

namespace configs {

template <typename Config>
ConfigManager& ConfigManager::PushConfig(const std::string& name) {
    using namespace std::string_literals;

    static_assert(std::is_base_of<ConfigInterface, Config>::value, "Not appropriate type!");
    static_assert((std::is_default_constructible<Config>::value), "No default constructor!");

    bool configs_unique = configs_.count(name);
    if (configs_unique)
        throw std::runtime_error("Config already exists! " + name);

    try {
        configs_[name] = std::make_shared<Config>();
    } catch (std::exception& e) {
        throw std::runtime_error{"Can't construct config, "s + e.what()};
    }

    return *this;
}

template <typename Config>
ConfigManager& ConfigManager::PushConfig() {
    return PushConfig<Config>(Config::kName);
}

/*
@throw runtime_error - Cannot cast config
*/
template <typename Config>
const std::shared_ptr<Config> ConfigManager::GetConfig(const std::string& name) const {
    using ConfigPtr = std::shared_ptr<Config>;
    ConfigPtr config_{};

    const auto config_iterator = configs_.find(name);

    if (config_iterator != configs_.end()) {
        config_ = std::dynamic_pointer_cast<Config>(config_iterator->second);
        if (!config_)
            throw std::runtime_error("Cannot cast config interface to config! " + name);
    } else {
        throw std::runtime_error("Can't find config: " + name);
    }
    return config_;
}

template <typename Config>
const std::shared_ptr<Config> ConfigManager::GetConfig() const {
    return GetConfig<Config>(Config::kName);
}

}  // namespace configs
