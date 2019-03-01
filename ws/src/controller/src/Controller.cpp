/**
*	@package controller
*	@date 28-02-2019
*	@authors Nicola De Carli and Noel Alejandro Avila Campos and Angelica Ginnante  
*	@brief Controller used for teleoperation of a Husqvarna Automower
*	@details Program that receives orientation data from the sensors and remap them to velocity sent the robot topic.@n
*/

#include "ros/ros.h"
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include "geometry_msgs/Twist.h"
#include <cstdlib>
#include "my_msgs/RPY.h"
#include <sstream>
#include "string.h"
#include <stdlib.h>
#include <stdio.h> 
#include <iostream>
#include <math.h>


///CONSTANTS DECLARATION

///Gains for the conversions to velocity
#define ANGULAR_GAIN 1.0		///Gain for the conversion from roll angle to angular velocity
#define LINEAR_GAIN 2.0			///Gain for the conversion from pitch angle to linear velocity

///Thresholds max/min for the conversions to velocity
#define MIN_ANGULAR_THRESHOLD 0.2	///For roll angles under this threshold the angular velocity is put to zero, to make easier to keep the robot fixed
#define MIN_LINEAR_THRESHOLD 0.1        ///For pitch angles under this threshold the linear velocity is put to zero, to make easier to keep the robot fixed
#define MAX_ANGULAR_THRESHOLD 1.5       ///For roll angles over this threshold the angular velocity doesn't increase anymore
#define MAX_LINEAR_THRESHOLD 1.3	///For pitch angles over this threshold the linear velocity doesn't increase anymore

#define SENSOR_TIMEOUT 1.0		///Time beyond which the controller consider the sensor useless if it doesn't update informations
#define SENSOR_IS_ACTIVE 4		///If the message from a sensor remains exactly the same for more than this value, then the data is considered unreliable

///Weights to compute the average velocities from the data sensors, based on the sensor reliability
#define SMART_WATCH_WEIGHT 1
#define KINECT_WEIGHT 1
#define LEAP_WEIGHT 1


///VARIABLES DECLARATION

///Time of the arrive of the last message for each sensor
ros::Time begin_smartwatch;
ros::Time begin_kinect;
ros::Time begin_leap;

///Flag to signal that the sensor is active
int flag_smart_watch = 0;
int flag_kinect = 0;
int flag_leap = 0;

int sensor_counter = 0;  		///Number of active sensors

///Roll and pitch angles arriving from the various sensors
double roll_smartwatch;
double pitch_smartwatch;
double roll_kinect;
double pitch_kinect;
double roll_leap;
double pitch_leap;

///Preceiding measures arrived from each sensor to evaluate its reliability (--> if the message doesn't change for a lot of time probably the message is unreliable)
double last_roll_smartwatch = 0;
double last_pitch_smartwatch = 0;
double last_pitch_kinect = 0;
double last_roll_leap = 0;
double last_pitch_leap = 0;

///Velocities obtained converting from the angle provided by the sensors
double lv_smartwatch = 0;
double av_smartwatch = 0;
double lv_kinect = 0;
double av_kinect = 0;	///This never changes because the kinect gives no roll information 
double lv_leap = 0;
double av_leap = 0;	 

///Possible senders of the messages we are receiving
const std::string& SMARTWATCH = "/smart_watch_pub";
const std::string& KINECT = "/kinect_pub";
const std::string& LEAP = "/leap_pub_32408_1551361598387";


//////////////////////////////////////////////////////////////////////////////////

void orientationCallback(const ros::MessageEvent<my_msgs::RPY const>& event)
{
  ///Get the sender name
  const std::string& publisher_name = event.getPublisherName();  
  ///Get the content of the message 
  const my_msgs::RPY::ConstPtr& msg = event.getMessage();
  
  std::cout << publisher_name << std::endl;

  ///Compare the publisher name with that of the known publishers 
  
  //////////	SMARTWATCH	/////////////
  if(publisher_name.compare(SMARTWATCH) == 0)
  { 
   if(flag_smart_watch == 0) ///If this sensor wasn't active, then activate it
   {
    sensor_counter++;
    flag_smart_watch = 1;
   }
   ///Extract the angles from the message
   roll_smartwatch = msg->roll;
   pitch_smartwatch = msg->pitch;
   ///Start the timer for this sensor
   begin_smartwatch= ros::Time::now();
  }

  //////////	KINECT	   /////////////
  else if(publisher_name.compare(KINECT) == 0)
  { 
   if(flag_kinect == 0)///If this sensor wasn't active, then activate it
   {
    sensor_counter++;
    flag_kinect = 1;
   }
   ///Extract the angles from the message
   roll_kinect = msg->roll;
   pitch_kinect = msg->pitch;
   ///Start the timer for this sensor
   begin_kinect = ros::Time::now();
  }
  
  //////////	LEAP MOTION	/////////////
  else
  { 
   if(flag_leap == 0)///If this sensor wasn't active, then activate it
   {
    sensor_counter++;
    flag_leap = 1;
   }
   ///Extract the angles from the message
   roll_leap = msg->roll;
   pitch_leap = msg->pitch;
   ///Start the timer for this sensor
   begin_leap = ros::Time::now();
  }
}


