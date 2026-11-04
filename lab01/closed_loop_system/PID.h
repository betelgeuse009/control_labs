#ifndef PIDCONTROLLER_PID_H
#define PIDCONTROLLER_PID_H

class PID {
public:
    PID(float Kc, float Ts);
    PID(float Kc, float Ti, float Ts);
    PID(float Kc, float Td, float N, float Ts);
    PID(float Kc, float Ti, float Td, float N, float Ts);

    void setMeasurement(float y);
    void setReference(float ysp);
    float getControl();

    void execute();
private:
    float y, ysp, u;
    float Kc, Ti, Td, N, Ts;
    float uI_prev, uD_prev, e_prev;
};

#endif //PIDCONTROLLER_PID_H
