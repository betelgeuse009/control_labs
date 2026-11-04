#ifndef PIDCONTROLLER_FOTF_H
#define PIDCONTROLLER_FOTF_H

class FOtf {
public:
    FOtf(float Kp, float T, float Ts);

    void setInput(float u);
    float getOutput();

    void simulate();
private:
    float u, y, y_prev;
    float Kp, T, Ts;
};

#endif //PIDCONTROLLER_FOTF_H
