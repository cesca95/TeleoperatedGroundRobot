#!/usr/bin/env python

## Script that converts the leap motion data into Twist messages by a defined hand-gesture in order to teleoperate a robot

import rospy
import math
from leap_motion.msg import leap
from leap_motion.msg import leapros
from geometry_msgs.msg import Twist
from my_msgs.msg import RPY

#teleop_topic = '/cmd_vel_mux/input/teleop'
teleop_topic = '/turtle1/cmd_vel' # For use with turtlesim
orientation_topic ='/orientation' # For use with controller

# Change values according to leap motion
low_speed = -0.5
stop_speed = 0
high_speed = 0.5

low_turn = -0.5
stop_turn = 0
high_turn = 0.5

pitch_low_range = -20
pitch_high_range = 20

roll_low_range = -50
roll_high_range = 80


# Callback of the ROS subscriber
def callback_ros(data):
    global pub

    msg = leapros()
    msg = data
    
    yaw = msg.ypr.z
    pitch = msg.ypr.y
    roll = msg.ypr.x

    twist = Twist()

    twist.linear.x = 0; twist.linear.y = 0; twist.linear.z = 0
    twist.angular.x = 0; twist.angular.y = 0; twist.angular.z = 0

#Just sending Twist message
   
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

    #rospy.loginfo(rospy.get_name() + ": Roll %s" % msg.ypr.x)
    #rospy.loginfo("\n")
    rospy.loginfo(rospy.get_name() + ": Yaw %s" % yaw + ": Pitch %s" % pitch + ": Roll %s" % roll)
    #rospy.loginfo("\n")
    
    # Publish Roll/Pitch/Yaw
    orientation = RPY()
    orientation.roll = roll; orientation.pitch = pitch; orientation.yaw = yaw;
    pub_orientation.publish(orientation)


# Listens to: leapmotion/data
def listener():
    global pub_teleop, pub_orientation
    rospy.init_node('leap_sub', anonymous=True)
    rospy.Subscriber("leapmotion/data", leapros, callback_ros)
    pub_teleop = rospy.Publisher(teleop_topic, Twist, queue_size=1)
    pub_orientation = rospy.Publisher(orientation_topic, RPY, queue_size=1) 
    
    rospy.spin()


if __name__ == '__main__':
    listener()
