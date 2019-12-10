/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 * 2018-10-18
 */


#include "IAR/include/IARController.h"
#include "WorldModels/RobotWorldModel.h"
#include "RoboroboMain/roborobo.h"
#include "World/World.h"

// Load readable sensor names
#define NB_SENSORS 12 // should be coherent with gRobotSpecsImageFilename value read from the property file.
#include "Utilities/Sensorbelt.h"

/* **** **** **** */
/* **** **** **** */
/* **** **** **** */

IARController::IARController( RobotWorldModel *__wm ) : Controller ( __wm )
{
    if ( _wm->_cameraSensorsNb != NB_SENSORS )
    {
        std::cerr << "[CRITICAL] This project assumes robot specifications with " << NB_SENSORS << " sensors (provided: " << _wm->_cameraSensorsNb << " sensors). STOP.\n";
        exit(-1);
    }
    srand (time(NULL));
}

/* **** **** **** */
/* **** **** **** */
/* **** **** **** */
/*
Algos:

Return 0 : On va vers A
Return 1 : on va vers B
Return -1 : On search

*/

//Consume nearest
int IARController::objective(){
  if(getDistance_A() == -1 && getDistance_B() == -1){
    return -1;
  }else{
    return !(getDistance_A()<getDistance_B());
  }
}

/*
//CueXDeficit
int IARController::objective(){
  if(getDistance_A() == -1 && getDistance_B() == -1){
    return -1;
  }else if (getDistance_A() == -1 || getDistance_B() == -1){
    return !(getDistance_A()<getDistance_B());
  }else{
    double cue_A = ((MAXSENSORDISTANCE-getDistance_A())/MAXSENSORDISTANCE)*A_A*(A_MAX - A_value)/A_MAX;
    double cue_B = ((MAXSENSORDISTANCE-getDistance_B())/MAXSENSORDISTANCE)*B_B*(B_MAX - B_value)/B_MAX;
    return !(cue_A > cue_B);
  }
}

//Cost Function  !!!!!implementer pas de detection
int IARController::objective(){
  return !(((A_MAX - A_value)*(A_MAX - A_value)/(A_MAX*A_MAX)) > ((B_MAX - B_value)*(B_MAX - B_value)/(B_MAX*B_MAX)));
}

// One Step Planning Cost Function
int IARController::objective(){
  double A_payoff = A_A;
  double B_payoff = B_B;
  if(getDistance_A() == -1 ){
    A_payoff = 0;
  }
  if(getDistance_B() == -1 ){
    B_payoff = 0;
  }
  double cost_A = (((A_MAX - A_value)/A_MAX) - A_payoff + (A_LOSS_PER_CYCLE*getDistance_A()/DISTANCE_PER_CYCLE))² + (((B_MAX - B_value)/B_MAX) - B_A + (B_LOSS_PER_CYCLE*getDistance_A()/DISTANCE_PER_CYCLE))²;
  double cost_B = (((B_MAX - B_value)/B_MAX) - B_payoff + (B_LOSS_PER_CYCLE*getDistance_B()/DISTANCE_PER_CYCLE))² + (((A_MAX - A_value)/A_MAX) - A_B + (A_LOSS_PER_CYCLE*getDistance_B()/DISTANCE_PER_CYCLE))²;
  int choice = cost_A > cost_B;
  if((choice && getDistance_B() == -1) || (!choice && getDistance_A() == -1) ){
    return -1;
  }else{
    return choice;
  }
}

// Reactive One Step Planning Cost Function
int IARController::objective(){
  double A_payoff = A_A;
  double B_payoff = B_B;
  if(getDistance_A() == -1 ){
    A_payoff = 0;
  }
  if(getDistance_B() == -1 ){
    B_payoff = 0;
  }
  double cost_A = (((A_MAX - A_value)/A_MAX) - A_payoff + (A_LOSS_PER_CYCLE*getDistance_A()/DISTANCE_PER_CYCLE))² + (((B_MAX - B_value)/B_MAX) - B_A + (B_LOSS_PER_CYCLE*getDistance_A()/DISTANCE_PER_CYCLE))²;
  double cost_B = (((B_MAX - B_value)/B_MAX) - B_payoff + (B_LOSS_PER_CYCLE*getDistance_B()/DISTANCE_PER_CYCLE))² + (((A_MAX - A_value)/A_MAX) - A_B + (A_LOSS_PER_CYCLE*getDistance_B()/DISTANCE_PER_CYCLE))²;
  int choice = cost_A > cost_B;
  if((choice && getDistance_B() == -1) || (!choice && getDistance_A() == -1) ){
    if(getDistance_A() == -1 && getDistance_B() == -1){
      return -1;
    }else{
      return !(getDistance_A()<getDistance_B());
    }
  }else{
    return choice;
  }
}

void IARController::explore(){
  _wm->_desiredRotationalVelocity = 0;
  double r = rand();
  if(rand < 0.01){
    if(rand < 0.005){
      target_orientation = _wm->_agentAbsoluteOrientation + 30;
    }else{
      target_orientation = _wm->_agentAbsoluteOrientation - 30;
    }
  }
  if ( target_orientation - _wm->_agentAbsoluteOrientation < 0 )
      _wm->_desiredRotationalVelocity = +10;
  else if( target_orientation - _wm->_agentAbsoluteOrientation > 0 )
      _wm->_desiredRotationalVelocity = -10;
}

*/
void IARController::goToA(){
  _wm->_desiredRotationalVelocity = 0;
  target_orientation = 0;
  Point2d closest_A = getClosestA();
  double angleToA = getAngleToTarget( _wm->_xReal, _wm->_yReal, _wm->_agentAbsoluteOrientation, closest_A.x,closest_A.y);
  if ( angleToA < 0 )
      _wm->_desiredRotationalVelocity = +10;
  else if( angleToA > 0 )
      _wm->_desiredRotationalVelocity = -10;
}

void IARController::goToB(){
  _wm->_desiredRotationalVelocity = 0;
  target_orientation = 0;
  Point2d closest_B = getClosestB();
  double angleToB = getAngleToTarget( _wm->_xReal, _wm->_yReal, _wm->_agentAbsoluteOrientation, closest_B.x,closest_B.y);
  if ( angleToB < 0 )
      _wm->_desiredRotationalVelocity = +10;
  else if( angleToB > 0 )
      _wm->_desiredRotationalVelocity = -10;
}

double IARController::getDistance_A(){
  Point2d closest_A = getClosestA();
  return sqrt(pow((_wm->_xReal - closest_A.x),2)+pow((_wm->_yReal - closest_A.y),2));

}

double IARController::getDistance_B(){
  Point2d closest_B = getClosestB();
  return sqrt(pow((_wm->_xReal - closest_B.x),2)+pow((_wm->_yReal - closest_B.y),2));

}


Point2d IARController::getClosestA(){

  return Point2d(0,0);
}

Point2d IARController::getClosestB(){
  return Point2d(0,0);

}



IARController::~IARController()
{
    // nothing to do.
}

/* **** **** **** */
/* **** **** **** */
/* **** **** **** */

void IARController::reset()
{
    // nothing to do.
}

/* **** **** **** */
/* **** **** **** */
/* **** **** **** */

// called at everytime step. Each robot is called once per timestep, but order of call always change from step to step. This is *the* function (and possibly the only one, in most case) you have to change.
void IARController::step()
{
  _wm->_desiredTranslationalValue = DISTANCE_PER_CYCLE;
  int target = objective();
  if(target == 0)
    goToA();
  else if(target == 1)
    goToB();
  else
    explore();

}
