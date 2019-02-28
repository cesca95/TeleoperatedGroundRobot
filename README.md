# hrp_teleoperation

## Objective of the Project
The objective of this project is to create a 3D pointcloud map from the images acquired by a Microsoft Kinect in a ROS environment on Linux, to transmit it to a Windows based Unity project which will tweak and improve the map in order to make it more user-friendly before sending it to the Oculus visor weared by the user.
The Kinect could be even mounted on a moving robot in order to create a real-time dynamic map of its surrounding.

## The System’s Architecture
The architecture implementation is conceptually quite trivial. As represented in the figure below, it can be
seen how the two principal modules share data with a simple websocket. In addition to them
there also is a Oculus VR device used for the final visualization.
<p align="center"> 
<img src="https://github.com/EmaroLab/hrp_teleoperation/blob/master/Architecture.gif">
</p>


### Description of the Modules
#### SLAM approach
This module is implemented on the machine running Linux by exploiting an existing package available on the ROS documentation, a ROS wrapper of RTAB-Map(Real-Time Appearance-Based Mapping). This package can be used to generate a 3D point clouds of the environment as was done in this project. 
For more information visit the following links:

[RTAB-Map](http://introlab.github.io/rtabmap)

[ROS Wiki](http://wiki.ros.org/rtabmap_ros)

[GitHub Repo](https://github.com/introlab/rtabmap_ros)

As the documentation shows, RTAB-Map is composed of different nodes but this project will only require the use of the one called "rtabmap".
In order for the kinect 2 v2 to work as needed it is necessary to install the [libfreenect2](https://github.com/OpenKinect/libfreenect2) and the [IAI Kinect2](https://github.com/code-iai/iai_kinect2) drivers.

To establish the connection between the two machines it was chosen [rosbridge](http://wiki.ros.org/rosbridge_suite) which provides a JSON interface to ROS, allowing any client to send JSON to publish or subscribe to ROS topics, call ROS services, and more.


##### Inputs
The inputs are the images acquired by the kinect 2 v2 in RGB-D format, which is a combination of a RGB image and its corresponding depth image.
##### Internal working
RTAB-Map takes the RGB-D images and publishes them as ROS messages under different topics as shown in the documentation [here](http://wiki.ros.org/rtabmap_ros#rtabmap). 
##### Outputs
The outputs are the messages published on the different ROS topics, in particular we are interested on the ```/rtabmap/mapData``` topic on which is published the 3D point cloud map of the environment. The map can be visualized in Rviz, which will be launched automatically with the required settings to visualize the map, in order to make a pre check before starting to send the data stream to Unity via a websocket.


#### Unity visualization of a 3D point cloud map
This module is implemented on the machine running windows and provides a platform on which visualize the point cloud map put together by the SLAM module. Unity will visualize the map and provide the connection with the oculus with all the relative scripts to link the game camera with the movement of the oculus.

##### Inputs 
Unity receives the ROS messages of the ```/rtabmap/mapData``` topic via the websocket.

##### Internal working
All the functionalities descripted above are integrated in a custom script which connects
to the ROS node, receives the data and then converts the pointcloud atomic elements
into 3D cubes (composed by meshes), in order to make the scene more intuitive and
user friendly.
The cubes are then colored using a particular shader, the “GUI/text shader”, which
allows to maintain the original color registered by the RGB camera of the Kinect for
every point in space.
 
##### Outputs
The output will be the 3D point cloud map visualized on the Unity scene, composed this
time not by points but by colored cubes.
Everything will also be displayed on the connected oculus, giving the possibility to the
user to explore the scene just by moving around his head.

## Implementation

### Prerequisites
#### LINUX SIDE 
* Microsoft XBOX ONE KINECT 2 V2 with relative connection cable
* Ubuntu 16.04 LTS
* ROS Kinetic
* RTAB-Map package
* libfreenect2 drivers
* IAI Kinect2 drivers
* Rosbridge_suite

#### WINDOWS SIDE
* Oculus rift Developer Kit 2
* Windows 10
* Unity 2018.2.7f1
* Oculus APP
* Unity project files

#### TROUBLESHOOTING
* Notebook and laptops are apparently not supported by the Oculus kit. This seems to be
due to a lack of drivers for portable GPUs, which prevents the Oculus from displaying
anything.
* The Oculus must be directly connected to the graphic card of the computer.
* It is recommended to connect the USB cable to a USB 2.0 port. However, in our case
the Oculus worked fine as well even when connected to a 3.0 port.
* Before opening the Unity project is always recommended to have already run the Oculus
Runtime application (which is also very useful to check the status of the connection of
the device).
* If, while launching the unity project, the error "VR: OpenVR Error! OpenVR failed
initialization with error code VRInitError_Init_PathRegistryNotFound: 'Installation
path could not be located (110)'!" occurs, it’s necessary to install VR Samples from
the Unity Assets Store in order to fix it.


### How to run the project
Here it's described step by step how to download and run the project on a new computer.

#### LINUX SIDE 

####Preparation

If you don't already have it, install ROS kinetic as shown in the [tutorial](http://wiki.ros.org/kinetic/Installation/Ubuntu)

Install rtabmap using the following command:

```
sudo apt-get install ros-kinetic-rtabmap-ros
```

Modify in the folder ```/opt/ros/kinetic/share/rtabmap_ros/launch``` the file ```rgbd_mapping_kinect2.launch```:
 at row 25 set ```default = "true"```, at row 26 set ```default = "false"``` in order to open the pointcloud map with Rviz. 

Modify in ```/opt/ros/kinetic/share/rtabmap_ros/launch/config``` the file ```rgbd.rviz```:
at row 76 substitute ```/voxel_cloud``` with ```/rtabmap/cloud_map``` in order to visualize the correct topic from the beginning.

->Note: remember to open the files as sudo in order to being able to modify and save them.


In order to install freenect2 libraries follow the README's instructions [here](https://github.com/OpenKinect/libfreenect2)

In order to install IAI Kinect2 libraries follow the README's instructions [here](https://github.com/code-iai/iai_kinect2)

In order to install the rosbridge_suite use the command below:

```
sudo apt-get install ros-kinetic-rosbridge-suite 
```

####Running the node

Now, after having plugged in your kinect, you're ready to launch RTAB-Map. Open a terminal and launch

```
ROSCORE
```

In a new terminal type the command to initialize the RGB and depth sensors: 

```
roslaunch kinect2_bridge kinect2_bridge.launch publish_tf:=true
```


In a third terminal type the command to start the mapping mode:

```
roslaunch rtabmap_ros rgbd_mapping_kinect2.launch resolution:=qhd
```

The last thing to do is to set up the websocket necessary to send the data stream to unity. Please remember that in order for the websocket to successfully connect the two machines, they must be connected to the same network.

To launch the websocket run in a new terminal:

``` 
roslaunch rosbridge_server rosbridge_websocket.launch 
```

It could be useful to launch a ```rostopic hz /rtabmap/mapData``` command in another terminal in order to check if the message are being consistently sent 


#### WINDOWS SIDE
Start by downloading the repository with the unity code [here](https://github.com/EmaroLab/hrp_teleoperation/tree/Unity).

Plug the oculus in the computer paying attention to the warnings in the troubleshooting
section. The Oculus Sensor must be plugged in alongside the VR, otherwise the Unity
scene would not be displayed.

Then, run the Unity project by opening the scene contained inside the “/Oculus with
pose/Assets” folder.

Once the project is fully loaded, the Oculus properly connected and the websocket on
the Linux machine up and running, click on play on the editor.

All the relevant information would be displayed on the Unity console such as the
configuration and the pointcloud messages. After a short time (depending on the
amount of data that Unity is receiving) the map will appear onto the scene and putting
on the Oculus should be sufficient to give the user a proper 3D immersion into Virtual
Reality.

If the Oculus App is not already running it will be opened automatically. If it’s not, the
project will run on Unity but the Oculus VR won’t be able to show any image.

## Results
All the three modules (Kinect-Unity-Oculus) have been thoroughly tested and have demonstrated to be fully working. 
The final implementation allows the user to visualize the entirety of the map in a realistic and dynamic way while the virtual environment keeps expanding as the robot explores its surroundings.

You can see the implemented architecture working in the following videos:

[Kinect - Unity - Oculus interface Video 1](https://www.youtube.com/watch?v=akuiFXSs5n4)
[Kinect - Unity - Oculus interface Video 2](https://www.youtube.com/watch?v=fg03l9Zvy0s)


For further comments on the results please refer to the [Report](link of report) here on the repository.

## Recommendations
The fundamental recommendiation are already reported in the "TROUBLESHOOTING" section above, for an in-depth analisys please refer to the [Report](link of report) here on the repository.

## Authors
* Enrico Casagrande: erri.casagrande@gmail.com
* Alberto Ghiotto: alberto.ghiotto@hotmail.it
