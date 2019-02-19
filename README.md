# hrp_teleoperation

## Objective of the Project
It describes what the project wants to achieve and defines terminologies. Presents the hardware or tools used in the project.

## The System’s Architecture

### Overall Architecture
It describes what the project wants to achieve and defines the key terminologies of this project. Presents the hardware or tools used in the project.

### Description of the Modules
#### Feature Leap Motion Teleoperation
This branch is about creating a project to teleoperate a robot using a Leap Motion controller with hand gestures.

##### Inputs
Hands and fingers motions.

##### Internal working
Images taken by two cameras are analyzed to reconstruct a 3D representation of what the device sees. Tracking algorithms interpret the 3D data and infer the pitch and the roll of occluded objects. Thresholds for commands are:
  * pitch
  -50 to -20 degrees
  * roll
  -100 to -50 and 80 to 130 degrees
  
##### Outputs
Outputs are commands for robot. When gesture command will be in pitch threshold, value 0.5 (move forward) will be send to the robot. When gesture command will be in lower threshold of roll, value -0.5 (turn right) will be send to the robot. Value 0.5 (turn left) will be send when gesture command will be in higher tershold for roll.

## Implementation

### Prerequisites
* Leap Motion controller
* USB cabel
* Ubuntu 16.04 LTS
* ROS Kinectic
* Leap Motion SDK

### How to run the project
#### Download and installation of Leap Motion SDK
1. Download Leap Motion SDK in Ubuntu form [here](https://www.leapmotion.com/setup/linux)
2. Open Terminal on the extracted location and install the DEB using: 

    ```
    sudp dpkg -install Leap-*-x64.deb
    ```

More detailed installation and debugging are [here](https://support.leapmotion.com/hc/en-us/articles/223782608-Linux-Installation)

3. Open Terminal and execute the command to verify that device is properly detected on Ubuntu

    ```
    dmesg
    ```
    
4. Invoke Leap Motion controller manager by ececuting the following command:

    ```
    sudo LeapControlPanel
    ```

5. If you want to start just the driver, you can use the following command:

    ```
    sudo leapd
    ```
    
6. Use this commands to restart the driver

    ```
    sudo service leapd stop
    sudo service leapd start
    ```
    
#### Installing the ROS driver for the Leap Motion controller
1. Download ROS driver

    ```
    git clone https://github.com/ros-drivers/leap_motion
    ```
    
2. Set the path of the Leap Motion SDK in the `.bashrc` file. Assuming that the Leap SDK is in the user's `home` folder with the name `LeapSDK`, we have to set the path variable in `.bashrc` as follows.

    ```
    export LEAP_SDK=$LEAP_SDK:$HOME/LeapSDK
    ```
    
3.  We also have to add the path of the Python extension of the Leap Motion SDK to `.bashrc`.

    ```
    export PYTHONPATH=$PYTHONPATH:$HOME/LeapSDK/lib:$HOME/LeapSDK/lib/x64
    ```
    
4. In new terminal copy the `libLeap.so` file to `/usr/local/lib`. Here is how we do it:

    ```
    sudo cp $LEAP_SDK/lib/x64/libLeap.so /usr/local/lib 
    ```
    
5. After copying, execute `ldconfig`:

    ```
    sudo ldconfig
    ```
    
6. Create a ROS workspace or copy the `leap_motion` package to an existing ROS workspace and use `catkin_make`
You can use the following command to install the `leap_motion` package:

    ```
    catkin_make install --pkg leap_motion
    ```
    
#### Running
Terminal 0: 

    
     sudo LeapControlPanel
   
    
Terminal 1: 

      roscore
      
Terminal 2: 

      roslaunch leap_motion sensor_sender.launch
      
Terminal 3: 

      rosrun leap_teleop leap_teleop.py
      
Terminal 4: 

      rosrun turtlesim turtlesim_node

#### Testing
Terminal 5: 

      rostopic echo /turtle1/cmd_vel
      rostopic echo /orientation

## Results
[Simulation with Turtlesim ](https://youtu.be/OcLwWefhjv0)

## Recommendations
While building the system we spotted some limitations in the hand gesture detection due to accuracy of sensors' work and due to user-defined tresholds. The idea to minimalize those limitations is to calibrate range of tresholds before use by each user.
ideas: calibrate range of tresholds addording to each user.

## Authors
* Adam Berka: berkaadam7@gmail.com
* Nicolas Dejon: nicolas.dejon@etu.utc.fr

# hrp_teleoperation_old

After cloning the repository type in ~/hrp_teleoperation

git submodule init

and

git submodule update

This commands will link to the submodules and pull all the relative code

In order to use the rgbdslam module follow the instructions at this link:(changed to rtabmap)

https://hubpages.com/technology/Instructions-for-compiling-rgbdslam-v2-on-a-fresh-Ubuntu-1604-install-ros-kinetic-in-virtualbox


http://wiki.ros.org/rtabmap_ros

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
