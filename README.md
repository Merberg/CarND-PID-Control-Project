# Overview

This repository contains the code needed to complete the PID project for Udacity's Self-Driving Car Nanodegree.  When run, the executable created in this project feeds the steering angle to a simulated vehicle driving in the [Term 2 Simulator](https://github.com/udacity/self-driving-car-sim/releases).  PID control is used to adjust the steering value based on the Cross Track Error.

---

## Dependencies

* cmake >= 3.5
* make >= 4.1(mac, linux), 3.81(Windows)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
* [Udacity Term 2 Simulator](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.


## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

---

[iKd]: ./data/KdTuning.jpg "Kd Tuning"
[iKdFine]: ./data/KdTuningFine.jpg "Kd Fine Tuning"
[iKp]: ./data/KpTuning.jpg "Kp Tuning"
[iKpFine]: ./data/KpTuningFine.jpg "Kp Fine Tuning"
[iFinal]: ./data/Final.jpg "Final"

## PID Tuning Information

Three command line parameters can be used by the pid executable as the coefficients (if enabled).  Initially I attempted to use Twiddle/Coordinate Ascent in a runtime fashion, but abandoned that approach due to the dynamic nature of the simulation track (see [previous git commit](https://github.com/Merberg/CarND-PID-Control-Project/tree/a8063e40dc301fa688fc396c0c9475dcf6e0c090) for source).  I then turned to a common tuning method taught in numerous courses.  It starts by tuning D (the future trend), then P (the current response), and finally I (past influence).  An excellent description is fully captured in [PID Without a PhD](http://www.wescottdesign.com/articles/pid/pidWithoutAPhd.pdf).

### Tuning Steps

1. Set all gains to zero.
2. Set Ki to a small value (-0.1) such that there are minimumal or slow oscillations.
2. Jump Kd to 100 times Ki (-10.0).
3. Back off Kd by factors of 2-4 to correct oscillations. The selected value with least amount of oscillations while still maintaining the course is Kd = -1.0;

![iKd]

![iKdFine]

4. Drop Kp to 1% of Kd and increase by factors of 8-10 until oscillations or excessive overshoot appears.  1% of Kd was too sluggish to drive around the track while a Kd of -0.8 oscillated too wildly to stay within the lanes.

![iKp]

5. Fine tune Kp by a factor of 2-4.  A Kp = -0.14 had a smoother performance, but -0.16 maintained the lanes slightly better.

![iKpFine]

6. Set Ki to about 1% of Kp.  This value of -0.0014 was large enough to notice increased oscillations on the straight sections.
7. Decrease Ki by a factor of 2-4.  Tuning the Ki term was more focused on keeping the car within the lanes on the large turns.  A slightly positive, Ki = 0.000005, helps.
8. STOP TUNING!!!

```
Kp = -0.16;
Ki = 0.000005;
Kd = -1.0;
```
![iFinal]



