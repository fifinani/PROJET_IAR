/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 * 2018-10-18
 */


#include "TMEbraitenberg/include/TMEbraitenbergController.h"
#include "WorldModels/RobotWorldModel.h"
#include "RoboroboMain/roborobo.h"
#include "World/World.h"

// Load readable sensor names
#define NB_SENSORS 12 // should be coherent with gRobotSpecsImageFilename value read from the property file.
#include "Utilities/Sensorbelt.h"

TMEbraitenbergController::TMEbraitenbergController( RobotWorldModel *__wm ) : Controller ( __wm )
{
    if ( _wm->_cameraSensorsNb != NB_SENSORS )
    {
        std::cerr << "[CRITICAL] This project assumes robot specifications with " << NB_SENSORS << " sensors (provided: " << _wm->_cameraSensorsNb << " sensors). STOP.\n";
        exit(-1);
    }
}

TMEbraitenbergController::~TMEbraitenbergController()
{
    // nothing to do.
}

void TMEbraitenbergController::reset()
{
    // nothing to do.
}

void TMEbraitenbergController::step()
{
    double poids[9] = {1,1,1,1,0.2,-1,-1,-1,-1};
    int i;
    double rotation = 0;
    for(i=0;i<9;i++){
      rotation += -getDistanceAt(i)*poids[i]/4.2;
    }
    setRotation(rotation);
    setTranslation(1);
}