int main(int argc, char **argv)
{
  ///NODE INITIALIZATION
  
  ros::init(argc, argv, "controller");

  ros::NodeHandle n;

  ros::Publisher velocity_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

  ros::Subscriber controller_sub = n.subscribe("orientation", 1000, orientationCallback);

  ros::Rate loop_rate(10);
  
  ///VARIABLES DECLARATION
  
  ///Variables to count for how many times the message from each sensor has remained equal
  int count_smartwatch = 0;
  int count_kinect = 0;
  int count_leap = 0;
  ///Variable to take the time
  ros::Time now;
  ///Constant representing the time beyond which the controller consider the sensor useless if it doesn't update informations
  ros::Duration one_sec(SENSOR_TIMEOUT);
  ///Message to send
  geometry_msgs::Twist twist;
  
  
  while (ros::ok())
  {
   ////////////////////////////////////////	SMART_WATCH	//////////////////////////////////////////////////////////////////
   if(flag_smart_watch == 1)
   {
    ////////////    LINEAR VELOCITY	//////////////
   
    ///If the absolute value is less than a threshold consider it zero, to make easier to keep the robot fixed
    if(fabs(pitch_smartwatch) < MIN_LINEAR_THRESHOLD)
    {
     lv_smartwatch = 0;
    }
    ///If the absolute value is over the threshold then use the maximum angle instead of the actual angle to compute the velocity
    else if(fabs(pitch_smartwatch) > MAX_LINEAR_THRESHOLD)
    {
     int sign = pitch_smartwatch / fabs(pitch_smartwatch);
     lv_smartwatch = sign * MAX_LINEAR_THRESHOLD * LINEAR_GAIN;
    }
    ///Compute the velocity in the standard way if the value of the angle is betweeen the two threshold
    else
    {
     lv_smartwatch = pitch_smartwatch * LINEAR_GAIN;
    }  
    
    ////////////    ANGULAR VELOCITY	//////////////
    
    ///If the absolute value is less than a threshold consider it zero, to make easier to keep the robot fixed
    if(fabs(roll_smartwatch) < MIN_ANGULAR_THRESHOLD)
    {
     av_smartwatch = 0;
    }
    ///If the absolute value is over the threshold then use the maximum angle instead of the actual angle to compute the velocity
    else if(fabs(roll_smartwatch) > MAX_ANGULAR_THRESHOLD)
    {
     int sign = roll_smartwatch / fabs(roll_smartwatch);
     av_smartwatch = sign * MAX_ANGULAR_THRESHOLD * ANGULAR_GAIN;
    }
    ///Compute the velocity in the standard way if the value of the angle is betweeen the two threshold
    else
    {
     av_smartwatch = roll_smartwatch * ANGULAR_GAIN;
    }
    
    /////////////////	SENSOR CHECK /////////////////////////////
    
    now = ros::Time::now();	///Check the time
    ///If the values of the two angles are both the same as those of the previous message increase the counter
    if(last_roll_smartwatch == roll_smartwatch && last_pitch_smartwatch == pitch_smartwatch)
    {
      count_smartwatch++;
    }
    ///If it is different restart the counter
    else
    { 
      count_smartwatch = 0; 
    }
    ///If no data has arrived in the last second, or the message from the sensor has remained the same for too many times then do not consider the output due to this sensor, it could be unreliable
    if(now - begin_smartwatch > one_sec || count_smartwatch >SENSOR_IS_ACTIVE)
    {
     lv_smartwatch = 0;
     av_smartwatch = 0;
     sensor_counter--;
     flag_smart_watch = 0;
    }    
    ///update the previous values
    last_roll_smartwatch = roll_smartwatch;
    last_pitch_smartwatch = pitch_smartwatch;
   }
   
   
   ////////////////////////////////////////	KINECT	//////////////////////////////////////////////////////////////////
   if(flag_kinect == 1)
   {
    ////////////    LINEAR VELOCITY	//////////////
   
    ///If the absolute value is less than a threshold consider it zero, to make easier to keep the robot fixed
    if(fabs(pitch_kinect) < MIN_LINEAR_THRESHOLD)
    {
     lv_kinect = 0;
    }
    ///If the absolute value is over the threshold then use the maximum angle instead of the actual angle to compute the velocity
    else if(fabs(pitch_kinect) > MAX_LINEAR_THRESHOLD)
    {
     int sign = pitch_kinect / fabs(pitch_kinect);
     lv_kinect = sign * MAX_LINEAR_THRESHOLD * LINEAR_GAIN;
    }
    ///Compute the velocity in the standard way if the value of the angle is betweeen the two threshold
    else
    {
     lv_kinect = pitch_kinect * LINEAR_GAIN;
    }
    
    /////////////////	SENSOR CHECK ///////////////////////////////////
    
    now = ros::Time::now();	///Check the time
    ///If the values of the two angles are both the same as those of the previous message increase the counter
    if(last_pitch_kinect == pitch_kinect)
    {
      count_kinect++;
    }
    ///If it is different restart the counter
    else
    { 
      count_kinect = 0; 
    }
    ///If no data has arrived in the last second, or the message from the sensor has remained the same for too many times then do not consider the output due to this sensor, it could be unreliable
    if(now - begin_kinect > one_sec || count_kinect >SENSOR_IS_ACTIVE)
    {
     lv_kinect = 0;
     av_kinect = 0;
     sensor_counter--;
     flag_kinect = 0;
    }
    ///update the previous values
    last_pitch_kinect = pitch_kinect;
   }
   
   
   ////////////////////////////////////////	LEAP_MOTION	//////////////////////////////////////////////////////////////////
   if(flag_leap == 1)
   {
    ////////////    LINEAR VELOCITY	//////////////
   
    ///If the absolute value is less than a threshold consider it zero, to make easier to keep the robot fixed
    if(fabs(pitch_leap) < MIN_LINEAR_THRESHOLD)
    {
     lv_leap = 0;
    } 
    ///If the absolute value is over the threshold then use the maximum angle instead of the actual angle to compute the velocity
    else if(fabs(pitch_leap) > MAX_LINEAR_THRESHOLD)
    {
     int sign = pitch_leap / fabs(pitch_leap);
     lv_leap = sign * MAX_LINEAR_THRESHOLD * LINEAR_GAIN;
    }
    ///Compute the velocity in the standard way if the value of the angle is betweeen the two threshold
    else
    {
     lv_leap = pitch_leap * LINEAR_GAIN;
    }  
    
    ////////////    ANGULAR VELOCITY	//////////////
    
    ///If the absolute value is less than a threshold consider it zero, to make easier to keep the robot fixed
    if(fabs(roll_leap) < MIN_ANGULAR_THRESHOLD)
    {
     av_leap = 0;
    }
    ///If the absolute value is over the threshold then use the maximum angle instead of the actual angle to compute the velocity
    else if(fabs(roll_leap) > MAX_ANGULAR_THRESHOLD)
    {
     int sign = roll_leap / fabs(roll_leap);
     av_leap = sign * MAX_ANGULAR_THRESHOLD * ANGULAR_GAIN;
    }
    ///Compute the velocity in the standard way if the value of the angle is betweeen the two threshold
    else
    {
     av_leap = roll_leap * ANGULAR_GAIN;
    }
    
    /////////////////	SENSOR CHECK //////////////////////////////
    
    now = ros::Time::now();	///Check the time
    ///If the values of the two angles are both the same as those of the previous message increase the counter
    if(last_roll_leap == roll_leap && last_pitch_leap == pitch_leap)
    {
      count_leap++;
    }
    ///If it is different restart the counter
    else
    { 
      count_leap = 0; 
    }
    ///If no data has arrived in the last second, or the message from the sensor has remained the same for too many times then do not consider the output due to this sensor, it could be unreliable
    if(now - begin_leap > one_sec || count_leap >SENSOR_IS_ACTIVE)
    {
     lv_leap = 0;
     av_leap = 0;
     sensor_counter--;
     flag_leap = 0;
    }    
    ///update the previous values
    last_roll_leap = roll_leap;
    last_pitch_leap = pitch_leap;
   }
   
   
   ////////////////////////////////////////	AVERAGE		//////////////////////////////////////////////////////////////////
   
   ///If at least one sensor is connected the velocity should be the weighted average between the velocities computed with the data from each sensor
   if(sensor_counter > 0)
   {
     twist.linear.x = ( (flag_smart_watch * SMART_WATCH_WEIGHT * lv_smartwatch) + (flag_kinect * KINECT_WEIGHT * lv_kinect) + (flag_leap * LEAP_WEIGHT * lv_leap) ) / (flag_smart_watch * SMART_WATCH_WEIGHT + 				flag_kinect * KINECT_WEIGHT + flag_leap * LEAP_WEIGHT);
     ///If the only sensor active is the kinect set the angular velocity to zero
     if(flag_smart_watch == 0 && flag_leap == 0)
     {
      twist.angular.z = 0;
     }
     ///For the computation of the angular component don't consider the kinect because it doesn't provide the roll angle  
     else
     {
      twist.angular.z = ( (flag_smart_watch * SMART_WATCH_WEIGHT * av_smartwatch) + (flag_leap * LEAP_WEIGHT * av_leap) ) / (flag_smart_watch * SMART_WATCH_WEIGHT + flag_leap * LEAP_WEIGHT);     
     }
   }
   ///Otherwise set all the velocities to zero
   else 
   {
    twist.linear.x = 0;
    twist.angular.z = 0;
   }
   ///Publish the velocity on the cmd_vel topic
   velocity_pub.publish(twist);
   ros::spinOnce();
   loop_rate.sleep();   
  }
  return 0;
}

