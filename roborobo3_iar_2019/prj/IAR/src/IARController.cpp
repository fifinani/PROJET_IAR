/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 * 2018-10-18
 */

 #include <iostream>
 #include <fstream>
 #include <string>

#include "IAR/include/IARController.h"
#include "WorldModels/RobotWorldModel.h"
#include "RoboroboMain/roborobo.h"
#include "World/World.h"


// Load readable sensor names
#define NB_SENSORS 8 // should be coherent with gRobotSpecsImageFilename value read from the property file.
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
    std::string str = "gALossPerCycle";
    if ( gProperties.hasProperty( str ) == true )
    {
        convertFromString<double>(ALossPerCycle, gProperties.getProperty( str ), std::dec);
    }
    else
    {
        ALossPerCycle = A_LOSS_PER_CYCLE;
    }
    str = "gBLossPerCycle";
    if ( gProperties.hasProperty( str ) == true )
    {
        convertFromString<double>(BLossPerCycle, gProperties.getProperty( str ), std::dec);
    }
    else
    {
        BLossPerCycle = B_LOSS_PER_CYCLE;
    }
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
/*
//Consume nearest
int IARController::objective(){
  if(closest_dist_A == -1 && closest_dist_B == -1){
    return -1;
  }else{
    return closest_dist_A == -1 || ( !(closest_dist_A<closest_dist_B) && closest_dist_B!=-1 );
  }
}*/

/*
//CueXDeficit
int IARController::objective(){
  if(closest_dist_A == -1 && closest_dist_B == -1){
    return -1;
  }else if (closest_dist_A == -1 || closest_dist_B == -1){
    return closest_dist_A < closest_dist_B;
  }else{
    double cue_A = ((MAXSENSORDISTANCE-closest_dist_A)/MAXSENSORDISTANCE)*A_A*(A_MAX - _wm->getEnergyLevel_A())/A_MAX;
    double cue_B = ((MAXSENSORDISTANCE-closest_dist_B)/MAXSENSORDISTANCE)*B_B*(B_MAX - _wm->getEnergyLevel_B())/B_MAX;
    return !(cue_A > cue_B);
  }
}*/
/*
//Cost Function  !!!!!implementer pas de detection
int IARController::objective(){
    bool obj = !(((A_MAX - _wm->getEnergyLevel_A())*(A_MAX -_wm->getEnergyLevel_A())/(A_MAX*A_MAX)) > ((B_MAX - _wm->getEnergyLevel_B())*(B_MAX - _wm->getEnergyLevel_B())/(B_MAX*B_MAX)));
    if( (obj == 0 && closest_dist_A == -1) || (obj == 1 && closest_dist_B == -1)){
    return -1;
    }
    return obj;
}*/
/*
// One Step Planning Cost Function
int IARController::objective(){
  double A_payoff = A_A;
  double B_payoff = B_B;
  if(closest_dist_A == -1 ){
    A_payoff = 0;
  }
  if(closest_dist_B == -1 ){
    B_payoff = 0;
  }
  double cost_A = std::pow((((A_MAX - _wm->getEnergyLevel_A())/A_MAX) - A_payoff + (ALossPerCycle*closest_dist_A/DISTANCE_PER_CYCLE)),2) + std::pow((((B_MAX - _wm->getEnergyLevel_B())/B_MAX) - B_A + (BLossPerCycle*closest_dist_A/DISTANCE_PER_CYCLE)),2);
  double cost_B = std::pow((((B_MAX - _wm->getEnergyLevel_B())/B_MAX) - B_payoff + (BLossPerCycle*closest_dist_B/DISTANCE_PER_CYCLE)),2) + std::pow((((A_MAX - _wm->getEnergyLevel_A())/A_MAX) - A_B + (ALossPerCycle*closest_dist_B/DISTANCE_PER_CYCLE)),2);
  int choice = cost_A > cost_B;
  if((choice && closest_dist_B == -1) || (!choice && closest_dist_A == -1) ){
    return -1;
  }else{
    return choice;
  }
}*/

