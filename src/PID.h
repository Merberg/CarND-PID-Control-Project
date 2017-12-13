#ifndef PID_H
#define PID_H

class PID {
 protected:

  /*
   * Errors
   */
  double p_error;
  double i_error;
  double d_error;

  /*
   * Coefficients
   */
  static const int N_COEFFICIENTS = 3;
  double Ks[N_COEFFICIENTS];
  const int idxP;
  const int idxI;
  const int idxD;

  /*
   * Tuning members
   */
  enum TuningStates_s {
    Add,
    Subtract,
    Complete
  };
  bool isTuning;
  TuningStates_s tuningState;
  int idxTuning;
  const int N_TUNING_COEFFS;
  const int TUNING_CTE_TRIGGER;
  const double TUNING_CTE_THRESHOLD;
  int counter;
  double cte_best;
  double cte_prev;
  double dKs[N_COEFFICIENTS];

  /*
   * Tune the PID coefficients using Coordinate Ascent/Twiddle
   */
  void Tune(double cte);
  void TuneEnterAddBestErr(double cte);
  void TuneEnterAdd();
  void TuneEnterSubtract();

 public:
  /*
   * Constructor
   */
  PID(double kp, double ki, double kd);

  /*
   * Destructor.
   */
  virtual ~PID();

  /*
   * Update the PID error variables given cross track error.
   */
  void UpdateError(double cte);

  /*
   * Calculate the total PID error.
   */
  double TotalError();
};

#endif /* PID_H */
