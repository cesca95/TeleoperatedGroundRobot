#!/usr/bin/env python

## @package leap_teleop
# @date 19-02-2019
# @authors Nicolas Dejon and Adam Berka
# @brief Leap Motion Teleoperation
# @details Script that sends the raw yaw, pitch and roll angles in degrees to the /orientation topic.@n
# It also converts the leap motion data into Twist messages by a defined hand-gesture in order to teleoperate the simulated robot turtlesim

import rospy
import math
from leap_motion.msg import leap
from leap_motion.msg import leapros
from geometry_msgs.msg import Twist
from my_msgs.msg import RPY

## Topic used by turtlesim
teleop_topic = '/turtle1/cmd_vel' # For use with turtlesim
## Topic used by the common controller
orientation_topic ='/orientation' # For use with controller

# Change values according to leap motion calibration
## Robot value for backward move
low_speed = -0.5
## Robot value for stopping
stop_speed = 0
## Robot value for forward move
high_speed = 0.5

## Robot value for turning right
low_turn = -0.5
## Robot value for stopping turn
stop_turn = 0
## Robot value for turning left
high_turn = 0.5

## Start of range for detecting low pitch 
pitch_low_range = -20
## Start of range for detecting high pitch
pitch_high_range = 20


## Start of range for detecting roll right
roll_low_range = -50
## Start of range for detecting roll left
roll_high_range = 80

## Sends the raw incoming yaw, pitch and roll angles from the Leap Motion to the /orientation topic
def sendOrientation(yaw,pitch,roll):
    # Publish Roll/Pitch/Yaw
    orientation = RPY()
    orientation.roll = roll; orientation.pitch = pitch; orientation.yaw = yaw;
    pub_orientation.publish(orientation)
    #rospy.loginfo(rospy.get_name() + ": Yaw %s" % yaw + ": Pitch %s" % pitch + ": Roll %s" % roll)
    #rospy.loginfo("\n")

## Interprets the received yaw, pitch and roll into user-defined hand gestures that controls
# the simulated robot turltesim by sending Twist messages
def sendTeleop(yaw,pitch,roll):
    # Just sending Twist messages
    twist = Twist()

    twist.linear.x = 0; twist.linear.y = 0; twist.linear.z = 0
    twist.angular.x = 0; twist.angular.y = 0; twist.angular.z = 0

    if(pitch < pitch_low_range and pitch > pitch_low_range - 30 ):
	    twist.linear.x = high_speed; twist.linear.y = 0; twist.linear.z = 0
	    twist.angular.x = 0; twist.angular.y = 0; twist.angular.z = 0
            #rospy.loginfo("Pitch low")
    
    elif(pitch > pitch_high_range and pitch < pitch_high_range + 30):
	    twist.linear.x = 0; twist.linear.y = 0; twist.linear.z = 0
	    twist.angular.x = 0; twist.angular.y = 0; twist.angular.z = 0
            #rospy.loginfo("Pitch high")

    
    if(roll > roll_high_range and roll < roll_high_range + 50):
	    twist.linear.x = 0; twist.linear.y = 0; twist.linear.z = 0
	    twist.angular.x = 0; twist.angular.y = 0; twist.angular.z = high_turn
            #rospy.loginfo("Roll left")

    
    elif(roll < roll_low_range and roll > roll_low_range - 50):
	    twist.linear.x = 0; twist.linear.y = 0; twist.linear.z = 0
	    twist.angular.x = 0; twist.angular.y = 0; twist.angular.z = low_turn
            #rospy.loginfo("Roll right")
    
    
    pub_teleop.publish(twist) # Publish the Twist messages to the turtlesim

## Callback of the ROS subscriber to send the orientation messages to the controller 
#  and the Twist messages to control the robot
def callback_ros(data):

    msg = leapros() # Get the messages from the Leap Motion
    msg = data
    
    yaw = msg.ypr.z
    pitch = msg.ypr.y
    roll = msg.ypr.x
    
    sendOrientation(yaw,pitch,roll)
    sendTeleop(yaw,pitch,roll) # Comment this line if you are not using turtlesim


## Listens to leapmotion/data and starts ROS spin
def listener():
    global pub_teleop, pub_orientation
    rospy.init_node('leap_sub', anonymous=True)
    rospy.Subscriber("leapmotion/data", leapros, callback_ros)
    pub_teleop = rospy.Publisher(teleop_topic, Twist, queue_size=1)
    pub_orientation = rospy.Publisher(orientation_topic, RPY, queue_size=1) 
    
    rospy.spin()

## Main is main
if __name__ == '__main__':
    listener()
