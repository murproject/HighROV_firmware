#include "Thrusters.h"
#include "PWMController.h"
#include "Config.h"

String Thrusters::status = "";

void Thrusters::init() {
	using namespace config::thrusters;
	SerialUSB.println("Thrusters init");
	PWMController::set_thruster(horizontal_front_left, 0);
	PWMController::set_thruster(horizontal_front_right, 0);
	PWMController::set_thruster(horizontal_back_left, 0);
	PWMController::set_thruster(horizontal_back_right, 0);
	PWMController::set_thruster(vertical_front, 0);
	PWMController::set_thruster(vertical_back, 0);
	PWMController::set_thruster(custom_0, 0);
	PWMController::set_thruster(custom_1, 0);
}

void Thrusters::update_thrusters(rov::RovControl &ctrl, rov::RovTelemetry & tel) {
	using namespace config::thrusters;
	auto &data = inst();

	{
		const int16_t y = ctrl.axisY;
		const int16_t x = ctrl.axisX;
		const int16_t w = ctrl.axisW;
		const int16_t z = ctrl.axisZ;

		PWMController::set_thruster(horizontal_front_left,  constrain(data.directions[0] * (y + x + w), -100, 100));
		PWMController::set_thruster(horizontal_front_right, constrain(data.directions[1] * (y - x - w), -100, 100));
		PWMController::set_thruster(horizontal_back_left,   constrain(data.directions[2] * (y - x + w), -100, 100));
		PWMController::set_thruster(horizontal_back_right,  constrain(data.directions[3] * (y + x - w), -100, 100));

		PWMController::set_thruster(vertical_front, constrain(data.directions[4] * z, -100, 100));
		PWMController::set_thruster(vertical_back,  constrain(data.directions[5] * z, -100, 100));

		status = ("Axis X:	" + (String) x + "	Axis Y:	" + (String) y + "	Axis W:	" + (String) w + "	Axis Z:	" + z + "\n"\
							"Thruster HorFrontLeft:	" + (String) (data.directions[0] * (y + x + w)) + "	Thruster HorFrontRight	" + (String) (data.directions[1] * (y - x - w)) +\
					 "\n" + "Thruster HorBackLeft:	" + (String) (data.directions[2] * (y - x + w)) + "	Thruster HorBackRight	" + (String) (data.directions[3] * (y + x - w)) +\
					 "\n" + "Thruster VerFront :	" + (String) (data.directions[4] * z) +           "	Thruster VerBack	" + (String) (data.directions[5] * z));
	}
}

Thrusters & Thrusters::inst() {
	static Thrusters th;
	return th;
}
