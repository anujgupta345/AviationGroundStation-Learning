#include <iostream>
#include <telemetry/AircraftTelemetry.h>

int main(int argc, char ** argv)
{
    struct AircraftTelemetry telemetry;
    telemetry.Aircraft_ID = 183;
    telemetry.Latitude = 37.7749;
    telemetry.Longitude = -122.4194;
    telemetry.Altitude = 1000.0;
    telemetry.Speed = 250.0;
    std::cout << telemetry.Aircraft_ID << std::endl;
    std::cout << telemetry.Latitude << std::endl;
    std::cout << telemetry.Longitude << std::endl;
    std::cout << telemetry.Altitude << std::endl;
    std::cout << telemetry.Speed << std::endl;

    return 0;
}