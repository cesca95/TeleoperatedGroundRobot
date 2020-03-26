# Mobile Robot Teleoperation - Adapter Kinect Module

### Kinetic Sensor Module

The Kinetic Sensor module takes as input the data sent by the Kinect v1 and gives as output a customized RPY ROS message containing the pitch of the user's arm.

## Implementation

### Prerequisites

Hardware prerequisites:

1. PC with Ubuntu 16.04 and following characteristics:
	-64 bit processor (x64)
    -Dual-core 2.66-GHz or faster processor
	-Dedicated USB 2.0 bus
	-2+ GB RAM

1. Microsoft Kinect Sensor v1 with USB adapter
 
Software prerequisites:

1. Install and update basic drivers:
    ```bash
    apt-get update
    sudo apt-get install git build-essential python libusb-1.0-0-dev freeglut3-dev openjdk-8-jdk
    sudo apt-get install doxygen graphviz mono-complete

    ```
1. Install OpenNI (we suggest to follow the tutorial and install OpenNI, NITE and Sensor Kinect in  the same folder called kinect):
	```bash
   	cd ~/
	mkdir kinect
	cd ~/kinect
	git clone https://github.com/OpenNI/OpenNI.git
	cd OpenNI 
	git checkout Unstable-1.5.4.0	
	cd Platform/Linux/CreateRedist
	chmod +x RedistMaker
	./RedistMaker
	cd ../Redist/OpenNI-Bin-Dev-Linux-x64-v1.5.4.0
	sudo ./install.sh
    ```
1.  Install Sensor Kinect:
	```bash
    SensorKinect:
	cd ~/kinect
	git clone https://github.com/avin2/SensorKinect
	cd SensorKinect
	cd Platform/Linux/CreateRedist
	chmod +x RedistMaker
	./RedistMaker
	cd ../Redist/Sensor-Bin-Linux-x64-v5.1.2.1 
	chmod +x install.sh
	sudo ./install.sh 
    ```
    
1.  Install Kinetic OpenNi:
    ```bash    
    sudo apt-get install ros-kinetic-openni*
    ```

1. Install NITE 1.5.2.23 (Change directory to x64 or x86 according to your PC):
	```bash  
	cd ~/kinect  
    git clone https://github.com/arnaud-ramey/NITE-Bin-Dev-Linux-v1.5.2.23.git
	cd x64
	sudo bash install.sh
    ```
1. Install openni_tracker (must be installed in the src folder of the ws):
	```bash    
	cd ~/<workspace_name>/src
    git clone https://github.com/ros-drivers/openni_tracker.git 
    ```

### How to setup the Adapter Kinect Module

1. After launching the controller launch file, in order to start the skeleton tracking feature of the Kinect, be sure to be User1.

1. Assume the [Psi-Pose](http://3.bp.blogspot.com/-t9FxKt9JUts/TWfK4juSF7I/AAAAAAAABBI/36-uvouIG7I/s320/PsiPose.gif) and stay in such position until the calibration is completed. 

1. Check Rviz to be sure that the calibration was successful. 

## Recommendations and limitations

1. Make sure that your arm swing is correctly perceived by the Kinect camera verifying through Rviz.

1. Whenever the user is lost or not registered as User1, the controller must be launched again. This is made in order to prevent multiple users interference.

## Authors
* Alberto Grillo: albogrillo@gmail.com
* Claudio Curti: curti.claudio96@gmail.com
* Francesca Cantoni: francescacantoni95@gmail.com
