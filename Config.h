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

        /* additional custom thrusters */
        constexpr int th_custom_0_pin   = 8;
        constexpr int th_custom_1_pin   = 9;

        /* cam servos pins */
        constexpr int servo_front_pin   = A4;
        constexpr int servo_back_pin    = A5;

        /* video multiplexer */
        constexpr int cam_select_pin    = 10;

        /* custom PWM pins */
        constexpr int pwm_custom_a2_pin = A2;
        constexpr int pwm_custom_a3_pin = A3;

        /* manipulator PCA9536 channels */
        constexpr int manip_left_ch     = 0;
        constexpr int manip_right_ch    = 1;

        constexpr int manip_grab_ch     = 2;
        constexpr int manip_relese_ch   = 3;
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
            custom_0,
            custom_1,
        };
    }

    /* indices of servos */
    namespace servos {
        enum servos {
            front = 0,
            back,
            pwm_a2,
            pwm_a3,
        };
    }

    namespace networking {
        constexpr uint8_t selfip[4] = {192, 168, 1, 5};
        constexpr uint16_t self_port = 3020;
        constexpr uint8_t remoteip[4] = {192, 168, 1, 4};
        constexpr uint16_t remote_port = 3010;
        constexpr uint8_t cs_pin = 43; // W5500 CS on PA13 pin
    }

    namespace analog {
        enum ammeter_types {}; // TODO: should support different ammeter types!

        constexpr int ammeter_pin = A0;
        constexpr int voltmeter_pin = A1;

        constexpr double voltage_multiplier = 0.016064;
    } // namespace analog


}
