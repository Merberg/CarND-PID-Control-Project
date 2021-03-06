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
  double Kp;
  double Ki;
  double Kd;

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
