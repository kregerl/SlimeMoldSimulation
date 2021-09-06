#include "Simulation.h"

int main(int argc, char **argv) {
    auto *simulation = new Simulation(1280, 720);
    simulation->run();
    return 0;
}
