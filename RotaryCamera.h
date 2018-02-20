#pragma once
#include "PayloadTool.h"
#include "RovDataStore.h"

#include <Servo.h>



namespace rov {

	namespace prvt {
		struct RotCam {
			Servo cam;
			int angle = 0;
			int max_angle = 0;
			int min_angle = 0;
		};
	};

	class RotaryCamera : public PayloadTool {
	public:
		RotaryCamera();
		~RotaryCamera();
		virtual void init();

		virtual void update(const RovDataStore & store_);

		virtual void commit(RovDataStore & store_);
	private:
		
		prvt::RotCam m_camOne;
		prvt::RotCam m_camTwo;

		void rotateCam(prvt::RotCam &cam_, int8_t val);

	};

}