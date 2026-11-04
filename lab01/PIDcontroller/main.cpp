#include <iostream>
#include <iomanip>

#include "PID.h"

int main() {
    // Create a P controller
    PID Pcontroller(0.5, 0.01);

    // Create a PI controller
    PID PIcontroller(0.5, 2.0, 0.01);

    // Create a PD controller
    PID PDcontroller(1.5, 0.5, 50.0, 0.01);

    // Create a PID controller
    PID PIDcontroller(2.5, 1.5, 0.5, 55.0, 0.01);

    // Setting measurement and reference
    Pcontroller.setMeasurement(0.5);
    Pcontroller.setReference(1.0);

    PIcontroller.setMeasurement(0.5);
    PIcontroller.setReference(1.0);

    PDcontroller.setMeasurement(0.5);
    PDcontroller.setReference(1.0);

    PIDcontroller.setMeasurement(0.5);
    PIDcontroller.setReference(1.0);

    // Executing PI controller
    Pcontroller.execute();
    PIcontroller.execute();
    PDcontroller.execute();
    PIDcontroller.execute();

    // Getting control value
    const float cv_P  = Pcontroller.getControl();
    const float cv_PI = PIcontroller.getControl();
    const float cv_PD = PDcontroller.getControl();
    const float cv_PID = PIDcontroller.getControl();

    // Plotting control value
    std::cout << "P controller output:   " << cv_P << std::endl;
    std::cout << "PI controller output:  " << cv_PI << std::endl;
    std::cout << "PD controller output:  " << cv_PD << std::endl;
    std::cout << "PID controller output: " << cv_PID << std::endl;

    return 0;
}
