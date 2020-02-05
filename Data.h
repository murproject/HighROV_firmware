// RovDataTypes.h

#ifndef _ROVDATATYPES_h
#define _ROVDATATYPES_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <stdint.h>
#include "Crc.h"


namespace rov {
    struct RovControl;
    struct RovTelimetry;

    namespace prvt {
        template <typename T>
        inline T swap_endian(T u) {

            union
            {
                T u;
                unsigned char u8[sizeof(T)];
            } source, dest;

            source.u = u;

            for (size_t k = 0; k < sizeof(T); k++)
                dest.u8[k] = source.u8[sizeof(T) - k - 1];

            return dest.u;
        }

        void swap_endian_for(RovControl &rc);

        void swap_endian_for(RovTelimetry &rt);
    };



    struct RovControl {
        enum class RovControlErrorCode : int {
            NoError = 0,
            WrongCrc = 1,
            WrongDataSize = 2,
        };

        int8_t axisX = 0; //! -100/100;    
        int8_t axisY = 0; //! -100/100;    
        int8_t axisZ = 0; //! -100/100;    
        int8_t axisW = 0; //! -100/100;
        int8_t cameraRotation[2] = { 0, 0 };
        int8_t thrusterPower[6] = { 0, 0, 0, 0, 0, 0 };
        uint8_t debugFlag = 0;
        int8_t manipulatorRotation = 0; //! -100/100    
        int8_t manipulatorOpenClose = 0; //! -1 close/+1 open;
        uint8_t regulators = 0; //! 1st bit - depth;
        float desiredDepth = 0.0f;

        RovControlErrorCode fromRovControlMsg(const uint8_t *msg, unsigned long size) {
            size_t i = 0;

            memcpy(&axisX, msg + i, sizeof(axisX));
            i += sizeof(axisX);
            memcpy(&axisY, msg + i, sizeof(axisY));
            i += sizeof(axisY);
            memcpy(&axisZ, msg + i, sizeof(axisZ));
            i += sizeof(axisZ);
            memcpy(&axisW, msg + i, sizeof(axisW));
            i += sizeof(axisW);

            memcpy(&debugFlag, msg + i, sizeof(debugFlag));
            i += sizeof(debugFlag);

            memcpy(&thrusterPower[0], msg + i, sizeof(thrusterPower[0]));
            i += sizeof(thrusterPower[0]);
            memcpy(&thrusterPower[1], msg + i, sizeof(thrusterPower[1]));
            i += sizeof(thrusterPower[1]);
            memcpy(&thrusterPower[2], msg + i, sizeof(thrusterPower[2]));
            i += sizeof(thrusterPower[2]);
            memcpy(&thrusterPower[3], msg + i, sizeof(thrusterPower[3]));
            i += sizeof(thrusterPower[3]);
            memcpy(&thrusterPower[4], msg + i, sizeof(thrusterPower[4]));
            i += sizeof(thrusterPower[4]);
            memcpy(&thrusterPower[5], msg + i, sizeof(thrusterPower[5]));
            i += sizeof(thrusterPower[5]);

            memcpy(&manipulatorRotation, msg + i, sizeof(manipulatorRotation));
            i += sizeof(manipulatorRotation);

            memcpy(&cameraRotation[0], msg + i, sizeof(cameraRotation[0]));
            i += sizeof(cameraRotation[0]);
            memcpy(&cameraRotation[1], msg + i, sizeof(cameraRotation[1]));
            i += sizeof(cameraRotation[1]);

            memcpy(&manipulatorOpenClose, msg + i, sizeof(manipulatorOpenClose));
            i += sizeof(manipulatorOpenClose);

            memcpy(&regulators, msg + i, sizeof(regulators));
            i += sizeof(regulators);
            memcpy(&desiredDepth, msg + i, sizeof(desiredDepth));
            i += sizeof(desiredDepth);

            uint16_t crc = 0;
            memcpy(&crc, msg + i, sizeof(crc));

            prvt::swap_endian_for(*this);
            crc = prvt::swap_endian<int16_t>(crc);


            uint16_t currentCrc = calculateCRC((const char *)msg, i);
            if (crc != currentCrc) {
                return RovControlErrorCode::WrongCrc;
            }
            return RovControlErrorCode::NoError;
        }

        static String fromErrorToString(RovControlErrorCode ec) {
            switch (ec) {
            case RovControlErrorCode::NoError: return "No error";
            case RovControlErrorCode::WrongCrc: return "CRC missmatch";
            case RovControlErrorCode::WrongDataSize: return "Wrong data size";
            }
        }

    };


    struct RovTelimetry {
        float depth = 0.0f;
        float pitch = 0; //! -180/180;    
        float yaw = 0; //! 0 - 360;    
        float roll = 0; //! -180/180;
        float ammeter = 0.0f;
        float voltmeter = 0.0f; 
        uint8_t regulatorsFeedback = 0;
        int8_t manipulatorAngle = 0; //! ???
        int8_t manipulatorState = 0; //! -1 close/+1 open;

        size_t toRovTelemetryMsg(uint8_t *msg) {
            size_t i = 0;
            RovTelimetry rt = *this;
            prvt::swap_endian_for(rt);

            memcpy(msg, &rt.depth, sizeof(rt.depth));
            i += sizeof(rt.depth);
            memcpy(msg + i, &rt.pitch, sizeof(rt.pitch));
            i += sizeof(rt.pitch);
            memcpy(msg + i, &rt.yaw, sizeof(rt.yaw));
            i += sizeof(rt.yaw);
            memcpy(msg + i, &rt.roll, sizeof(rt.roll));
            i += sizeof(rt.roll);
            memcpy(msg + i, &rt.ammeter, sizeof(rt.ammeter));
            i += sizeof(rt.ammeter);
            memcpy(msg + i, &rt.voltmeter, sizeof(rt.voltmeter));
            i += sizeof(rt.voltmeter);
            memcpy(msg + i, &rt.regulatorsFeedback, sizeof(rt.regulatorsFeedback));
            i += sizeof(rt.regulatorsFeedback);
            memcpy(msg + i, &rt.manipulatorAngle, sizeof(rt.manipulatorAngle));
            i += sizeof(rt.manipulatorAngle);
            memcpy(msg + i, &rt.manipulatorState, sizeof(rt.manipulatorState));
            i += sizeof(rt.manipulatorState);

            int16_t crc = prvt::swap_endian<int16_t>(calculateCRC((const char *)msg, i));
            memcpy(msg + i, &crc, sizeof(crc));
            i += sizeof(crc);

            return i;
        }
    };

}
#endif
