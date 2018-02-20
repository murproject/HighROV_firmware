
#include "MotorBase.h"

namespace rov {

MotorBase::MotorBase() :m_coef(1)
	{

}

MotorBase::~MotorBase(){

}

void MotorBase::setProportionalCoeff(float coef) {

		m_coef = coef;
}


} // namespace rov