// Reactive One Step Planning Cost Function
int IARController::objective(){
  double A_payoff = A_A;
  double B_payoff = B_B;
  if(closest_dist_A == -1 ){
    A_payoff = 0;
  }
  if(closest_dist_B == -1 ){
    B_payoff = 0;
  }
  double cost_A = std::pow((((A_MAX - _wm->getEnergyLevel_A())/A_MAX) - A_payoff + (ALossPerCycle*closest_dist_A/DISTANCE_PER_CYCLE)),2) + std::pow((((B_MAX -_wm->getEnergyLevel_B())/B_MAX) - B_A + (BLossPerCycle*closest_dist_A/DISTANCE_PER_CYCLE)),2);
  double cost_B = std::pow((((B_MAX - _wm->getEnergyLevel_B())/B_MAX) - B_payoff + (BLossPerCycle*closest_dist_B/DISTANCE_PER_CYCLE)),2) + std::pow((((A_MAX - _wm->getEnergyLevel_A())/A_MAX) - A_B + (ALossPerCycle*closest_dist_B/DISTANCE_PER_CYCLE)),2);
  int choice = cost_A > cost_B;
  if((choice && closest_dist_B == -1) || (!choice && closest_dist_A == -1) ){
    if(closest_dist_A == -1 && closest_dist_B == -1){
      return -1;
    }else{
      return closest_dist_A < closest_dist_B ;
    }
  }else{
    return choice;
  }
}

void IARController::explore(){
  _wm->_desiredRotationalVelocity = 0;
  double r = (double)rand()/(double)RAND_MAX;

  if(r < 0.01){
    if(r < 0.005){
      _wm->_agentAbsoluteOrientation = _wm->_agentAbsoluteOrientation + 30;
    }else{
      _wm->_agentAbsoluteOrientation = _wm->_agentAbsoluteOrientation - 30;
    }
  }
  if ( target_orientation - _wm->_agentAbsoluteOrientation < 0 )
      _wm->_desiredRotationalVelocity = +10;
  else if( target_orientation - _wm->_agentAbsoluteOrientation > 0 )
      _wm->_desiredRotationalVelocity = -10;

}

void IARController::goToA(){
  _wm->_desiredRotationalVelocity = 0;
  target_orientation = 0;
  Point2d closest_A = getClosestA();
  double angleToA = getAngleToTarget( _wm->_xReal, _wm->_yReal, _wm->_agentAbsoluteOrientation, closest_A.x +_directionX_A*gAreaWidth , closest_A.y +_directionY_A*gAreaHeight);
  // std::cout << "angle to A : " << angleToA << std::endl;
  if ( angleToA < 0 )
      _wm->_desiredRotationalVelocity = -10;
  else if( angleToA > 0 )
      _wm->_desiredRotationalVelocity = 10;
  // _wm->_agentAbsoluteOrientation = _wm->_agentAbsoluteOrientation + angleToA;
}

void IARController::goToB(){
  _wm->_desiredRotationalVelocity = 0;
  target_orientation = 0;
  Point2d closest_B = getClosestB();
  double angleToB = getAngleToTarget( _wm->_xReal, _wm->_yReal, _wm->_agentAbsoluteOrientation, closest_B.x+_directionX_B*gAreaWidth,closest_B.y+_directionY_B*gAreaHeight);
  // std::cout << "angle to B : " << angleToB << std::endl;
  if ( angleToB < 0 )
      _wm->_desiredRotationalVelocity = -10;
  else if( angleToB > 0 )
      _wm->_desiredRotationalVelocity = 10;
  // _wm->_agentAbsoluteOrientation = _wm->_agentAbsoluteOrientation + angleToB;

}

double IARController::getDistance_A(){
  Point2d closest_A = getClosestA();
  return sqrt(pow((_wm->_xReal - closest_A.x),2)+pow((_wm->_yReal - closest_A.y),2));

}

double IARController::getDistance_B(){
  Point2d closest_B = getClosestB();
  return sqrt(pow((_wm->_xReal - closest_B.x),2)+pow((_wm->_yReal - closest_B.y),2));

}

double IARController::getDistance(PhysicalObject * obj){

  return sqrt(pow((_wm->_xReal - obj->getXReal()),2)+pow((_wm->_yReal - obj->getYReal()),2));
}

double IARController::getDistance(PhysicalObject * obj, int &directionX, int& directionY){
  return ToroidalDistance(_wm->_xReal, _wm->_yReal, obj->getXReal(),obj->getYReal(),directionX, directionY);
}

