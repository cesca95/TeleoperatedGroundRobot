;; Auto-generated. Do not edit!


(when (boundp 'mqtt_ros_bridge::ImuPackage)
  (if (not (find-package "MQTT_ROS_BRIDGE"))
    (make-package "MQTT_ROS_BRIDGE"))
  (shadow 'ImuPackage (find-package "MQTT_ROS_BRIDGE")))
(unless (find-package "MQTT_ROS_BRIDGE::IMUPACKAGE")
  (make-package "MQTT_ROS_BRIDGE::IMUPACKAGE"))

(in-package "ROS")
;;//! \htmlinclude ImuPackage.msg.html


(defclass mqtt_ros_bridge::ImuPackage
  :super ros::object
  :slots (_linear_acceleration _angular_velocity ))

(defmethod mqtt_ros_bridge::ImuPackage
  (:init
   (&key
    ((:linear_acceleration __linear_acceleration) (let (r) (dotimes (i 0) (push (instance mqtt_ros_bridge::Vector3Time :init) r)) r))
    ((:angular_velocity __angular_velocity) (let (r) (dotimes (i 0) (push (instance mqtt_ros_bridge::Vector3Time :init) r)) r))
    )
   (send-super :init)
   (setq _linear_acceleration __linear_acceleration)
   (setq _angular_velocity __angular_velocity)
   self)
  (:linear_acceleration
   (&rest __linear_acceleration)
   (if (keywordp (car __linear_acceleration))
       (send* _linear_acceleration __linear_acceleration)
     (progn
       (if __linear_acceleration (setq _linear_acceleration (car __linear_acceleration)))
       _linear_acceleration)))
  (:angular_velocity
   (&rest __angular_velocity)
   (if (keywordp (car __angular_velocity))
       (send* _angular_velocity __angular_velocity)
     (progn
       (if __angular_velocity (setq _angular_velocity (car __angular_velocity)))
       _angular_velocity)))
  (:serialization-length
   ()
   (+
    ;; mqtt_ros_bridge/Vector3Time[] _linear_acceleration
    (apply #'+ (send-all _linear_acceleration :serialization-length)) 4
    ;; mqtt_ros_bridge/Vector3Time[] _angular_velocity
    (apply #'+ (send-all _angular_velocity :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; mqtt_ros_bridge/Vector3Time[] _linear_acceleration
     (write-long (length _linear_acceleration) s)
     (dolist (elem _linear_acceleration)
       (send elem :serialize s)
       )
     ;; mqtt_ros_bridge/Vector3Time[] _angular_velocity
     (write-long (length _angular_velocity) s)
     (dolist (elem _angular_velocity)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; mqtt_ros_bridge/Vector3Time[] _linear_acceleration
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _linear_acceleration (let (r) (dotimes (i n) (push (instance mqtt_ros_bridge::Vector3Time :init) r)) r))
     (dolist (elem- _linear_acceleration)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; mqtt_ros_bridge/Vector3Time[] _angular_velocity
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _angular_velocity (let (r) (dotimes (i n) (push (instance mqtt_ros_bridge::Vector3Time :init) r)) r))
     (dolist (elem- _angular_velocity)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get mqtt_ros_bridge::ImuPackage :md5sum-) "62e531d68c2a751bac021327d713af95")
(setf (get mqtt_ros_bridge::ImuPackage :datatype-) "mqtt_ros_bridge/ImuPackage")
(setf (get mqtt_ros_bridge::ImuPackage :definition-)
      "mqtt_ros_bridge/Vector3Time[] linear_acceleration
mqtt_ros_bridge/Vector3Time[] angular_velocity
================================================================================
MSG: mqtt_ros_bridge/Vector3Time
geometry_msgs/Vector3 vector
std_msgs/UInt64 time


================================================================================
MSG: geometry_msgs/Vector3
# This represents a vector in free space. 
# It is only meant to represent a direction. Therefore, it does not
# make sense to apply a translation to it (e.g., when applying a 
# generic rigid transformation to a Vector3, tf2 will only apply the
# rotation). If you want your data to be translatable too, use the
# geometry_msgs/Point message instead.

float64 x
float64 y
float64 z
================================================================================
MSG: std_msgs/UInt64
uint64 data
")



(provide :mqtt_ros_bridge/ImuPackage "62e531d68c2a751bac021327d713af95")


