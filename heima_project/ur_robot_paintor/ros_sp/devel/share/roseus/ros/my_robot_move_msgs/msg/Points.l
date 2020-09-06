;; Auto-generated. Do not edit!


(when (boundp 'my_robot_move_msgs::Points)
  (if (not (find-package "MY_ROBOT_MOVE_MSGS"))
    (make-package "MY_ROBOT_MOVE_MSGS"))
  (shadow 'Points (find-package "MY_ROBOT_MOVE_MSGS")))
(unless (find-package "MY_ROBOT_MOVE_MSGS::POINTS")
  (make-package "MY_ROBOT_MOVE_MSGS::POINTS"))

(in-package "ROS")
;;//! \htmlinclude Points.msg.html


(defclass my_robot_move_msgs::Points
  :super ros::object
  :slots (_data ))

(defmethod my_robot_move_msgs::Points
  (:init
   (&key
    ((:data __data) ())
    )
   (send-super :init)
   (setq _data __data)
   self)
  (:data
   (&rest __data)
   (if (keywordp (car __data))
       (send* _data __data)
     (progn
       (if __data (setq _data (car __data)))
       _data)))
  (:serialization-length
   ()
   (+
    ;; my_robot_move_msgs/Point[] _data
    (apply #'+ (send-all _data :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; my_robot_move_msgs/Point[] _data
     (write-long (length _data) s)
     (dolist (elem _data)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; my_robot_move_msgs/Point[] _data
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _data (let (r) (dotimes (i n) (push (instance my_robot_move_msgs::Point :init) r)) r))
     (dolist (elem- _data)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get my_robot_move_msgs::Points :md5sum-) "bd8230b572f3a22a16d1166189c29f5b")
(setf (get my_robot_move_msgs::Points :datatype-) "my_robot_move_msgs/Points")
(setf (get my_robot_move_msgs::Points :definition-)
      "Point[] data

================================================================================
MSG: my_robot_move_msgs/Point
float32 x
float32 y
float32 z
float32 rx
float32 ry
float32 rz

")



(provide :my_robot_move_msgs/Points "bd8230b572f3a22a16d1166189c29f5b")