double IARController::ToroidalDistance (double x1, double y1, double x2, double y2, int& directionX, int& directionY)
{
    double dx = std::abs(x2 - x1);
    double dy = std::abs(y2 - y1);

    directionX = 0;
    if (dx > gAreaWidth/2){
      dx = gAreaWidth - dx;
      if(x1 > gAreaWidth/2)
        directionX = 1;
      else
        directionX = -1;
    }

    directionY = 0;
    if (dy > gAreaHeight/2){
      dy = gAreaHeight - dy;
      if(y1 > gAreaHeight/2)
        directionY = 1;
      else
        directionY = -1;
    }
    return std::sqrt(dx*dx + dy*dy);
}

// TODO if not define !
Point2d IARController::getClosestA(){
  return Point2d(closest_A->getXReal(),closest_A->getYReal());
}

// TODO if not define !
Point2d IARController::getClosestB(){
  return Point2d(closest_B->getXReal(),closest_B->getYReal());

}

/** L'objet obj est il à porter de senseur
**/
bool IARController::isInRange(PhysicalObject * obj){
  int dirX, dirY;
    return getDistance(obj,dirX,dirY) < MAXSENSORDISTANCE ;
}


void IARController::setClosest_A(){
  int dist = -1;
  int dirX = 0 , dirY = 0;
  for(size_t i = 0 ; i < gPhysicalObjects.size() ; i++){
    if ( ( dist == -1 || getDistance(gPhysicalObjects[i],dirX,dirY) < dist ) && gPhysicalObjects[i]->getType() == 0 && isInRange(gPhysicalObjects[i]) ){
      dist = getDistance(gPhysicalObjects[i],_directionX_A, _directionY_A);
      closest_A = gPhysicalObjects[i];
    }
  }
  closest_dist_A = dist;
}

void IARController::setClosest_B(){
  int dist = -1;
  int dirX = 0 , dirY = 0;
  for(size_t i = 0 ; i < gPhysicalObjects.size() ; i++){
    if ( ( dist == -1 || getDistance(gPhysicalObjects[i],dirX,dirY) < dist ) && gPhysicalObjects[i]->getType() == 1 && isInRange(gPhysicalObjects[i]) ){
      dist = getDistance(gPhysicalObjects[i],_directionX_B,_directionY_B);
      closest_B = gPhysicalObjects[i];
    }
  }
  closest_dist_B = dist;
}

