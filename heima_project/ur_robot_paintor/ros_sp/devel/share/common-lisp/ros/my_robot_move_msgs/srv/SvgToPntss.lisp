; Auto-generated. Do not edit!


(cl:in-package my_robot_move_msgs-srv)


;//! \htmlinclude SvgToPntss-request.msg.html

(cl:defclass <SvgToPntss-request> (roslisp-msg-protocol:ros-message)
  ((ori_x
    :reader ori_x
    :initarg :ori_x
    :type cl:float
    :initform 0.0)
   (ori_y
    :reader ori_y
    :initarg :ori_y
    :type cl:float
    :initform 0.0)
   (ori_z
    :reader ori_z
    :initarg :ori_z
    :type cl:float
    :initform 0.0)
   (tran_z
    :reader tran_z
    :initarg :tran_z
    :type cl:float
    :initform 0.0)
   (rx
    :reader rx
    :initarg :rx
    :type cl:float
    :initform 0.0)
   (ry
    :reader ry
    :initarg :ry
    :type cl:float
    :initform 0.0)
   (rz
    :reader rz
    :initarg :rz
    :type cl:float
    :initform 0.0)
   (width
    :reader width
    :initarg :width
    :type cl:float
    :initform 0.0)
   (height
    :reader height
    :initarg :height
    :type cl:float
    :initform 0.0)
   (svg_width
    :reader svg_width
    :initarg :svg_width
    :type cl:float
    :initform 0.0)
   (svg_height
    :reader svg_height
    :initarg :svg_height
    :type cl:float
    :initform 0.0)
   (svg_pathds
    :reader svg_pathds
    :initarg :svg_pathds
    :type (cl:vector cl:string)
   :initform (cl:make-array 0 :element-type 'cl:string :initial-element "")))
)

(cl:defclass SvgToPntss-request (<SvgToPntss-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SvgToPntss-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SvgToPntss-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name my_robot_move_msgs-srv:<SvgToPntss-request> is deprecated: use my_robot_move_msgs-srv:SvgToPntss-request instead.")))

(cl:ensure-generic-function 'ori_x-val :lambda-list '(m))
(cl:defmethod ori_x-val ((m <SvgToPntss-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_robot_move_msgs-srv:ori_x-val is deprecated.  Use my_robot_move_msgs-srv:ori_x instead.")
  (ori_x m))

(cl:ensure-generic-function 'ori_y-val :lambda-list '(m))
(cl:defmethod ori_y-val ((m <SvgToPntss-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_robot_move_msgs-srv:ori_y-val is deprecated.  Use my_robot_move_msgs-srv:ori_y instead.")
  (ori_y m))

(cl:ensure-generic-function 'ori_z-val :lambda-list '(m))
(cl:defmethod ori_z-val ((m <SvgToPntss-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_robot_move_msgs-srv:ori_z-val is deprecated.  Use my_robot_move_msgs-srv:ori_z instead.")
  (ori_z m))

(cl:ensure-generic-function 'tran_z-val :lambda-list '(m))
(cl:defmethod tran_z-val ((m <SvgToPntss-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_robot_move_msgs-srv:tran_z-val is deprecated.  Use my_robot_move_msgs-srv:tran_z instead.")
  (tran_z m))

(cl:ensure-generic-function 'rx-val :lambda-list '(m))
(cl:defmethod rx-val ((m <SvgToPntss-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_robot_move_msgs-srv:rx-val is deprecated.  Use my_robot_move_msgs-srv:rx instead.")
  (rx m))

(cl:ensure-generic-function 'ry-val :lambda-list '(m))
(cl:defmethod ry-val ((m <SvgToPntss-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_robot_move_msgs-srv:ry-val is deprecated.  Use my_robot_move_msgs-srv:ry instead.")
  (ry m))

(cl:ensure-generic-function 'rz-val :lambda-list '(m))
(cl:defmethod rz-val ((m <SvgToPntss-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_robot_move_msgs-srv:rz-val is deprecated.  Use my_robot_move_msgs-srv:rz instead.")
  (rz m))

(cl:ensure-generic-function 'width-val :lambda-list '(m))
(cl:defmethod width-val ((m <SvgToPntss-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_robot_move_msgs-srv:width-val is deprecated.  Use my_robot_move_msgs-srv:width instead.")
  (width m))

(cl:ensure-generic-function 'height-val :lambda-list '(m))
(cl:defmethod height-val ((m <SvgToPntss-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_robot_move_msgs-srv:height-val is deprecated.  Use my_robot_move_msgs-srv:height instead.")
  (height m))

(cl:ensure-generic-function 'svg_width-val :lambda-list '(m))
(cl:defmethod svg_width-val ((m <SvgToPntss-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_robot_move_msgs-srv:svg_width-val is deprecated.  Use my_robot_move_msgs-srv:svg_width instead.")
  (svg_width m))

(cl:ensure-generic-function 'svg_height-val :lambda-list '(m))
(cl:defmethod svg_height-val ((m <SvgToPntss-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_robot_move_msgs-srv:svg_height-val is deprecated.  Use my_robot_move_msgs-srv:svg_height instead.")
  (svg_height m))

(cl:ensure-generic-function 'svg_pathds-val :lambda-list '(m))
(cl:defmethod svg_pathds-val ((m <SvgToPntss-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_robot_move_msgs-srv:svg_pathds-val is deprecated.  Use my_robot_move_msgs-srv:svg_pathds instead.")
  (svg_pathds m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SvgToPntss-request>) ostream)
  "Serializes a message object of type '<SvgToPntss-request>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'ori_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'ori_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'ori_z))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'tran_z))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'rx))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'ry))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'rz))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'width))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'height))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'svg_width))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'svg_height))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'svg_pathds))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((__ros_str_len (cl:length ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) ele))
   (cl:slot-value msg 'svg_pathds))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SvgToPntss-request>) istream)
  "Deserializes a message object of type '<SvgToPntss-request>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ori_x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ori_y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ori_z) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'tran_z) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'rx) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ry) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'rz) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'width) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'height) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'svg_width) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'svg_height) (roslisp-utils:decode-single-float-bits bits)))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'svg_pathds) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'svg_pathds)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:aref vals i) __ros_str_idx) (cl:code-char (cl:read-byte istream))))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SvgToPntss-request>)))
  "Returns string type for a service object of type '<SvgToPntss-request>"
  "my_robot_move_msgs/SvgToPntssRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SvgToPntss-request)))
  "Returns string type for a service object of type 'SvgToPntss-request"
  "my_robot_move_msgs/SvgToPntssRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SvgToPntss-request>)))
  "Returns md5sum for a message object of type '<SvgToPntss-request>"
  "60816149316c144de894d769a72c05f1")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SvgToPntss-request)))
  "Returns md5sum for a message object of type 'SvgToPntss-request"
  "60816149316c144de894d769a72c05f1")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SvgToPntss-request>)))
  "Returns full string definition for message of type '<SvgToPntss-request>"
  (cl:format cl:nil "float32 ori_x~%float32 ori_y~%float32 ori_z~%float32 tran_z~%~%float32 rx~%float32 ry~%float32 rz~%~%float32 width~%float32 height~%~%float32 svg_width~%float32 svg_height~%string[] svg_pathds~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SvgToPntss-request)))
  "Returns full string definition for message of type 'SvgToPntss-request"
  (cl:format cl:nil "float32 ori_x~%float32 ori_y~%float32 ori_z~%float32 tran_z~%~%float32 rx~%float32 ry~%float32 rz~%~%float32 width~%float32 height~%~%float32 svg_width~%float32 svg_height~%string[] svg_pathds~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SvgToPntss-request>))
  (cl:+ 0
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'svg_pathds) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4 (cl:length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SvgToPntss-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SvgToPntss-request
    (cl:cons ':ori_x (ori_x msg))
    (cl:cons ':ori_y (ori_y msg))
    (cl:cons ':ori_z (ori_z msg))
    (cl:cons ':tran_z (tran_z msg))
    (cl:cons ':rx (rx msg))
    (cl:cons ':ry (ry msg))
    (cl:cons ':rz (rz msg))
    (cl:cons ':width (width msg))
    (cl:cons ':height (height msg))
    (cl:cons ':svg_width (svg_width msg))
    (cl:cons ':svg_height (svg_height msg))
    (cl:cons ':svg_pathds (svg_pathds msg))
))
;//! \htmlinclude SvgToPntss-response.msg.html

(cl:defclass <SvgToPntss-response> (roslisp-msg-protocol:ros-message)
  ((pts
    :reader pts
    :initarg :pts
    :type my_robot_move_msgs-msg:Points
    :initform (cl:make-instance 'my_robot_move_msgs-msg:Points)))
)

(cl:defclass SvgToPntss-response (<SvgToPntss-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SvgToPntss-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SvgToPntss-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name my_robot_move_msgs-srv:<SvgToPntss-response> is deprecated: use my_robot_move_msgs-srv:SvgToPntss-response instead.")))

(cl:ensure-generic-function 'pts-val :lambda-list '(m))
(cl:defmethod pts-val ((m <SvgToPntss-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_robot_move_msgs-srv:pts-val is deprecated.  Use my_robot_move_msgs-srv:pts instead.")
  (pts m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SvgToPntss-response>) ostream)
  "Serializes a message object of type '<SvgToPntss-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'pts) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SvgToPntss-response>) istream)
  "Deserializes a message object of type '<SvgToPntss-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'pts) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SvgToPntss-response>)))
  "Returns string type for a service object of type '<SvgToPntss-response>"
  "my_robot_move_msgs/SvgToPntssResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SvgToPntss-response)))
  "Returns string type for a service object of type 'SvgToPntss-response"
  "my_robot_move_msgs/SvgToPntssResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SvgToPntss-response>)))
  "Returns md5sum for a message object of type '<SvgToPntss-response>"
  "60816149316c144de894d769a72c05f1")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SvgToPntss-response)))
  "Returns md5sum for a message object of type 'SvgToPntss-response"
  "60816149316c144de894d769a72c05f1")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SvgToPntss-response>)))
  "Returns full string definition for message of type '<SvgToPntss-response>"
  (cl:format cl:nil "~%my_robot_move_msgs/Points pts~%~%~%================================================================================~%MSG: my_robot_move_msgs/Points~%Point[] data~%~%================================================================================~%MSG: my_robot_move_msgs/Point~%float32 x~%float32 y~%float32 z~%float32 rx~%float32 ry~%float32 rz~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SvgToPntss-response)))
  "Returns full string definition for message of type 'SvgToPntss-response"
  (cl:format cl:nil "~%my_robot_move_msgs/Points pts~%~%~%================================================================================~%MSG: my_robot_move_msgs/Points~%Point[] data~%~%================================================================================~%MSG: my_robot_move_msgs/Point~%float32 x~%float32 y~%float32 z~%float32 rx~%float32 ry~%float32 rz~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SvgToPntss-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'pts))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SvgToPntss-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SvgToPntss-response
    (cl:cons ':pts (pts msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SvgToPntss)))
  'SvgToPntss-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SvgToPntss)))
  'SvgToPntss-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SvgToPntss)))
  "Returns string type for a service object of type '<SvgToPntss>"
  "my_robot_move_msgs/SvgToPntss")