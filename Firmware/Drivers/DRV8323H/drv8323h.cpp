
#include "drv8323h.hpp"
#include "utils.hpp"
#include "cmsis_os.h"
#include "board.h"

bool Drv8323h::init() {
    if (state_ == kStateReady) {
        return true;
    }

    state_ = kStateStartupChecks;

    if (!nfault_gpio_.read()) {
        return false;
    }

    // There could have been an nFAULT edge meanwhile. In this case we shouldn't
    // consider the driver ready.
    CRITICAL_SECTION() {
        if (state_ == kStateStartupChecks) {
            state_ = kStateReady;
        }
    }

    return state_ == kStateReady;
}

void Drv8323h::do_checks() {
    if (state_ != kStateUninitialized && !nfault_gpio_.read()) {
        state_ = kStateUninitialized;
    }
}

bool Drv8323h::is_ready() {
    return state_ == kStateReady;
}