/** Evite le double parcours pour la mise à jour des infos A et B
**/
void IARController::setClosests(){
  double dist_A = -1;
  double dist_B = -1;
  int dirX = 0 , dirY = 0;
  for(size_t i = 0 ; i < gPhysicalObjects.size() ; i++){
    //A
    PhysicalObject * obj =  gPhysicalObjects[i] ;
    if ( ( dist_A == -1 || getDistance(obj, dirX, dirY) < dist_A ) && obj->getType() == 0
    && isInRange(obj) && obj->isVisible() )
    {
      dist_A = getDistance(obj, _directionX_A, _directionY_A);
      closest_A = obj;
    }
    //B
    if ( ( dist_B == -1 || getDistance(obj, dirX, dirY) < dist_B ) && obj->getType() == 1
    && isInRange(obj) && obj->isVisible() )
    {
      dist_B = getDistance(obj, _directionX_B, _directionY_B);
      closest_B = obj;
    }
  }
  closest_dist_A = dist_A;
  closest_dist_B = dist_B;
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
  //test
  // int dirX,dirY;
  // double dist, angle ;
  // dist = ToroidalDistance(100,900, 900,900, dirX, dirY);
  // angle = getAngleToTarget( 100, 900, 0, 900 + dirX*gAreaWidth , 900 + dirY*gAreaHeight);
  // std:: cout << "(1) " << dist << " " << dirX << " " << dirY << " " << angle << std::endl;
  //
  // dist = ToroidalDistance(100,900, 100,100, dirX, dirY);
  // angle = getAngleToTarget( 100, 900, 0, 100 + dirX*gAreaWidth , 100 + dirY*gAreaHeight);
  // std:: cout << "(2) " << dist << " " << dirX << " " << dirY << " " << angle  << std::endl;
  //
  // dist = ToroidalDistance(100,900, 900,100, dirX, dirY);
  // angle = getAngleToTarget( 100, 900, 0, 900 + dirX*gAreaWidth , 100 + dirY*gAreaHeight);
  // std:: cout << "(3) " << dist << " " << dirX << " " << dirY << " " << angle << std::endl;
  //
  // dist = ToroidalDistance(100,900, 500,500, dirX, dirY);
  // angle = getAngleToTarget( 100, 900, 0, 500 + dirX*gAreaWidth , 500 + dirY*gAreaHeight);
  // std:: cout << "(4) " << dist << " " << dirX << " " << dirY << " " << angle << std::endl;
  //
  // exit(-1);
  // int ldirXA=_directionX_A, ldirYA=_directionY_A , ldirXB=_directionX_B, ldirYB =_directionY_B;
  _wm->_desiredTranslationalValue = DISTANCE_PER_CYCLE;
  setClosests();
  int target = objective();
  if(target == 0)
    goToA();
  else if(target == 1)
    goToB();
  else
    explore();
  updateValue();
  toroidaliter();
  // std::cout <<
  // "Energy A : " << _wm->getEnergyLevel_A() <<
  // "\nEnergyB : " << _wm->getEnergyLevel_B() <<
  // "\nTarget:" << target << " \n";
  // if(target == 0 && closest_dist_A != -1){
  //   std::cout << "\t" << closest_A->getXReal() << " " << closest_A->getYReal() << std::endl;
  //   std:: cout << "\tDirection : " << _directionX_A << " " << _directionY_A << std::endl;
  // }
  // else if(target == 1 && closest_dist_B != -1){
  //   std::cout << "\t" << closest_B->getXReal() << " " << closest_B->getYReal() << std::endl;
  //   std:: cout << "\tDirection : " << _directionX_B << " " << _directionY_B << std::endl;
  //
  // }
  // std::cout << std::endl;
  if(_wm->getEnergyLevel_A() == 0 || _wm->getEnergyLevel_B() == 0 || nbr_iteration == 50000){
    std::cout << "MORT" << nbr_iteration << std::endl;
    std::ofstream fichier;
    fichier.open("resultat_"+std::to_string(ALossPerCycle)+".txt", std::ios::out | std::ios::app);
    fichier << nbr_iteration << std::endl;
    fichier.close();
    exit(0);
  }else{
    nbr_iteration++;
    // std::cout <<
    // "Energy A : " << _wm->getEnergyLevel_A() <<
    // "\nEnergyB : " << _wm->getEnergyLevel_B() <<std::endl;
  }
  // if(nbr_iteration%5000 == 0 )
  //   std::cout << nbr_iteration << std::endl;
  // if( _directionX_A != ldirXA
  //   || _directionY_A != ldirYA
  //   || _directionX_B != ldirXB
  //   || _directionY_B != ldirYB
  // ){
  //   int dirX=0, dirY =0;
  //   int r;
  //   double dist;
  //   std::cout << "ROBOT : " << getPosition().x << " " << getPosition().y << " " << _wm->_agentAbsoluteOrientation << std::endl;
  //   for(size_t i = 0 ; i < gPhysicalObjects.size() ; i++){
  //     if(gPhysicalObjects[i]->isVisible()){
  //       dist = getDistance(gPhysicalObjects[i],dirX,dirY);
  //       std::cout << "(" << gPhysicalObjects[i]->getType()<<") (" << gPhysicalObjects[i]->getXReal() <<", " << gPhysicalObjects[i]->getYReal() <<") "
  //       << dist << " "<< dirX <<" " << dirY<< std::endl;
  //     }
  //   }
  //   std::cout << _directionX_A << " " << _directionY_A << " " << _directionX_B << " " << _directionY_B << std::endl;
  //   std::cin >> r ;
  // }

}

void IARController::updateValue(){
  _wm->substractEnergy_A(ALossPerCycle);
  _wm->substractEnergy_B(BLossPerCycle);
}

void IARController::toroidaliter(){
  int x, y ;
  _wm->getWorld()->getRobot(0)->getCoord(x,y);
  if(getPosition().x < 0){
    _wm->getWorld()->getRobot(0)->setCoordReal(gAreaWidth-gMaxTranslationalSpeed, getPosition().y);
  }
  else if( getPosition().x >= gAreaWidth ){
    _wm->getWorld()->getRobot(0)->setCoordReal(gMaxTranslationalSpeed, getPosition().y);
  }
  if(getPosition().y < 0){
    _wm->getWorld()->getRobot(0)->setCoordReal( getPosition().x , gAreaHeight - gMaxTranslationalSpeed);
  }else if( getPosition().y >= gAreaHeight ){
    _wm->getWorld()->getRobot(0)->setCoordReal( getPosition().x, gMaxTranslationalSpeed);
  }
}
