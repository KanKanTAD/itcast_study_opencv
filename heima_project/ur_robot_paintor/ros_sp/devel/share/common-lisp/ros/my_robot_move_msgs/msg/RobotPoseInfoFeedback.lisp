; Auto-generated. Do not edit!


(cl:in-package my_robot_move_msgs-msg)


;//! \htmlinclude RobotPoseInfoFeedback.msg.html

(cl:defclass <RobotPoseInfoFeedback> (roslisp-msg-protocol:ros-message)
  ((code
    :reader code
    :initarg :code
    :type cl:integer
    :initform 0)
   (info
    :reader info
    :initarg :info
    :type cl:string
    :initform "")
   (pose
    :reader pose
    :initarg :pose
    :type my_robot_move_msgs-msg:Point
    :initform (cl:make-instance 'my_robot_move_msgs-msg:Point)))
)

(cl:defclass RobotPoseInfoFeedback (<RobotPoseInfoFeedback>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <RobotPoseInfoFeedback>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'RobotPoseInfoFeedback)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name my_robot_move_msgs-msg:<RobotPoseInfoFeedback> is deprecated: use my_robot_move_msgs-msg:RobotPoseInfoFeedback instead.")))

(cl:ensure-generic-function 'code-val :lambda-list '(m))
(cl:defmethod code-val ((m <RobotPoseInfoFeedback>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_robot_move_msgs-msg:code-val is deprecated.  Use my_robot_move_msgs-msg:code instead.")
  (code m))

(cl:ensure-generic-function 'info-val :lambda-list '(m))
(cl:defmethod info-val ((m <RobotPoseInfoFeedback>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_robot_move_msgs-msg:info-val is deprecated.  Use my_robot_move_msgs-msg:info instead.")
  (info m))

(cl:ensure-generic-function 'pose-val :lambda-list '(m))
(cl:defmethod pose-val ((m <RobotPoseInfoFeedback>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_robot_move_msgs-msg:pose-val is deprecated.  Use my_robot_move_msgs-msg:pose instead.")
  (pose m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <RobotPoseInfoFeedback>) ostream)
  "Serializes a message object of type '<RobotPoseInfoFeedback>"
  (cl:let* ((signed (cl:slot-value msg 'code)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'info))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'info))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'pose) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <RobotPoseInfoFeedback>) istream)
  "Deserializes a message object of type '<RobotPoseInfoFeedback>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'code) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'info) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'info) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'pose) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<RobotPoseInfoFeedback>)))
  "Returns string type for a message object of type '<RobotPoseInfoFeedback>"
  "my_robot_move_msgs/RobotPoseInfoFeedback")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RobotPoseInfoFeedback)))
  "Returns string type for a message object of type 'RobotPoseInfoFeedback"
  "my_robot_move_msgs/RobotPoseInfoFeedback")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<RobotPoseInfoFeedback>)))
  "Returns md5sum for a message object of type '<RobotPoseInfoFeedback>"
  "9b7495d158609a11ddc10b55aa965269")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'RobotPoseInfoFeedback)))
  "Returns md5sum for a message object of type 'RobotPoseInfoFeedback"
  "9b7495d158609a11ddc10b55aa965269")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<RobotPoseInfoFeedback>)))
  "Returns full string definition for message of type '<RobotPoseInfoFeedback>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%~%int32 code~%string info~%my_robot_move_msgs/Point pose~%~%~%~%~%~%================================================================================~%MSG: my_robot_move_msgs/Point~%float32 x~%float32 y~%float32 z~%float32 rx~%float32 ry~%float32 rz~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'RobotPoseInfoFeedback)))
  "Returns full string definition for message of type 'RobotPoseInfoFeedback"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%~%int32 code~%string info~%my_robot_move_msgs/Point pose~%~%~%~%~%~%================================================================================~%MSG: my_robot_move_msgs/Point~%float32 x~%float32 y~%float32 z~%float32 rx~%float32 ry~%float32 rz~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <RobotPoseInfoFeedback>))
  (cl:+ 0
     4
     4 (cl:length (cl:slot-value msg 'info))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'pose))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <RobotPoseInfoFeedback>))
  "Converts a ROS message object to a list"
  (cl:list 'RobotPoseInfoFeedback
    (cl:cons ':code (code msg))
    (cl:cons ':info (info msg))
    (cl:cons ':pose (pose msg))
))
