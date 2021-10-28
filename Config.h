#pragma once
#include <stdint.h>
#include "variant.h"

namespace config {
    namespace wifi {
        constexpr char ssid[] = "HighROV";
        constexpr char pass[] = "robocenter";
        constexpr char pass_for_update[] = "1";
    }

    /* pinout */
    namespace pwm {
        /* thrusters */
        constexpr int th_horizontal_front_left_pin  = 2;
        constexpr int th_horizontal_front_right_pin = 3;
        constexpr int th_horizontal_back_left_pin   = 4;
        constexpr int th_horizontal_back_right_pin  = 5;
        constexpr int th_vertical_front_pin         = 6;
        constexpr int th_vertical_back_pin          = 7;
        // constexpr int th_custom_1 = 8;
        // constexpr int th_custom_2 = 9;

        /* manipulator PCA9536 channels */
        constexpr int manip_left_ch     = 0;
        constexpr int manip_right_ch    = 1;

        constexpr int manip_grab_ch     = 2;
        constexpr int manip_relese_ch   = 3;

        /* cam servos pins */
        constexpr int servo_front_pin   = A4;
        constexpr int servo_back_pin    = A5;

        /* video multiplexer */
        constexpr int cam_select_pin    = 10;
    }

    namespace networking {
        constexpr uint8_t selfip[4] = {192, 168, 1, 5};
        constexpr uint16_t self_port = 3020;
        constexpr uint8_t remoteip[4] = {192, 168, 1, 4};
        constexpr uint16_t remote_port = 3010;
    }

    /* indices of thursters */
    namespace thrusters {
        enum thrusters {
            horizontal_front_left = 0,
            horizontal_front_right,
            horizontal_back_left,
            horizontal_back_right,
            vertical_front,
            vertical_back,
        };
    }

    /* indices of servos */
    namespace servos {
        enum servos {
            front = 0,
            back = 1,
        };
    }
}
