# Inverted-Pendulum
Arduino hobby project


The project consists of salvaging and reverse engineering a linear carriage and rotary encoder from an inkjet printer 
(HP in this case) and using them to build an inverted pendulum. 

[Linked video](https://gfycat.com/gifs/detail/VigilantSilentAnemoneshrimp) Shows current prototype moving the carriage to 
randomly chosen positions
using the program in folder random_position.

The project is currently in the state that I left it over a year ago. I did not use git at the time so first thing to do is clean
up the project structure and the project files. Right now the project has multiple detached program code files that have duplicate
code. The goal before adding new functionality is to split the motor driver and encoder functions into separate classes.

# Achieved Goals

Two working optical encoder units, one linear and second rotational

Motor driver using an H-bridge

Driving motor using feedback from linear encoder reading

# To do

Mechanical design of mounting pendulum arm and encoder to the carriage

Design of control system for inverted pendulum system, possibly using Simulink if needed



