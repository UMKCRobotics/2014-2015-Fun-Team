#include <RedBot.h>
#include <RedBotSoftwareSerial.h>

#include <Cardinal.h>
#include <Navigation.h>
#include <FunMazeSolver.h>
#include <Notification.h>
#include <ConfigManager.h>
#include <RobotState.h>



setup() {
  Configuration* config = ConfigurationFactory::createConfiguration();
  
  Navigation nav;
  
  if(config->phase == 1)
    nav = phase1(config);
  
  while(button is not pr essed stopped)
    //do nothing til go
    
  config = ConfigurationFactory::createConfiguration();
  
  if (config->phase == 2)
    phase2(config, nav);
  
  
}


loop()
//nothing


Navigation phase1(config)
{
   Navigation nav(config);
   RobotState state(config);
   Cardinal nextCard;
   FunMotorController motor;
   Notifier note;
  
   bool finalNode = false;
 
   while( not over time) {
      //Compute openings from sensors
      nextCard = FunMazeSolver::doRightHand(state, FunWorldSensor::computeOpenings(state));
      if (nextCard != right or straight) 
      {
        motors.turnLeft();
        switch(state.currentDirection)
         {
            case NORTH:
            {
              state.currentDirection = WEST;
              break;
            }
            case WEST:
            {
              state.currentDirection = SOUTH;
              break;
            }
            case SOUTH:
            {
              state.currentDirection = EAST;
              break;
            }
            case EAST:
            {
              state.currentDirection = NORTH;
              break;
            }
          }
        nextCard = FunMazeSolver::doRightHand(state, FunWorldSensor::computeOpenings(state))
      
        if(nextCard == NULL) 
        {
          motors.turnLeft();
          switch(state.currentDirection)
          {
            case NORTH:
            {
              state.currentDirection = WEST;
              break;
            }
            case WEST:
            {
              state.currentDirection = SOUTH;
              break;
            }
            case SOUTH:
            {
              state.currentDirection = EAST;
              break;
            }
            case EAST:
            {
              state.currentDirection = NORTH;
              break;
            }
          }
          nextCard == state.currentDiection;
          nav.updateMap(state, nextCard);
          state = motors.move(state, nextCard);
        }
        else 
        {
          nextCard = state.currentDirection;
          nav.updateMap(state, nextCard);
          state = motors.move(state, nextCard);
        }  
      }
      else
      {
        nav.updateMap(state, nextCard);
        state = motors.move(state, nextCard);
      }
    
      if(nav.inFinalNode(state) && !visitedFinalNode) 
      {
        visitedFinalNode = true;
        note.mazeComplete;
        return nav;
      }
     }
}


phase2(Configuration* config, Navigation nav) {
  
  Robotstate state(config)
  Cardinal nextCard;
  FunMotorController motor;
  Notifier note
  
  while(!nav.inFinalNode(state)) {
    nextCard = nav.getCardinalToNextNode(state)
    state = move(state, nextCard);
  }
  
  note.mazeComplete
  
}
