; Auto-generated. Do not edit!


(cl:in-package my_robot_move_msgs-msg)


;//! \htmlinclude PainterMoveGoal.msg.html

(cl:defclass <PainterMoveGoal> (roslisp-msg-protocol:ros-message)
  ((host
    :reader host
    :initarg :host
    :type cl:string
    :initform "")
   (port
    :reader port
    :initarg :port
    :type cl:integer
    :initform 0)
   (acceleration
    :reader acceleration
    :initarg :acceleration
    :type cl:float
    :initform 0.0)
   (velocity
    :reader velocity
    :initarg :velocity
    :type cl:float
    :initform 0.0)
   (epsilon
    :reader epsilon
    :initarg :epsilon
    :type cl:float
    :initform 0.0)
   (ways
    :reader ways
    :initarg :ways
    :type my_robot_move_msgs-msg:Points
    :initform (cl:make-instance 'my_robot_move_msgs-msg:Points)))
)

(cl:defclass PainterMoveGoal (<PainterMoveGoal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PainterMoveGoal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PainterMoveGoal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name my_robot_move_msgs-msg:<PainterMoveGoal> is deprecated: use my_robot_move_msgs-msg:PainterMoveGoal instead.")))

(cl:ensure-generic-function 'host-val :lambda-list '(m))
(cl:defmethod host-val ((m <PainterMoveGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_robot_move_msgs-msg:host-val is deprecated.  Use my_robot_move_msgs-msg:host instead.")
  (host m))

(cl:ensure-generic-function 'port-val :lambda-list '(m))
(cl:defmethod port-val ((m <PainterMoveGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_robot_move_msgs-msg:port-val is deprecated.  Use my_robot_move_msgs-msg:port instead.")
  (port m))

(cl:ensure-generic-function 'acceleration-val :lambda-list '(m))
(cl:defmethod acceleration-val ((m <PainterMoveGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_robot_move_msgs-msg:acceleration-val is deprecated.  Use my_robot_move_msgs-msg:acceleration instead.")
  (acceleration m))

(cl:ensure-generic-function 'velocity-val :lambda-list '(m))
(cl:defmethod velocity-val ((m <PainterMoveGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_robot_move_msgs-msg:velocity-val is deprecated.  Use my_robot_move_msgs-msg:velocity instead.")
  (velocity m))

(cl:ensure-generic-function 'epsilon-val :lambda-list '(m))
(cl:defmethod epsilon-val ((m <PainterMoveGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_robot_move_msgs-msg:epsilon-val is deprecated.  Use my_robot_move_msgs-msg:epsilon instead.")
  (epsilon m))

(cl:ensure-generic-function 'ways-val :lambda-list '(m))
(cl:defmethod ways-val ((m <PainterMoveGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_robot_move_msgs-msg:ways-val is deprecated.  Use my_robot_move_msgs-msg:ways instead.")
  (ways m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PainterMoveGoal>) ostream)
  "Serializes a message object of type '<PainterMoveGoal>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'host))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'host))
  (cl:let* ((signed (cl:slot-value msg 'port)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'acceleration))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'velocity))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'epsilon))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'ways) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PainterMoveGoal>) istream)
  "Deserializes a message object of type '<PainterMoveGoal>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'host) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'host) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'port) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'acceleration) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'velocity) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'epsilon) (roslisp-utils:decode-single-float-bits bits)))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'ways) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PainterMoveGoal>)))
  "Returns string type for a message object of type '<PainterMoveGoal>"
  "my_robot_move_msgs/PainterMoveGoal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PainterMoveGoal)))
  "Returns string type for a message object of type 'PainterMoveGoal"
  "my_robot_move_msgs/PainterMoveGoal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PainterMoveGoal>)))
  "Returns md5sum for a message object of type '<PainterMoveGoal>"
  "2eaee159032b051f1ffcf20961a0ee4e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PainterMoveGoal)))
  "Returns md5sum for a message object of type 'PainterMoveGoal"
  "2eaee159032b051f1ffcf20961a0ee4e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PainterMoveGoal>)))
  "Returns full string definition for message of type '<PainterMoveGoal>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%string host~%int32 port~%float32 acceleration~%float32 velocity ~%float32 epsilon~%my_robot_move_msgs/Points ways~%~%~%================================================================================~%MSG: my_robot_move_msgs/Points~%Point[] data~%~%================================================================================~%MSG: my_robot_move_msgs/Point~%float32 x~%float32 y~%float32 z~%float32 rx~%float32 ry~%float32 rz~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PainterMoveGoal)))
  "Returns full string definition for message of type 'PainterMoveGoal"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%string host~%int32 port~%float32 acceleration~%float32 velocity ~%float32 epsilon~%my_robot_move_msgs/Points ways~%~%~%================================================================================~%MSG: my_robot_move_msgs/Points~%Point[] data~%~%================================================================================~%MSG: my_robot_move_msgs/Point~%float32 x~%float32 y~%float32 z~%float32 rx~%float32 ry~%float32 rz~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PainterMoveGoal>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'host))
     4
     4
     4
     4
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'ways))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PainterMoveGoal>))
  "Converts a ROS message object to a list"
  (cl:list 'PainterMoveGoal
    (cl:cons ':host (host msg))
    (cl:cons ':port (port msg))
    (cl:cons ':acceleration (acceleration msg))
    (cl:cons ':velocity (velocity msg))
    (cl:cons ':epsilon (epsilon msg))
    (cl:cons ':ways (ways msg))
))
