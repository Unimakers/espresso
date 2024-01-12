#include "lidar.hpp"

namespace lidar {

void task(void* pvParameters)
{
    Lidar* lidar = static_cast<Lidar*>(pvParameters);
    lidar->loop();
}

void startService(Lidar& lidar)
{
    void* params = static_cast<void*>(&lidar);
    xTaskCreatePinnedToCore(task, "LIDAR", 1000, params, 6, NULL, 1);
}

Lidar::Lidar()
    : _bined_serialdev(NULL)
{
    _currentMeasurement.distance = 0;
    _currentMeasurement.angle = 0;
    _currentMeasurement.quality = 0;
    _currentMeasurement.startBit = 0;
}

Lidar::~Lidar() { end(); }

void Lidar::setup(LidarConfig& config)
{
    begin(config.serial);
    setLidarSpeed(config.motor_speed);
    setMotorPin(config.motor_pin);
    startScan(false, config.timeout);
}

void Lidar::setLidarSpeed(int speed) { _lidar_speed = speed; }

void Lidar::setMotorPin(int pin) { _lidar_motor_pin = pin; }

void Lidar::reconnect()
{
    analogWrite(_lidar_motor_pin, 0);
    delay(15);
    lidar_response_device_info_t info;
    if (IS_OK(getDeviceInfo(info, 100))) {
        Serial.println("Lidar Detected...");
        startScan();
        analogWrite(_lidar_motor_pin, _lidar_speed);
        delay(50);
    }
}

const void Lidar::loop()
{
    while (true) {
        if (IS_OK(scan()))
            continue;
        Lidar::reconnect();
    }
}

const LidarPoint& Lidar::getCurrentPoint() { return _currentMeasurement; }
// open the given serial interface and try to connect to the LIDAR
void Lidar::begin(HardwareSerial& serial)
{
    if (isOpen()) {
        end();
    }
    _bined_serialdev = &serial;
    _bined_serialdev->end();
    _bined_serialdev->begin(LIDAR_SERIAL_BAUDRATE);
}

// close the currently opened serial interface
void Lidar::end()
{
    if (isOpen()) {
        _bined_serialdev->end();
        _bined_serialdev = NULL;
    }
}

// check whether the serial interface is opened
bool Lidar::isOpen() { return _bined_serialdev ? true : false; }

// ask the LIDAR for its health info
u_result Lidar::getHealth(lidar_response_device_health_t& healthinfo,
    _u32 timeout)
{
    _u32 currentTs = millis();
    _u32 remainingtime;

    _u8* infobuf = (_u8*)&healthinfo;
    _u8 recvPos = 0;

    lidar_ans_header_t response_header;
    u_result ans;

    if (!isOpen())
        return RESULT_OPERATION_FAIL;

    {
        if (IS_FAIL(ans = _sendCommand(LIDAR_CMD_GET_DEVICE_HEALTH, NULL, 0))) {
            return ans;
        }

        if (IS_FAIL(ans = _waitResponseHeader(&response_header, timeout))) {
            return ans;
        }

        // verify whether we got a correct header
        if (response_header.type != LIDAR_ANS_TYPE_DEVHEALTH) {
            return RESULT_INVALID_DATA;
        }

        if ((response_header.size) < sizeof(lidar_response_device_health_t)) {
            return RESULT_INVALID_DATA;
        }

        while ((remainingtime = millis() - currentTs) <= timeout) {
            int currentbyte = _bined_serialdev->read();
            if (currentbyte < 0)
                continue;

            infobuf[recvPos++] = currentbyte;

            if (recvPos == sizeof(lidar_response_device_health_t)) {
                return RESULT_OK;
            }
        }
    }
    return RESULT_OPERATION_TIMEOUT;
}
u_result Lidar::startScan(bool force, _u32 timeout)
{
    u_result ans;

    if (!isOpen())
        return RESULT_OPERATION_FAIL;

    stop(); // force the previous operation to stop

    {
        ans = _sendCommand(force ? LIDAR_CMD_FORCE_SCAN : LIDAR_CMD_SCAN, NULL, 0);
        if (IS_FAIL(ans))
            return ans;

        // waiting for confirmation
        lidar_ans_header_t response_header;
        if (IS_FAIL(ans = _waitResponseHeader(&response_header, timeout))) {
            return ans;
        }

        // verify whether we got a correct header
        if (response_header.type != LIDAR_ANS_TYPE_MEASUREMENT) {
            return RESULT_INVALID_DATA;
        }

        if (response_header.size < sizeof(lidar_response_measurement_node_t)) {
            return RESULT_INVALID_DATA;
        }
    }
    return RESULT_OK;
}
// ask the LIDAR for its device info like the serial number
u_result Lidar::getDeviceInfo(lidar_response_device_info_t& info,
    _u32 timeout)
{
    _u8 recvPos = 0;
    _u32 currentTs = millis();
    _u32 remainingtime;
    _u8* infobuf = (_u8*)&info;
    lidar_ans_header_t response_header;
    u_result ans;

    if (!isOpen())
        return RESULT_OPERATION_FAIL;

    {
        if (IS_FAIL(ans = _sendCommand(LIDAR_CMD_GET_DEVICE_INFO, NULL, 0))) {
            return ans;
        }

        if (IS_FAIL(ans = _waitResponseHeader(&response_header, timeout))) {
            return ans;
        }

        // verify whether we got a correct header
        if (response_header.type != LIDAR_ANS_TYPE_DEVINFO) {
            return RESULT_INVALID_DATA;
        }

        if (response_header.size < sizeof(lidar_response_device_info_t)) {
            return RESULT_INVALID_DATA;
        }

        while ((remainingtime = millis() - currentTs) <= timeout) {
            int currentbyte = _bined_serialdev->read();
            if (currentbyte < 0)
                continue;
            infobuf[recvPos++] = currentbyte;

            if (recvPos == sizeof(lidar_response_device_info_t)) {
                return RESULT_OK;
            }
        }
    }

    return RESULT_OPERATION_TIMEOUT;
}

// stop the measurement operation
u_result Lidar::stop()
{
    if (!isOpen())
        return RESULT_OPERATION_FAIL;
    u_result ans = _sendCommand(LIDAR_CMD_STOP, NULL, 0);
    return ans;
}

// wait for one sample point to arrive
u_result Lidar::scan(_u32 timeout)
{
    _u32 currentTs = millis();
    _u32 remainingtime;
    lidar_response_measurement_node_t node;
    _u8* nodebuf = (_u8*)&node;

    _u8 recvPos = 0;

    while ((remainingtime = millis() - currentTs) <= timeout) {
        int currentbyte = _bined_serialdev->read();
        if (currentbyte < 0)
            continue;

        switch (recvPos) {
        case 0: // expect the sync bit and its reverse in this byte          {
        {
            _u8 tmp = (currentbyte >> 1);
            if ((tmp ^ currentbyte) & 0x1) {
                // pass
            } else {
                continue;
            }

        } break;
        case 1: // expect the highest bit to be 1
        {
            if (currentbyte & LIDAR_RESP_MEASUREMENT_CHECKBIT) {
                // pass
            } else {
                recvPos = 0;
                continue;
            }
        } break;
        }
        nodebuf[recvPos++] = currentbyte;

        if (recvPos == sizeof(lidar_response_measurement_node_t)) {
            // store the data ...
            _currentMeasurement.distance = node.distance_q2 / 4.0f;
            _currentMeasurement.angle = (node.angle_q6_checkbit >> LIDAR_RESP_MEASUREMENT_ANGLE_SHIFT) / 64.0f;
            _currentMeasurement.quality = (node.sync_quality >> LIDAR_RESP_MEASUREMENT_QUALITY_SHIFT);
            _currentMeasurement.startBit = (node.sync_quality & LIDAR_RESP_MEASUREMENT_SYNCBIT);
            return RESULT_OK;
        }
    }

    return RESULT_OPERATION_TIMEOUT;
}

u_result Lidar::_sendCommand(_u8 cmd, const void* payload, size_t payloadsize)
{
    lidar_cmd_packet_t pkt_header;
    lidar_cmd_packet_t* header = &pkt_header;
    _u8 checksum = 0;

    if (payloadsize && payload) {
        cmd |= LIDAR_CMDFLAG_HAS_PAYLOAD;
    }

    header->syncByte = LIDAR_CMD_SYNC_BYTE;
    header->cmd_flag = cmd;

    // send header first
    _bined_serialdev->write((uint8_t*)header, 2);

    if (cmd & LIDAR_CMDFLAG_HAS_PAYLOAD) {
        checksum ^= LIDAR_CMD_SYNC_BYTE;
        checksum ^= cmd;
        checksum ^= (payloadsize & 0xFF);

        // calc checksum
        for (size_t pos = 0; pos < payloadsize; ++pos) {
            checksum ^= ((_u8*)payload)[pos];
        }

        // send size
        _u8 sizebyte = payloadsize;
        _bined_serialdev->write((uint8_t*)&sizebyte, 1);

        // send payload
        _bined_serialdev->write((uint8_t*)&payload, sizebyte);

        // send checksum
        _bined_serialdev->write((uint8_t*)&checksum, 1);
    }

    return RESULT_OK;
}

u_result Lidar::_waitResponseHeader(lidar_ans_header_t* header, _u32 timeout)
{
    _u8 recvPos = 0;
    _u32 currentTs = millis();
    _u32 remainingtime;
    _u8* headerbuf = (_u8*)header;
    while ((remainingtime = millis() - currentTs) <= timeout) {
        int currentbyte = _bined_serialdev->read();
        if (currentbyte < 0)
            continue;
        switch (recvPos) {
        case 0:
            if (currentbyte != LIDAR_ANS_SYNC_BYTE1) {
                continue;
            }
            break;
        case 1:
            if (currentbyte != LIDAR_ANS_SYNC_BYTE2) {
                recvPos = 0;
                continue;
            }
            break;
        }
        headerbuf[recvPos++] = currentbyte;

        if (recvPos == sizeof(lidar_ans_header_t)) {
            return RESULT_OK;
        }
    }
    return RESULT_OPERATION_TIMEOUT;
}
} // namespace lidar
