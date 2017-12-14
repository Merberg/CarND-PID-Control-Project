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
[iKpTuningRough]: ./data/KpTuningRough.jpg" "Kp Tuning Rough"

## PID Tuning Information

Three command line parameters can be provided to the pid executable to be used as the coefficients.  Initially I attempted to use Twiddle/Coordinate Ascent in a runtime fashion, but abandoned that approach due to the dynamic nature of the simulation track (see [previous git commit](https://github.com/Merberg/CarND-PID-Control-Project/tree/a8063e40dc301fa688fc396c0c9475dcf6e0c090) for source).  I then turned to this common tuning method taught in numerous courses and fully captured in [PID Without a PhD](http://www.wescottdesign.com/articles/pid/pidWithoutAPhd.pdf):
1. Set all gains to zero.
2. Set Ki to a small value (-0.1) such that there are minimumal or slow oscillations.
2. Jump Kd to 100 times Ki (-10.0).
3. Back off Kd by factors of 2-4 to correct oscillations.
![iKd]
4. Drop Kp to 1% of Kd and increase by factors of 8-10 until oscillations or excessive overshoot appears. 
![iKpTuningRough]
*Note: 1% of Kd was too sluggish to drive around the track*
5. Fine tune Kp by a factor of 2-4.  In order to keep the car on the track, additional tuning of Kd was done with Kp.
Set Ki to about 1% of Kp.
Increase Ki until oscillations start.
Decrease Ki by a factor of 2-4.



