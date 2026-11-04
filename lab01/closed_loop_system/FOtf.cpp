#include "FOtf.h"

#include <iostream>

FOtf::FOtf(float Kp, float T, float Ts) {
    this->Kp = Kp;
    this->T  = Kp;
    this->Ts = Ts;

    // Initialize internal variables
    u = y = y_prev = 0.0;
}

void FOtf::simulate() {
    // Compute the output according to backword Euler discretization
    y = T/(T+Ts)*y_prev+Kp*Ts/(T+Ts)*u;

    // Update system state
    y_prev = y;
}

void FOtf::setInput(float u) {
    this->u = u;
}

float FOtf::getOutput() {
    return y;
}
