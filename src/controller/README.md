# Mobile Robot Teleoperation

This project allows to read the orientation of the right arm estimated by three different sensors, a smartwatch, a kinect and a leap motion. The controller collects these data and evaluates the linear and the angular velocity to be sent to the robot in order to move it. 

## The System’s Architecture

The hardware is composed by a smartwatch, a kinect, a leap motion and the robot we want to move. The modules are wrote in cpp or in python.

### Description of the Modules

The architecture is composed by three sensors that get information regarding the arm and interface to the PC using the respective drivers. The adapter nodes receive the orientation data from the respective sensors and in different ways convert them into RPY data and then send everything to the controller. The controller receives RPY angles which are easier to interpret than quaternions and converts them into linear and angular velocities, makes the average and sends the actual velocities to the robot.  

### Smartwatch Module 

The smartwatch module takes as input the data sent by the smartwatch, filtered by the Complementary Filter Node, and gives as output the corresponding RPY (roll-pitch-yaw) data.

### Controller Module 

The controller module takes as input the RPY data sent by the three adapter of the sensors and converts them into linear and angular velocities. Then it computes the weighted average between the velocities available and gives as output the actual velocity that the robot has to take.

### Gazebo Simulation

During the test phase the simulator listen at the topic /cmd_vel and a simulated hrp_automower moves in Gazebo according to the message received.

## Implementation

### Prerequisites

Hardware prerequisites:

1. LG G Watch R W110

1. LG G6 H870

1. Husqvarna Automower

Software prerequisites:

1. ROS kinetic, to download it follow [this guide](http://wiki.ros.org/kinetic/Installation/Ubuntu).

1. Imu Stream, a set of Android applications (mobile and wear) to stream IMU data from the smartwatch to an MQTT broker. For more feature follow [this guide](http://github.com/EmaroLab/imu_stream).

1. Mosquitto on Ubuntu, to download it follow [this guide](https://www.digitalocean.com/community/tutorials/how-to-install-and-secure-the-mosquitto-mqtt-messaging-broker-on-ubuntu-16-04).

1. GAZEBO robotic simulator for ROS, to download it follow [this guide](http://gazebosim.org/tutorials?tut=ros_installing). 

### How to run the project
1. Clone this repository in your workspace through the command 
	```bash
    git clone
    ```
1. (ONLY IF YOU WANT TO SIMULATE ON GAZEBO)For the simulation of the Husqvarna Automower on GAZEBO install all the dependencies (for more info about this part look at [this guide](https://github.com/HusqvarnaResearch/hrp/blob/master/Startup%20Guide%20HRP.pdf) 
	```bash
	sudo apt-get install ros-kinetic-gazebo-ros-control
	sudo apt-get install ros-kinetic-joint-state-controller
	sudo apt-get install ros-kinetic-hector-gazebo-plugins
	sudo apt-get install ros-kinetic-hector-gazebo
	sudo apt-get install python-pygame
	```
1. Install the timed roslaunch package through the command, is needed for the timing of the complementary filter
	```bash
	sudo apt install ros-kinetic-timed-roslaunch
	```
1. Compile your workspace
	```bash
	catkin_make
	```
1. Setup the model path
	```bash
	export GAZEBO_MODEL_PATH=[your path]/src/haro/am_gazebo/models:$GAZEBO_MODEL_PATH
	```


1. Check the Mosquitto broker status, if the broker is already active skip step 6.
    ```bash
    sudo service mosquitto status
    ```
1. Start the Mosquitto broker.
    ```bash
    mosquitto
    ```
1. In another terminal tab launch the controller and all the other nodes (inside the launch file you cold comment components not needed, for example those
 for the simulation)
	```bash
    roslaunch controller controller.launch
    ```
1. In order to start the simulation on gazebo
	```bash
    roslaunch am_gazebo am_gazebo_hrp.launch gui:=true
    ```
## Results
The smartwatch was fully tested and we can conclude that the Husqvarna Automower is totally controllable through the usage of a smartwatch.

## Recommendations
During the test phase some issues raised, one of them is the fact that the connection between smartwatch, smartphone and computer introduce a considerable delay that retard the movement of the robot with respect to the smartwatch orientation.

## Authors
* Noel Alejandro Avila Campos: nono.nonex@gmail.com
* Nicola De Carli: s4198668@studenti.unige.it
* Angelica Ginnante: angelica.ginnante@gmail.com

