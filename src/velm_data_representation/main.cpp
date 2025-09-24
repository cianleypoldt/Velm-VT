#include "spdlog/common.h"

#include <spdlog/spdlog.h>

#include <iostream>

int main() {
    spdlog::set_level(spdlog::level::debug);
    spdlog::debug("Looooolll");
}
