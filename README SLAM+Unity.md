# hrp_teleoperation

## Objective of the Project
It describes what the project wants to achieve and defines terminologies. Presents the hardware or tools used in the project.

## The System’s Architecture

### Overall Architecture
It describes what the project wants to achieve and defines the key terminologies of this project. Presents the hardware or tools used in the project.

### Description of the Modules
#### SLAM algorithm mapping
This module is implemented on the machine running Linux by exploiting an existing package available on the ROS documentation, a ROS wrapper of RTAB-Map(Real-Time Appearance-Based Mapping). This package can be used to generate a 3D point clouds of the environment as was done in this project. 
For more information visit the following links:

[RTAB-Map](http://introlab.github.io/rtabmap)

[ROS Wiki](http://wiki.ros.org/rtabmap_ros)

[GitHub Repo](https://github.com/introlab/rtabmap_ros)

As the documentation shows, RTAB-Map is composed of differents nodes but this projects will only require the use of the "rtabmap" one.
In order for the kinect 2 v2 to work as needed it is necessary to install the [libfreenect2](https://github.com/OpenKinect/libfreenect2) and the [IAI Kinect2](https://github.com/code-iai/iai_kinect2) drivers.

To establish the connection between the two machines it was chosen [rosbridge](http://wiki.ros.org/rosbridge_suite) which provides a JSON interface to ROS, allowing any client to send JSON to publish or subscribe to ROS topics, call ROS services, and more.


##### Inputs
The inputs are the images taken by the kinect 2 v2 in RGB-D format, which is a combination of a RGB image and its corresponding depth image.
##### Internal working
RTAB-Map takes the RGB-D images and publishes them as ROS messages under different topics as shown in the documentation [here](http://wiki.ros.org/rtabmap_ros#rtabmap). 
##### Outputs
The ouputs are the messages published on the different ROS topics, in particular we are interested on the ```/rtabmap/mapData``` topic on which is published the 3D point cloud map of the enviroment. The map can be visualized in Rviz, which will be launched automatically with the required settings to visualize the map, in order to make a pre check before starting to send the data stream to Unity via a websocket.


#### Unity visualization of a 3D point cloud map
This modules is implemented on the machine running windows and provides a platform on which visualize the point cloud map put together by the SLAM mapping module. Unity will visualize the map and provide the connection with the oculus with all the relative scripts to link the game camera with the movement of the oculus.

##### Inputs 
Unity receives the ROS messages of the ```/rtabmap/mapData``` topic via the websocket.

##### Internal working
The data stream is processed by a script tuned to convert the ROS message received in an image visualizable on the Unity scene.
  
##### Outputs
The outputs will be the 3D point cloud map visualized on the Unity scene which will also be visualized by the connected oculus.


## Implementation

### Prerequisites
It describes all hardwares and softwares that are required for running the system.
#### LINUX SIDE 
* Microsoft XBOX ONE KINECT 2 V2 with relatives connection cable
* Ubuntu 16.04 LTS
* ROS Kinetic
* RTAB-Map package
* libfreenect2 drivers
* IAI Kinect2 drivers
* Rosbridge_suite

#### WINDOWS SIDE
* Oculus rift Developer Kit 2
* Unity 2018.
* Oculus Runtime v0.8.0.0
* Oculus APP
* Unity project files


### How to run the project
It describes step by step how to download and run the project on a new computer.

#### LINUX SIDE 
If you don't already have it, install ROS kinetic as shown in the [tutorial](http://wiki.ros.org/kinetic/Installation/Ubuntu)

Install rtabmap using the following command:
```
sudo apt-get install ros-kinetic-rtabmap-ros
```
Modify in ```/opt/ros/kinetic/share/rtabmap_ros/launch``` the file ```rgbd_mapping_kinect2.launch```, at row 25 set ```default = "true"```, at row 26 set ```default = "false"``` in order to open the pointcloud map with Rviz. 

Modify in ```/opt/ros/kinetic/share/rtabmap_ros/launch/config``` the file ```rgbd.rviz```, at row 76 substitute ```/voxel_cloud``` with ```/rtabmap/cloud_map``` in order to visualize the correct topic from the beginning.

Note: remember to open the files as sudo in order to being able to modify and save them.


In order to install freenect2 libraries follow the README's instructions [here](https://github.com/OpenKinect/libfreenect2)

In order to install IAI Kinect2 libraries follow the README's instructions [here](https://github.com/code-iai/iai_kinect2)

In order to install the rosbridge_suite use the command below:
```
sudo apt-get install ros-kinetic-rosbridge-suite 
```


Now, after having plugged in your kinect, you're ready to launch RTAB-Map. Open a terminal and launch ```ROSCORE```

In a new terminal type the command to initialize the RGB and depth sensors: 
```
roslaunch kinect2_bridge kinect2_bridge.launch publish_tf:=true
```


In a third terminal type the command to start the mapping mode:
```
roslaunch rtabmap_ros rgbd_mapping_kinect2.launch resolution:=qhd
```


The last thing to do is to set up the websocket necessary to send the data stream to unity. Please rememeber that in order for the websocket to successfully connect the two machines they must be connected to the same network.

To launch the websocket run in a new terminal:
``` roslaunch rosbridge_server rosbridge_websocket.launch ```


#### WINDOWS SIDE
Start by downloading the repository with the unity code [here](github unity repo link). Plug the oculus in the computerand then open the project. When the websocket on the Linux machine is up and running click on play.
## Results
It presents the result using (images or videos) of the working system, in (real or simulation).

## Recommendations
The Recommendations follow naturally from the conclusions. They describe: the assumptions made while building the system (and/or) the limitations of the working system. Therefore, presenting possible ideas that could overcome the limitations or assumptions. 

## Authors
* Enrico Casagrande: erri.casagrande@gmail.com
* Alberto Ghiotto: alberto.ghiotto@hotmail.it

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

sudo apt-get install ros-kinetic-libfreenect

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

Kinect v2

roslaunch kinect2_bridge kinect2_bridge.launch publish_tf:=true

