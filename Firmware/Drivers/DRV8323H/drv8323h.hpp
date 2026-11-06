#ifndef __DRV8323H_HPP
#define __DRV8323H_HPP

#include "stdbool.h"
#include "stdint.h"

#include <Drivers/STM32/stm32_gpio.hpp>


class Drv8323h {
public:
    Drv8323h(Stm32Gpio nfault_gpio)
            : nfault_gpio_(nfault_gpio) {}

    /**
     * @brief Initializes the gate driver
     *
     * Returns true on success or false otherwise (e.g. if the gate driver is
     * not connected).
     */
    bool init();

    /**
     * @brief Monitors the nFAULT pin.
     *
     * This must be run at an interval of <8ms from the moment the init()
     * functions starts to run, otherwise it's possible that a temporary power
     * loss is missed, leading to unwanted register values.
     * In case of power loss the nFAULT pin can be low for as little as 8ms.
     */
    void do_checks();

    /**
     * @brief Returns true if and only if the DRV8301 chip is in an initialized
     * state.
     */
    bool is_ready();

private:
    // Configuration
    Stm32Gpio nfault_gpio_;

    enum {
        kStateUninitialized,
        kStateStartupChecks,
        kStateReady,
    } state_ = kStateUninitialized;
};


#endif // __DRV8323H_HPP
