#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <cmath>
#include "my_msgs/RPY.h"


double yaw, pitch, roll; ///these angles are the fields of the message

int main(int argc, char** argv){
  ros::init(argc, argv, "kinect_pub"); 

  ros::NodeHandle node;
  tf::TransformListener listener;
  ros::Publisher pub = node.advertise<my_msgs::RPY>("orientation",1000); ///orientation is the topic on which we publish the angles
  
  ros::Rate rate(10.0); ///10 Hz
  while (node.ok()){
    tf::StampedTransform tf_shoulder; ///define a transformation matrix for the shoulder
    tf::StampedTransform tf_elbow; ///define a transformation matrix for the elbow
    tf::Vector3 arm_vector; ///define a transformation matrix between shoulder and elbow
    tf::Vector3 ref_vector(0.0,-1.0,0.0); ///vertical reference vector to measure the pitch angle
    
    try ///if it is posssible to extract the transformation matrices
    {
      listener.lookupTransform("/openni_depth_optical_frame", "/right_shoulder_1",  
                               ros::Time(0), tf_shoulder); ///transformation matrix between shoulder and kinect
      listener.lookupTransform("/openni_depth_optical_frame","/right_elbow_1",   
                               ros::Time(0), tf_elbow); ///transformation matrix between hand and kinect
      
      arm_vector = tf_shoulder.getOrigin()-tf_elbow.getOrigin(); ///vector joining shoulder and elbow 
     
      pitch = arm_vector.angle(ref_vector); ///extract the angle formed by the reference vector and the arm_vector
      
      ROS_INFO("Pitch %lf",pitch);
      my_msgs::RPY msg;
      msg.roll = 0; ///default value
      msg.pitch = pitch - M_PI/2; ///shifting of pi/2 according to the values produced by the other sensors
      msg.yaw = 0; ///default value

      pub.publish(msg);
    }
    catch (tf::TransformException ex){ ///otherwise throw an exception
      ROS_ERROR("%s",ex.what());
      ros::Duration(1.0).sleep();    
    }
        
    rate.sleep();
  }
  return 0;
};
