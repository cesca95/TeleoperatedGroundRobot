# hrp_teleoperation

## Objective of the Project
It describes what the project wants to achieve and defines terminologies. Presents the hardware or tools used in the project.

## The System’s Architecture

### Overall Architecture
It describes what the project wants to achieve and defines the key terminologies of this project. Presents the hardware or tools used in the project.

### Description of the Modules
#### SLAM algorithm implementation
This module is implemented on the machine running linux by exploiting an existing package available on the ros documentation, a ROS wrapper of RTAB-Map(Real-Time Appearance-Based Mapping). This package can be used to generate a 3D point clouds of the environment as was done in this project. 
For more information visit the following links:
[RTAB-Map](http://introlab.github.io/rtabmap/)
[Ros Wiki](http://wiki.ros.org/rtabmap_ros)
[GitHub Repo](https://github.com/introlab/rtabmap_ros) 		<optional>

As the documentation shows, RTAB-Map is composed of differents nodes but this projects will only require the use of the "rtabmap" one.

##### Inputs
The inputs are the images taken by the kinect v2 in RGB-D format, which is a combination of a RGB image and its corresponding depth image.
##### Internal working
RTAB-Map takes the RGB-D images and publish it as ros messages under different topics as shown in the documentation [here](http://wiki.ros.org/rtabmap_ros#rtabmap). 
##### Outputs
The ouputs are the messages published on the different ros topics, in particular we are interested on the "/rtabmap/mapData" topic on which is published the 3d point cloud map of the enviroment. The map can be visualized in Rviz, which will be launched automatically with the required settings to visualize the map, in order to make a pre check before starting to send the data stream to unity.


#### Unity visualization of a 3d point cloud map
This modules is implemented on the machine running windows and provides a platform on which visualize the point cloud map put together by the SLAM algorithm module
#### Oculus 

##### Inputs


##### Internal working

  
##### Outputs



## Implementation

### Prerequisites
It describes all hardwares and softwares that are required for running the system.

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

* To embbed an image

<p align="center"> 
<img src="https://github.com/yushakareem/test-delete/blob/master/light-bulb-2-256.gif">
</p>

* To link a [video](https://youtu.be/-yOZEiHLuVU)




#http://wiki.ros.org/rtabmap_ros

In order to install and launch rtabmap:

sudo apt-get install ros-kinetic-rtabmap-ros

Modify in /opt/ros/kinetic/share/rtabmap_ros/launch the file rtabmap.launch
at row 21 set default = false, at row 22 set deafault = true in order to open the pointcloud map with rviz.

Launch rtabmap:
roscore

roslaunch freenect_launch freenect.launch depth_registration:=true

roslaunch rtabmap_ros rtabmap.launch rtabmap_args:="--delete_db_on_start"


pointcloud topic:  /rtabmap/mapData     type:  rtabmap_ros/MapData


run the websocket with: roslaunch rosbridge_server rosbridge_websocket.launch
