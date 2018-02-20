#ifndef ROV_ROVMAGICS_H
#define ROV_ROVMAGICS_H

#include <stdint.h>
#include <math.h>
#include <limits.h>
namespace rov {

#define VERTICAL_THRUSTER_SIZE 2
#define HORIZONTAL_THRUSTER_SIZE 4
#define SENSORS_SIZE 4
#define PAYLOAD_SIZE 2

struct RotaryCameraConfig {
	enum : uint8_t {
		CAM_FRONT_PIN = 40,
		CAM_BACK_PIN = 41
	};

	static constexpr int  CAM_ONE_DEFAULT_ANGLE = 90;	
	static constexpr int  CAM_ONE_MIN_ANGLE = 0;
	static constexpr int  CAM_ONE_MAX_ANGLE = 180;

	static constexpr int  CAM_TWO_DEFAULT_ANGLE = 90;
	static constexpr int  CAM_TWO_MIN_ANGLE = 0;
	static constexpr int  CAM_TWO_MAX_ANGLE = 180;
};


struct CurrentConfig {
    enum : uint8_t {
      VOLTMETER_PIN =  1,
      AMPERMETER_PIN =  0
    };
};

struct ManipulatorConfig {
    enum : uint8_t {
      AXISX_PIN1 =  33,
      AXISX_PIN2 =  31,
      AXISY_PIN1 =  29,
      AXISY_PIN2 =  27
    };
};

struct HorizontalThrusterConfig {
    enum : int {
      FRONT_LEFT_PIN =  2,
      FRONT_RIGHT_PIN =  3,
      BACK_LEFT_PIN =  4,
      BACK_RIGHT_PIN =  5
    };
};

struct VerticalThrusterConfig {
    enum : int {
      FRONT_PIN =  6,
      BACK_PIN =  7
    };
};

struct HorizontalThruster {
    enum : int {
      FRONT_LEFT =  0,
      FRONT_RIGHT =  1,
      BACK_LEFT =  2,
      BACK_RIGHT =  3
    };
};

struct VerticalThruster {
    enum : int {
      FRONT =  0,
      BACK =  1
    };
};

} // namespace rov
#endif
