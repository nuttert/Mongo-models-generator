#pragma once
#include <functional>
#include <unordered_map>
#include "config_interface.hh"
#include "Configs/configs-list.hpp"

namespace configs {

class ConfigManager {
    using ConfigInterfacePtr = std::shared_ptr<ConfigInterface>;
    using Container          = std::unordered_map<std::string, ConfigInterfacePtr>;
    using ConfigFactory      = std::function<ConfigInterfacePtr()>;

public:
    ConfigManager() {
        FillConfigManager(*this);
        LoadConfigs();
    }

    ConfigManager& PushConfig(const std::string& name, const ConfigFactory& factory);
    template <typename Config>
    ConfigManager& PushConfig(const std::string& name);
    template <typename Config>
    ConfigManager& PushConfig();

    template <typename Config>
    const std::shared_ptr<Config> GetConfig(const std::string& name) const;
    template <typename Config>
    const std::shared_ptr<Config> GetConfig() const;

    void LoadConfigs() {
        for (const auto& [name, config_] : configs_) {
            config_->LoadFile();
        }
    }

private:
    Container configs_{};
};

}  // namespace configs

#include "configs_manager.tpp"
