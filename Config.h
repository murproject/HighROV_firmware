#pragma once
#include <stdint.h>

namespace config {
    namespace wifi {
        constexpr char ssid[] = "HighROV";
        constexpr char pass[] = "robocenter";
        constexpr char pass_for_update[] = "1";
    }
    namespace pwm {
        constexpr int left_front_horizontal_ch = 0;
        constexpr int right_front_horizontal_ch = 1;
        constexpr int left_back_horizontal_ch = 2;
        constexpr int right_back_horizontal_ch = 3;
        constexpr int front_vertical_ch = 4;
        constexpr int back_vertical_ch = 5;
        constexpr int servo_front_ch = 14;
        constexpr int servo_back_ch = 15;
        constexpr int manip_left_ch = 10;
        constexpr int manip_right_ch = 11;
        constexpr int manip_grab_ch = 12;
        constexpr int manip_relese_ch = 13;
        constexpr int pwm_freq = 50;
    }

    namespace networking {
        constexpr uint8_t selfip[4] = {192, 168, 1, 5};
        constexpr uint16_t self_port = 3020;
        constexpr uint8_t remoteip[4] = {192, 168, 1, 4};
        constexpr uint16_t remote_port = 3010;
    }
}
