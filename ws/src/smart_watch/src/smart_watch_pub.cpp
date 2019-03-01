#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
#include "tf/transform_listener.h"
#include <tf/transform_datatypes.h>
#include "geometry_msgs/Quaternion.h"
#include <geometry_msgs/TransformStamped.h>
#include <tf2/convert.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <tf/tf.h>
#include "my_msgs/RPY.h"


///VARIABLE DECLARATION

tf::Quaternion orientation_tf;
geometry_msgs::Quaternion orientation_geom;

double yaw, pitch, roll;

void chatterCallback(const sensor_msgs::Imu::ConstPtr &msg)
{
  ///Save the message contents representing quaternion orientation in variables of type geometry_msgs::Quaternion
  orientation_geom.x = msg->orientation.x;
  orientation_geom.y = msg->orientation.y;
  orientation_geom.z = msg->orientation.z;
  orientation_geom.w = msg->orientation.w;

  ///Convert geometry_msgs::Quaternion to tf::Quaternion 
  quaternionMsgToTF(orientation_geom,orientation_tf);

  ///Convert from quaternion to RPY
  tf::Matrix3x3 m(orientation_tf);
  m.getRPY(roll, pitch, yaw);
}

int main(int argc, char **argv)
{
  ///Node initialization
  ros::init(argc, argv, "smart_watch_pub");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("imu/data", 1000, chatterCallback);
  ros::Publisher pub = n.advertise<my_msgs::RPY>("orientation", 1000);

  ros::Rate loop_rate(10);

  ///Main loop
  while(ros::ok())
  {
    ///Fill a message of type RPY with the values obtained by the conversion from received data
    my_msgs::RPY msg;
    msg.roll = roll;
    msg.pitch = pitch;
    msg.yaw = yaw;

    ros::spinOnce();
    ///Publish the message
    pub.publish(msg);
    loop_rate.sleep();
  }

  return 0;
}
