#pragma once

namespace WiFiUpdater
{
    void init();
    void check_updates();

    void set_before_callback(void (*fn)());
}

