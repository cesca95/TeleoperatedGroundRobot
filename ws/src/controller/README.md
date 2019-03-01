# Mobile Robot Teleoperation

This project allows to read the orientation of the right arm estimated by three different sensors, a smartwatch, a kinect and a leap motion. The controller collects these data and evaluates the linear and the angular velocity to be sent to the robot in order to meve it. 

## The System’s Architecture

The hardware is composed by a smartwatch, a kinect, a leap motion and the robot we want to move. The modules are wrote in cpp or in python.

### Description of the Modules

The architecture is composed by three sensors that get information regarding the arm and interface to the PC using the respective drivers. Since the controller receives RPY angles that are easier to interpret than quaternions. The adapter nodes receive the orientation data from the respective sensors and in different ways convert them into RPY data and then send everything to the controller. The controller converts RPY data into linear and angular velocities, makes the average and sends the actual velocities to the robot.  

###Smartwatch Module 

The smartwatch module takes as input the data sent by the smartwatch, filtered by the Complementary Filter Node, and gives as output the corresponding RPY (roll-pitch-yaw) data.

###Controller Module 

The controller module takes as input the RPY data sent by the three adapter of the sensors and converts them into linear and angular velocities. Then it makes the average between the velocities available and gives as output the actual velocity that the robot has to take.

###GAZEBO

During the phase of project testing the final velocity is sent to the GAZEBO simulation, but this velocity can also be sent to the real robot in order to move it.

## Implementation

### Prerequisites

Hardware prerequisites:

1.LG G Watch R W110

1.LG G6 H870

1.Husqvarna Automower

Software prerequisites:

1.ROS kinetic, to download it follow [this guide](http://wiki.ros.org/kinetic/Installation/Ubuntu).

1.Mosquitto on Ubuntu, to download it follow [this guide](https://www.digitalocean.com/community/tutorials/how-to-install-and-secure-the-mosquitto-mqtt-messaging-broker-on-ubuntu-16-04).

1.GAZEBO robotic simulator for ROS, to download it follow [this guide](http://gazebosim.org/tutorials?tut=ros_installing).

### How to run the project
It describes step by step how to download and run the project on a new computer.

## Results
It presents the result using (images or videos) of the working system, in (real or simulation).

## Recommendations
The Recommendations follow naturally from the conclusions. They describe: the assumptions made while building the system (and/or) the limitations of the working system. Therefore, presenting possible ideas that could overcome the limitations or assumptions. 

## Authors
* FirstName LastName: email@email.com
* FirstName LastName: email@email.com
* FirstName LastName: email@email.com

# Useful GitHub readme syntax

## To make bullet points

* Do this
	* Do this

## To make hyper-link

For example, making a link to [ROS tutorials](http://wiki.ros.org/ROS/Tutorials)

## To show, how to execute some commands in the terminal

    ```
    sudo apt install ros-kinetic-opencv3 #(should be already installed with previous point)
    sudo apt install ros-kinetic-opencv-apps
    ```

## To exphasize about a particular command

For example: Please do a ```catkin_make ```, once you have modified your code. 

## To add image(s) or video(s)

