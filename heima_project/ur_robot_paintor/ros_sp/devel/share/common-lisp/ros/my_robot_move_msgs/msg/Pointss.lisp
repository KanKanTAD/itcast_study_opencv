; Auto-generated. Do not edit!


(cl:in-package my_robot_move_msgs-msg)


;//! \htmlinclude Pointss.msg.html

(cl:defclass <Pointss> (roslisp-msg-protocol:ros-message)
  ((data
    :reader data
    :initarg :data
    :type (cl:vector my_robot_move_msgs-msg:Points)
   :initform (cl:make-array 0 :element-type 'my_robot_move_msgs-msg:Points :initial-element (cl:make-instance 'my_robot_move_msgs-msg:Points))))
)

(cl:defclass Pointss (<Pointss>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Pointss>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Pointss)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name my_robot_move_msgs-msg:<Pointss> is deprecated: use my_robot_move_msgs-msg:Pointss instead.")))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <Pointss>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_robot_move_msgs-msg:data-val is deprecated.  Use my_robot_move_msgs-msg:data instead.")
  (data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Pointss>) ostream)
  "Serializes a message object of type '<Pointss>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'data))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'data))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Pointss>) istream)
  "Deserializes a message object of type '<Pointss>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'data) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'data)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'my_robot_move_msgs-msg:Points))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Pointss>)))
  "Returns string type for a message object of type '<Pointss>"
  "my_robot_move_msgs/Pointss")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Pointss)))
  "Returns string type for a message object of type 'Pointss"
  "my_robot_move_msgs/Pointss")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Pointss>)))
  "Returns md5sum for a message object of type '<Pointss>"
  "252224edcc17c0fb24b03717a7beba36")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Pointss)))
  "Returns md5sum for a message object of type 'Pointss"
  "252224edcc17c0fb24b03717a7beba36")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Pointss>)))
  "Returns full string definition for message of type '<Pointss>"
  (cl:format cl:nil "Points[] data~%~%================================================================================~%MSG: my_robot_move_msgs/Points~%Point[] data~%~%================================================================================~%MSG: my_robot_move_msgs/Point~%float32 x~%float32 y~%float32 z~%float32 rx~%float32 ry~%float32 rz~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Pointss)))
  "Returns full string definition for message of type 'Pointss"
  (cl:format cl:nil "Points[] data~%~%================================================================================~%MSG: my_robot_move_msgs/Points~%Point[] data~%~%================================================================================~%MSG: my_robot_move_msgs/Point~%float32 x~%float32 y~%float32 z~%float32 rx~%float32 ry~%float32 rz~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Pointss>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'data) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Pointss>))
  "Converts a ROS message object to a list"
  (cl:list 'Pointss
    (cl:cons ':data (data msg))
))
