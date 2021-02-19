#include <iostream>

#include "Logger.hpp"

void someDummyProcess(Logger &logger) {
    int wait = rand() % 5;
    sleep(wait);
    logger.writeLog(Severity::INFO, "Just a message " + std::to_string(wait) + " seconds later.");
}

int main(int argc, char* argv[])
{
    Logger logger;
    
    logger.init();

    logger.writeLog(Severity::TRACE, "Testing TRACE log.");
    logger.writeLog(Severity::DEBUG, "Testing DEBUG log.");
    logger.writeLog(Severity::INFO, "Testing INFO log.");
    logger.writeLog(Severity::WARNING, "Testing WARNING log.");
    logger.writeLog(Severity::ERROR, "Testing ERROR log.");
    logger.writeLog(Severity::FATAL, "Testing FATAL log.");

    std::string test;
    for (int i = 0; i < 84; i++) {
        test += std::to_string( i % 2 );
    }

    logger.writeLog(Severity::INFO, test);

    logger.writeLog("This is just a header");
    logger.writeLog(Severity::INFO, "Message after the header.");

    someDummyProcess(logger);

    logger.writeLog(Severity::TRACE, __function__);

    logger.writeLog(Severity::DEBUG, "She had been an angel for coming up on 10 years and in all that time nobody had told her this was possible. The fact that it could ever happen never even entered her mind. Yet there she stood, with the undeniable evidence sitting on the ground before her. Angels could lose their wings.");

    std::string somethingRandom = "She had been an angel for coming up on 10 years and in all that time nobody had told her this was possible. The fact that it could ever happen never even entered her mind. Yet there she stood, with the undeniable evidence sitting on the ground before her. Angels could lose their wings.";


    /* logger.beginIterationLog("Dividing the phrase.");
    int prevPos = 0;
    for (int i = 0; i < 20; i++) {
        std::string curIte(somethingRandom.begin() + prevPos, somethingRandom.begin() + prevPos + i);

        logger.writeLog(curIte);

        prevPos += i;
    }
    logger.endIterationLog(); */

    return 0;
}

/*
Haps Simulator

[Article] https://ieeexplore.ieee.org/document/8396531  -> Modelica OOP? "The acausal and object-oriented modeling language Modelica has been used to create the integrated simulation model, enabling a modular and detailed modeling approach."

Será isto?
https://www.simulationx.com/simulation-software/experts/modelica-simulation.html
ou isto?
https://openmodelica.org/uncategorised/191-omsimulator


[Web Site] https://www.atlanticmicrowave.com/application/haps-high-altitude-pseudo-satellite-testing

https://www.atlanticmicrowave.com/news/2021/02/bench-mounted-satellite-simulator-equipment

https://www.atlanticmicrowave.com/markets/satellite-communications

Sao apenas produtos/hardware que se pode comprar para simular?


Drones Simulator -> The best ones are paid, and are not opensource...

[Software] https://www.dji.com/pt/simulator  -> uff

[Software] https://zephyr-sim.com/ -> Zephyr

[GitHub OPENSOURCE!!] https://github.com/microsoft/AirSim -> You would have to understand the code to manage whatever else you want.

Other opensources... But not smelling that good... https://opensource.com/article/18/2/drone-projects


Last resource...
> Develop a simulation on Unity / Unreal Engine 4.
What would this imply? Lots of time developing the scene... Simulating the physics more precisely for more relevant results...


*/