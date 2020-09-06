;; Auto-generated. Do not edit!


(when (boundp 'my_robot_move_msgs::Pointss)
  (if (not (find-package "MY_ROBOT_MOVE_MSGS"))
    (make-package "MY_ROBOT_MOVE_MSGS"))
  (shadow 'Pointss (find-package "MY_ROBOT_MOVE_MSGS")))
(unless (find-package "MY_ROBOT_MOVE_MSGS::POINTSS")
  (make-package "MY_ROBOT_MOVE_MSGS::POINTSS"))

(in-package "ROS")
;;//! \htmlinclude Pointss.msg.html


(defclass my_robot_move_msgs::Pointss
  :super ros::object
  :slots (_data ))

(defmethod my_robot_move_msgs::Pointss
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
    ;; my_robot_move_msgs/Points[] _data
    (apply #'+ (send-all _data :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; my_robot_move_msgs/Points[] _data
     (write-long (length _data) s)
     (dolist (elem _data)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; my_robot_move_msgs/Points[] _data
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _data (let (r) (dotimes (i n) (push (instance my_robot_move_msgs::Points :init) r)) r))
     (dolist (elem- _data)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get my_robot_move_msgs::Pointss :md5sum-) "252224edcc17c0fb24b03717a7beba36")
(setf (get my_robot_move_msgs::Pointss :datatype-) "my_robot_move_msgs/Pointss")
(setf (get my_robot_move_msgs::Pointss :definition-)
      "Points[] data

================================================================================
MSG: my_robot_move_msgs/Points
Point[] data

================================================================================
MSG: my_robot_move_msgs/Point
float32 x
float32 y
float32 z
float32 rx
float32 ry
float32 rz

")



(provide :my_robot_move_msgs/Pointss "252224edcc17c0fb24b03717a7beba36")


