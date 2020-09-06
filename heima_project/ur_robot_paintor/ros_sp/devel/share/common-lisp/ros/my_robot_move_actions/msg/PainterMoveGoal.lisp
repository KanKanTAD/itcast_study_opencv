; Auto-generated. Do not edit!


(cl:in-package my_robot_move_actions-msg)


;//! \htmlinclude PainterMoveGoal.msg.html

(cl:defclass <PainterMoveGoal> (roslisp-msg-protocol:ros-message)
  ((acceleration
    :reader acceleration
    :initarg :acceleration
    :type cl:float
    :initform 0.0)
   (velocity
    :reader velocity
    :initarg :velocity
    :type cl:float
    :initform 0.0)
   (z_coef
    :reader z_coef
    :initarg :z_coef
    :type cl:float
    :initform 0.0)
   (ways
    :reader ways
    :initarg :ways
    :type my_robot_move_msgs-msg:Pointss
    :initform (cl:make-instance 'my_robot_move_msgs-msg:Pointss)))
)

(cl:defclass PainterMoveGoal (<PainterMoveGoal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PainterMoveGoal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PainterMoveGoal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name my_robot_move_actions-msg:<PainterMoveGoal> is deprecated: use my_robot_move_actions-msg:PainterMoveGoal instead.")))

(cl:ensure-generic-function 'acceleration-val :lambda-list '(m))
(cl:defmethod acceleration-val ((m <PainterMoveGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_robot_move_actions-msg:acceleration-val is deprecated.  Use my_robot_move_actions-msg:acceleration instead.")
  (acceleration m))

(cl:ensure-generic-function 'velocity-val :lambda-list '(m))
(cl:defmethod velocity-val ((m <PainterMoveGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_robot_move_actions-msg:velocity-val is deprecated.  Use my_robot_move_actions-msg:velocity instead.")
  (velocity m))

(cl:ensure-generic-function 'z_coef-val :lambda-list '(m))
(cl:defmethod z_coef-val ((m <PainterMoveGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_robot_move_actions-msg:z_coef-val is deprecated.  Use my_robot_move_actions-msg:z_coef instead.")
  (z_coef m))

(cl:ensure-generic-function 'ways-val :lambda-list '(m))
(cl:defmethod ways-val ((m <PainterMoveGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_robot_move_actions-msg:ways-val is deprecated.  Use my_robot_move_actions-msg:ways instead.")
  (ways m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PainterMoveGoal>) ostream)
  "Serializes a message object of type '<PainterMoveGoal>"
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
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'z_coef))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'ways) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PainterMoveGoal>) istream)
  "Deserializes a message object of type '<PainterMoveGoal>"
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
    (cl:setf (cl:slot-value msg 'z_coef) (roslisp-utils:decode-single-float-bits bits)))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'ways) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PainterMoveGoal>)))
  "Returns string type for a message object of type '<PainterMoveGoal>"
  "my_robot_move_actions/PainterMoveGoal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PainterMoveGoal)))
  "Returns string type for a message object of type 'PainterMoveGoal"
  "my_robot_move_actions/PainterMoveGoal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PainterMoveGoal>)))
  "Returns md5sum for a message object of type '<PainterMoveGoal>"
  "a335a4998eb8ceb23d4bb2646fae6a2a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PainterMoveGoal)))
  "Returns md5sum for a message object of type 'PainterMoveGoal"
  "a335a4998eb8ceb23d4bb2646fae6a2a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PainterMoveGoal>)))
  "Returns full string definition for message of type '<PainterMoveGoal>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%float32 acceleration~%float32 velocity ~%float32 z_coef~%my_robot_move_msgs/Pointss ways~%~%================================================================================~%MSG: my_robot_move_msgs/Pointss~%Points[] data~%~%================================================================================~%MSG: my_robot_move_msgs/Points~%Point[] data~%~%================================================================================~%MSG: my_robot_move_msgs/Point~%float32 x~%float32 y~%float32 z~%float32 rx~%float32 ry~%float32 rz~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PainterMoveGoal)))
  "Returns full string definition for message of type 'PainterMoveGoal"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%float32 acceleration~%float32 velocity ~%float32 z_coef~%my_robot_move_msgs/Pointss ways~%~%================================================================================~%MSG: my_robot_move_msgs/Pointss~%Points[] data~%~%================================================================================~%MSG: my_robot_move_msgs/Points~%Point[] data~%~%================================================================================~%MSG: my_robot_move_msgs/Point~%float32 x~%float32 y~%float32 z~%float32 rx~%float32 ry~%float32 rz~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PainterMoveGoal>))
  (cl:+ 0
     4
     4
     4
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'ways))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PainterMoveGoal>))
  "Converts a ROS message object to a list"
  (cl:list 'PainterMoveGoal
    (cl:cons ':acceleration (acceleration msg))
    (cl:cons ':velocity (velocity msg))
    (cl:cons ':z_coef (z_coef msg))
    (cl:cons ':ways (ways msg))
))
