# EQL

## Espresso Query Language

### Description

A very small query language with very specific keywords named as Commands (CMD's),
intented to execute user defined actions on the robot. it abstracts the tedious work of implementing repetitive robot behaviors such as movement from different points, basic actions...etc.

### Syntax

```c

Move X:int Y:int  // basic movement

Rotate Alpha:int  // perform robot rotation

Pick              // execute the Pick sequence

Capture           // execute the Capture sequence for object detection

// Example
Move 30 54
Rotate 90
Move 50
Rotate 45
Capture
Pick
Rotate -45
Move 100 230
...
```

### Use Cases

- Sending commands over TCP/UDP:

  - very lightweight, a single command is only 72 bytes.
  - avoid the "Iterate -> Compile -> Run" hell cycle.
  - perform those actions on the fly without turning off the robot.

- Simulate CMD's beforehand:

  - Abitily to simulate those actions before excuting it.
  - Simple Visual Simulation of the robot movement for example.

- Everybody can contribute:

  - How many people know how to code in your team?
  - Extremely simple syntax.
  - Idiot-proof language.
