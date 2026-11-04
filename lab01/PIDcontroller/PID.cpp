#include "PID.h"

#include <iostream>

PID::PID(float Kc, float Ts) {
    this->Kc = Kc;
    this->Ts = Ts;

    // Set unused parameters to -1
    this->Ti = -1.0;
    this->Td = -1.0;
    this->N  = -1.0;

    // Initialize internal variables
    y = ysp = u = 0.0;
    uI_prev = uD_prev = e_prev = 0.0;
}

PID::PID(float Kc, float Ti, float Ts) {
    this->Kc = Kc;
    this->Ti = Ti;
    this->Ts = Ts;

    // Set unused parameters to -1
    this->Td = -1.0;
    this->N  = -1.0;

    // Initialize internal variables
    y = ysp = u = 0.0;
    uI_prev = uD_prev = e_prev = 0.0;
}

PID::PID(float Kc, float Td, float N, float Ts) {
    this->Kc = Kc;
    this->Td = Td;
    this->N  = N;
    this->Ts = Ts;

    // Set unused parameters to -1
    this->Ti = -1.0;

    // Initialize internal variables
    y = ysp = u = 0.0;
    uI_prev = uD_prev = e_prev = 0.0;
}

PID::PID(float Kc, float Ti, float Td, float N, float Ts) {
    this->Kc = Kc;
    this->Ti = Ti;
    this->Td = Td;
    this->N  = N;
    this->Ts = Ts;

    // Initialize internal variables
    y = ysp = u = 0.0;
    uI_prev = uD_prev = e_prev = 0.0;
}

void PID::execute() {
    // Compute actual error
    const float e = ysp-y;

    // Compute integral action
    float uI = 0.0;
    if (Ti>0.0)
    {
        uI = uI_prev+Kc*Ts/Ti*e;
    }

    // Compute derivative action
    float uD = 0.0;
    if (Td>0.0)
    {
        uD = Td/(N*Ts+Td)*uD_prev+Kc*N*(e-e_prev);
    }

    // Compute control action
    u = Kc*e+uI+uD;

    // Update controller state
    e_prev = e;
    uI_prev = uI;
    uD_prev = uD;
}

void PID::setMeasurement(float y) {
    this->y = y;
}

void PID::setReference(float ysp) {
    this->ysp = ysp;
}

float PID::getControl() {
    return u;
}
