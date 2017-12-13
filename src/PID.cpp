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
      TUNING_CTE_TRIGGER(4),
      TUNING_CTE_THRESHOLD(0.00001),
      counter(0),
      cte_best(10),
      cte_prev(10)
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
  double cte_abs = fabs(cte);

  //Check first for done
  if (cte_abs <= TUNING_CTE_THRESHOLD) {
    cout << endl;
    cout << "Tuning Complete P:" << Ks[idxP] << " I:" << Ks[idxI] << " D:"
         << Ks[idxD] << endl;
    isTuning = false;
    tuningState = Complete;
    return;
  }
  //Otherwise run the twiddle states
  counter = (cte_abs > cte_prev) ? counter + 1 : 0;
  cte_prev = cte_abs;
  if (counter > TUNING_CTE_TRIGGER){
    if (cte_abs < cte_best) {
      TuneEnterAddBestErr(cte_abs);
    } else if (tuningState == Add) {
      TuneEnterSubtract();
    } else {
      TuneEnterAdd();
    }
    counter = 0;
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
  tuningState = Add;
}

void PID::TuneEnterSubtract()
{
  //Transition to Subtract State
  cout << endl;
  cout << idxTuning << " enter -: " << dKs[idxTuning] << endl;
  Ks[idxTuning] -= 2 * dKs[idxTuning];
  tuningState = Subtract;
}
