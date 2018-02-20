#include "RotaryCamera.h"
#include "RovMagics.h"

namespace rov {
	RotaryCamera::RotaryCamera()
	{
		m_camOne.angle = RotaryCameraConfig::CAM_ONE_DEFAULT_ANGLE;
		m_camOne.min_angle = RotaryCameraConfig::CAM_ONE_MIN_ANGLE;
		m_camOne.max_angle = RotaryCameraConfig::CAM_ONE_MAX_ANGLE;

		m_camTwo.angle = RotaryCameraConfig::CAM_TWO_DEFAULT_ANGLE;
		m_camTwo.min_angle = RotaryCameraConfig::CAM_TWO_MIN_ANGLE;
		m_camTwo.max_angle = RotaryCameraConfig::CAM_TWO_MAX_ANGLE;
	}


	RotaryCamera::~RotaryCamera()
	{
		m_camOne.cam.detach();
		m_camTwo.cam.detach();
	}

	void RotaryCamera::init()
	{
		m_camOne.cam.attach(RotaryCameraConfig::CAM_FRONT_PIN);
		m_camTwo.cam.attach(RotaryCameraConfig::CAM_BACK_PIN);
		m_camOne.cam.write(m_camOne.angle);
		m_camTwo.cam.write(m_camTwo.angle);
		delay(100);
	}

	void RotaryCamera::update(const RovDataStore & store_)
	{
		if (store_.getControl().cameraRotation[0] != 0) {
			rotateCam(m_camOne, store_.getControl().cameraRotation[0]);
		}
		if (store_.getControl().cameraRotation[1] != 0) {
			rotateCam(m_camTwo, store_.getControl().cameraRotation[1]);
		}
	}

	void RotaryCamera::commit(RovDataStore & store_)
	{
	}
	void RotaryCamera::rotateCam(prvt::RotCam &cam_, int8_t val)
	{
		cam_.angle += constrain(val, -2, 2);
		cam_.angle = constrain(cam_.angle, cam_.min_angle, cam_.max_angle);
		cam_.cam.write(cam_.angle);
	}
}