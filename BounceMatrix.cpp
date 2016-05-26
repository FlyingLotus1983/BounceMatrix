
#include "Arduino.h"
#include "BounceMatrix.h"

BounceMatrix::BounceMatrix(unsigned long interval_millis)
{
	interval(interval_millis);
	previous_millis = millis();
	state = 0;
}

void BounceMatrix::write(int new_state)
	{
		this->state = new_state;
	}

void BounceMatrix::interval(unsigned long interval_millis)
{
  this->interval_millis = interval_millis;
  this->rebounce_millis = 0;
}

void BounceMatrix::rebounce(unsigned long interval)
{
	this->rebounce_millis = interval;
}

int BounceMatrix::update(bool newState)
{
	if ( debounce(newState) ) 
	{
		rebounce(0);
		return stateChanged = 1;
	}
	// We need to rebounce, so simulate a state change
	if ( rebounce_millis && (millis() - previous_millis >= rebounce_millis) ) 
	{
		previous_millis = millis();
		rebounce(0);
		return stateChanged = 1;
	}
	return stateChanged = 0;
}

unsigned long BounceMatrix::duration()
{
  return millis() - previous_millis;
}

int BounceMatrix::read()
{
	return (int)state;
}

// Protected: debounces the pin
int BounceMatrix::debounce(bool newState) 
{	
	if (state != newState ) 
	{
		if (millis() - previous_millis >= interval_millis) 
		{
  		previous_millis = millis();
  		state = newState;
  		return 1;
		}
  }
  return 0;
}

// The risingEdge method is true for one scan after the de-bounced input goes from off-to-on.
bool  BounceMatrix::risingEdge() 
{
  if (stateChanged && state)
  {
    stateChanged = 0;
    return true;
  }
  else
  {
    return false;
  }
}

// The fallingEdge  method it true for one scan after the de-bounced input goes from on-to-off. 
bool  BounceMatrix::fallingEdge() 
{ 
  if (stateChanged && !state)
  {
    stateChanged = 0;
    return true;
  }
  else
  {
    return false;
  }
}

