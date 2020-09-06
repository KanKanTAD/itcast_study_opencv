; Auto-generated. Do not edit!


(cl:in-package my_robot_move_msgs-msg)


;//! \htmlinclude Points.msg.html

(cl:defclass <Points> (roslisp-msg-protocol:ros-message)
  ((data
    :reader data
    :initarg :data
    :type (cl:vector my_robot_move_msgs-msg:Point)
   :initform (cl:make-array 0 :element-type 'my_robot_move_msgs-msg:Point :initial-element (cl:make-instance 'my_robot_move_msgs-msg:Point))))
)

(cl:defclass Points (<Points>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Points>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Points)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name my_robot_move_msgs-msg:<Points> is deprecated: use my_robot_move_msgs-msg:Points instead.")))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <Points>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_robot_move_msgs-msg:data-val is deprecated.  Use my_robot_move_msgs-msg:data instead.")
  (data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Points>) ostream)
  "Serializes a message object of type '<Points>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'data))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'data))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Points>) istream)
  "Deserializes a message object of type '<Points>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'data) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'data)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'my_robot_move_msgs-msg:Point))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Points>)))
  "Returns string type for a message object of type '<Points>"
  "my_robot_move_msgs/Points")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Points)))
  "Returns string type for a message object of type 'Points"
  "my_robot_move_msgs/Points")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Points>)))
  "Returns md5sum for a message object of type '<Points>"
  "bd8230b572f3a22a16d1166189c29f5b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Points)))
  "Returns md5sum for a message object of type 'Points"
  "bd8230b572f3a22a16d1166189c29f5b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Points>)))
  "Returns full string definition for message of type '<Points>"
  (cl:format cl:nil "Point[] data~%~%================================================================================~%MSG: my_robot_move_msgs/Point~%float32 x~%float32 y~%float32 z~%float32 rx~%float32 ry~%float32 rz~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Points)))
  "Returns full string definition for message of type 'Points"
  (cl:format cl:nil "Point[] data~%~%================================================================================~%MSG: my_robot_move_msgs/Point~%float32 x~%float32 y~%float32 z~%float32 rx~%float32 ry~%float32 rz~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Points>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'data) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Points>))
  "Converts a ROS message object to a list"
  (cl:list 'Points
    (cl:cons ':data (data msg))
))
