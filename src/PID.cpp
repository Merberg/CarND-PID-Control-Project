#include "PID.h"
#include <iostream>
#include <math.h>

using namespace std;

/*
 * TODO: Complete the PID class.
 */

PID::PID(double kp, double ki, double kd)
    : p_error(0.0),
      i_error(0.0),
      d_error(0.0),
      idxP(0),
      idxI(2),
      idxD(1),
      isTuning(true),
      tuningState(Add),
      idxTuning(0),
      N_TUNING_COEFFS(2),
      TUNING_CTE_TRIGGER(3.0),
      TUNING_CTE_THRESHOLD(0.00001),
      TUNING_SETTLE_COUNTS(5),
      tuningCounter(0),
      cte_best(TUNING_CTE_TRIGGER)
{
  Ks[idxP] = kp;
  Ks[idxI] = ki;
  Ks[idxD] = kd;
  dKs[idxP] = -1.0;
  dKs[idxI] = 1.0;
  dKs[idxD] = -1.0;
}

PID::~PID()
{
}

void PID::UpdateError(double cte)
{
  d_error = cte - p_error;  //p_error = previous cte
  p_error = cte;
  i_error += cte;

  if (isTuning) {
    Tune(cte);
  }
}

double PID::TotalError()
{
  return Ks[idxP] * p_error + Ks[idxI] * i_error + Ks[idxD] * d_error;
}

void PID::Tune(double cte)
{
  //Check first for done
  if (fabs(cte) <= TUNING_CTE_THRESHOLD) {
    cout << endl;
    cout << "Tuning Complete P:" << Ks[idxP] << " I:" << Ks[idxI] << " D:"
         << Ks[idxD] << endl;
    isTuning = false;
    tuningState = Complete;
    return;
  }
  //Otherwise run the twiddle states
  if ((tuningCounter > TUNING_SETTLE_COUNTS)
      || (fabs(cte) > TUNING_CTE_TRIGGER)) {
    if (fabs(cte) < cte_best) {
      TuneEnterAddBestErr(cte);
    } else if (tuningState == Add) {
      TuneEnterSubtract();
    } else {
      TuneEnterAdd();
    }
  } else {
    tuningCounter++;
  }
}

void PID::TuneEnterAddBestErr(double cte)
{
  //Transition to the Add State with a better cte, increasing the delta
  cout << endl;
  cout << idxTuning << " enter + best: " << dKs[idxTuning] << endl;
  cte_best = cte;
  dKs[idxTuning] *= 1.1;
  idxTuning = (idxTuning + 1) % N_TUNING_COEFFS;
  Ks[idxTuning] += dKs[idxTuning];
  tuningCounter = 0;
  tuningState = Add;
}

void PID::TuneEnterAdd()
{
  //Transition to Add State, decreasing the delta
  cout << endl;
  cout << idxTuning << " enter +: " << dKs[idxTuning] << endl;
  Ks[idxTuning] += dKs[idxTuning];
  dKs[idxTuning] *= 0.9;
  idxTuning = (idxTuning + 1) % N_TUNING_COEFFS;
  Ks[idxTuning] += dKs[idxTuning];
  tuningCounter = 0;
  tuningState = Add;
}

void PID::TuneEnterSubtract()
{
  //Transition to Subtract State
  cout << endl;
  cout << idxTuning << " enter -: " << dKs[idxTuning] << endl;
  Ks[idxTuning] -= 2 * dKs[idxTuning];
  tuningCounter = 0;
  tuningState = Subtract;
}
