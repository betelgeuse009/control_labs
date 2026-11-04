#include <iostream>
#include <iomanip>

#include "FOtf.h"
#include "PID.h"

int main() {
    // Create plant transfer function
    FOtf plant(10.0, 10.0, 0.1);

    // Create a PI controller
    PID PIcontroller(1.0, 10.0, 0.1);

    // Set controller reference
    PIcontroller.setReference(1.0);

    // Simulating and printing data
    float t, y, u;
    t, y, u = 0.0;
    for (int k=0; k<=100; k++)
    {
        // Set measurement
        PIcontroller.setMeasurement(y);

        // Execute PI controller
        PIcontroller.execute();

        // Get control value
        u = PIcontroller.getControl();

        // Set plant input
        plant.setInput(u);

        // Simulate the plant
        plant.simulate();

        // Get measurement
        y = plant.getOutput();

        // Printing data
        std::cout << "Time: " << std::fixed << std::setprecision(1) << t << "\t" << "Plant output: " << std::setprecision(4) << y
        << "\t" << "PI output: " << std::setprecision(4) << u << std::endl;

        // Update time
        t += 0.1;
    }

    return 0;
}
