#include <iostream>
#include <iomanip>

#include "FOtf.h"

int main() {
    // Create a first order transfer function
    const float Kp = 1.0;
    const float T  = 10.0;
    const float Ts = 0.1;
    FOtf plant(Kp, T, Ts);

    // Setting input
    plant.setInput(1.0);

    // Simulating and printing data
    float t = 0.0;
    for (int k=0; k<=100; k++)
    {
        // Simulating the plant
        plant.simulate();

        // Getting output value
        float y = plant.getOutput();

        // Printing data
        std::cout << "Time: " << std::fixed << std::setprecision(1) << t << "\t" << "Output: " << std::setprecision(4) << y << std::endl;

        // Update time
        t += Ts;
    }

    return 0;
}
