### Smartwatch Module 

The smartwatch module takes as input the data sent by the smartwatch, filtered by the Complementary Filter Node, and gives as output the corresponding RPY (roll-pitch-yaw) data.


## Implementation

### Prerequisites

Hardware prerequisites:

1. LG G Watch R W110

1. LG G6 H870

Software prerequisites:

1. ROS kinetic, to download it follow [this guide](http://wiki.ros.org/kinetic/Installation/Ubuntu).

1. Imu Stream, a set of Android applications (mobile and wear) to stream IMU data from the smartwatch to an MQTT broker. For more feature follow [this guide](http://github.com/EmaroLab/imu_stream).

1. Mosquitto on Ubuntu, to download it follow [this guide](https://www.digitalocean.com/community/tutorials/how-to-install-and-secure-the-mosquitto-mqtt-messaging-broker-on-ubuntu-16-04).


### How to run the project
1. Clone this repository in your workspace through the command 
	```bash
    git clone
    ```
1. Install the timed roslaunch package through the command, is needed for the timing of the complementary filter (It is already incuded if you clone all the project)
	```bash
	sudo apt install ros-kinetic-timed-roslaunch
	```
1. Compile your workspace
	```bash
	catkin_make
	```

1. Check the Mosquitto broker status, if the broker is already active skip step 6.
    ```bash
    sudo service mosquitto status
    ```
1. Start the Mosquitto broker.
    ```bash
    mosquitto
    ```
1. To run (separate from the rest of the project):
    ```bash
    roslaunch smart_watch smartwatch.launch
    ```

## Results
The smartwatch was fully tested and we can conclude that the Husqvarna Automower is totally controllable through the usage of a smartwatch.

## Recommendations
During the test phase some issues raised, one of them is the fact that the connection between smartwatch, smartphone and computer introduce a considerable delay that retard the movement of the robot with respect to the smartwatch orientation.

## Authors
* Nicola De Carli: s4198668@studenti.unige.it
* Angelica Ginnante: angelica.ginnante@gmail.com

