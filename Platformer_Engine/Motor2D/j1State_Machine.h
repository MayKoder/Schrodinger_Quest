#ifndef __StateMachine_H__
#define __StateMachine_H__

#include "p2Defs.h"
#include "j1Player.h"
#include "j1Module.h"

void CheckInputs(int& inputsouts, int& speed_y, state actual, inputin& input_in, inputout input_out[3]);
Animation* ExecuteState(iPoint& speed, state actual, bool reset_animation);
bool CheckState(int &inputsouts, state& actual, inputin& input_in, inputout input_out[3]);


#endif