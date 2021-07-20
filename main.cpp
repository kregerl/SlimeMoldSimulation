#include "Simulation.h"

int main() {
    auto *simulation = new Simulation(1280, 720);
    simulation->run();
    return 0;
}
