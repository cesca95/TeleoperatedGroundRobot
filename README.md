# hrp_teleoperation

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

Launch:
roscore

roslaunch freenect_launch freenect.launch depth_registration:=true

roslaunch rtabmap_ros rtabmap.launch rtabmap_args:="--delete_db_on_start"
