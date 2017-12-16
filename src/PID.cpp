#include "PID.h"
#include <iostream>
#include <math.h>

using namespace std;

/*
 * PID class.
 */

PID::PID(double kp, double ki, double kd)
    : p_error(0.0),
      i_error(0.0),
      d_error(0.0),
      Kp(kp),
      Ki(ki),
      Kd(kd)
{
  //Intentionally left blank
}

PID::~PID()
{
}

void PID::UpdateError(double cte)
{
  d_error = cte - p_error;  //p_error = previous cte
  p_error = cte;
  i_error += cte;
}

double PID::TotalError()
{
  return Kp * p_error + Ki * i_error + Kd * d_error;
}

