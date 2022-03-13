#pragma once
#include <fmt/format.h>

#define logInfo(...) std::cout << fmt::format(__VA_ARGS__) << std::endl;
#define logError(...) std::cout << fmt::format(__VA_ARGS__) << std::endl;
#define logFatal(...) std::cout << fmt::format(__VA_ARGS__) << std::endl;
#define logWarn(...) std::cout << fmt::format(__VA_ARGS__) << std::endl;
#define logDebug(...) std::cout << fmt::format(__VA_ARGS__) << std::endl;