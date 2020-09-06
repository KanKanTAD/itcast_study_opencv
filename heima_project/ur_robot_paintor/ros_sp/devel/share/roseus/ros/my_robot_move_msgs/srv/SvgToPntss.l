;; Auto-generated. Do not edit!


(when (boundp 'my_robot_move_msgs::SvgToPntss)
  (if (not (find-package "MY_ROBOT_MOVE_MSGS"))
    (make-package "MY_ROBOT_MOVE_MSGS"))
  (shadow 'SvgToPntss (find-package "MY_ROBOT_MOVE_MSGS")))
(unless (find-package "MY_ROBOT_MOVE_MSGS::SVGTOPNTSS")
  (make-package "MY_ROBOT_MOVE_MSGS::SVGTOPNTSS"))
(unless (find-package "MY_ROBOT_MOVE_MSGS::SVGTOPNTSSREQUEST")
  (make-package "MY_ROBOT_MOVE_MSGS::SVGTOPNTSSREQUEST"))
(unless (find-package "MY_ROBOT_MOVE_MSGS::SVGTOPNTSSRESPONSE")
  (make-package "MY_ROBOT_MOVE_MSGS::SVGTOPNTSSRESPONSE"))

(in-package "ROS")





(defclass my_robot_move_msgs::SvgToPntssRequest
  :super ros::object
  :slots (_ori_x _ori_y _ori_z _tran_z _rx _ry _rz _width _height _svg_width _svg_height _svg_pathds ))

(defmethod my_robot_move_msgs::SvgToPntssRequest
  (:init
   (&key
    ((:ori_x __ori_x) 0.0)
    ((:ori_y __ori_y) 0.0)
    ((:ori_z __ori_z) 0.0)
    ((:tran_z __tran_z) 0.0)
    ((:rx __rx) 0.0)
    ((:ry __ry) 0.0)
    ((:rz __rz) 0.0)
    ((:width __width) 0.0)
    ((:height __height) 0.0)
    ((:svg_width __svg_width) 0.0)
    ((:svg_height __svg_height) 0.0)
    ((:svg_pathds __svg_pathds) (let (r) (dotimes (i 0) (push "" r)) r))
    )
   (send-super :init)
   (setq _ori_x (float __ori_x))
   (setq _ori_y (float __ori_y))
   (setq _ori_z (float __ori_z))
   (setq _tran_z (float __tran_z))
   (setq _rx (float __rx))
   (setq _ry (float __ry))
   (setq _rz (float __rz))
   (setq _width (float __width))
   (setq _height (float __height))
   (setq _svg_width (float __svg_width))
   (setq _svg_height (float __svg_height))
   (setq _svg_pathds __svg_pathds)
   self)
  (:ori_x
   (&optional __ori_x)
   (if __ori_x (setq _ori_x __ori_x)) _ori_x)
  (:ori_y
   (&optional __ori_y)
   (if __ori_y (setq _ori_y __ori_y)) _ori_y)
  (:ori_z
   (&optional __ori_z)
   (if __ori_z (setq _ori_z __ori_z)) _ori_z)
  (:tran_z
   (&optional __tran_z)
   (if __tran_z (setq _tran_z __tran_z)) _tran_z)
  (:rx
   (&optional __rx)
   (if __rx (setq _rx __rx)) _rx)
  (:ry
   (&optional __ry)
   (if __ry (setq _ry __ry)) _ry)
  (:rz
   (&optional __rz)
   (if __rz (setq _rz __rz)) _rz)
  (:width
   (&optional __width)
   (if __width (setq _width __width)) _width)
  (:height
   (&optional __height)
   (if __height (setq _height __height)) _height)
  (:svg_width
   (&optional __svg_width)
   (if __svg_width (setq _svg_width __svg_width)) _svg_width)
  (:svg_height
   (&optional __svg_height)
   (if __svg_height (setq _svg_height __svg_height)) _svg_height)
  (:svg_pathds
   (&optional __svg_pathds)
   (if __svg_pathds (setq _svg_pathds __svg_pathds)) _svg_pathds)
  (:serialization-length
   ()
   (+
    ;; float32 _ori_x
    4
    ;; float32 _ori_y
    4
    ;; float32 _ori_z
    4
    ;; float32 _tran_z
    4
    ;; float32 _rx
    4
    ;; float32 _ry
    4
    ;; float32 _rz
    4
    ;; float32 _width
    4
    ;; float32 _height
    4
    ;; float32 _svg_width
    4
    ;; float32 _svg_height
    4
    ;; string[] _svg_pathds
    (apply #'+ (mapcar #'(lambda (x) (+ 4 (length x))) _svg_pathds)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _ori_x
       (sys::poke _ori_x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _ori_y
       (sys::poke _ori_y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _ori_z
       (sys::poke _ori_z (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _tran_z
       (sys::poke _tran_z (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _rx
       (sys::poke _rx (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _ry
       (sys::poke _ry (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _rz
       (sys::poke _rz (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _width
       (sys::poke _width (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _height
       (sys::poke _height (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _svg_width
       (sys::poke _svg_width (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _svg_height
       (sys::poke _svg_height (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; string[] _svg_pathds
     (write-long (length _svg_pathds) s)
     (dolist (elem _svg_pathds)
       (write-long (length elem) s) (princ elem s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _ori_x
     (setq _ori_x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _ori_y
     (setq _ori_y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _ori_z
     (setq _ori_z (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _tran_z
     (setq _tran_z (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _rx
     (setq _rx (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _ry
     (setq _ry (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _rz
     (setq _rz (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _width
     (setq _width (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _height
     (setq _height (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _svg_width
     (setq _svg_width (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _svg_height
     (setq _svg_height (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; string[] _svg_pathds
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _svg_pathds (make-list n))
     (dotimes (i n)
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setf (elt _svg_pathds i) (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
     ))
   ;;
   self)
  )

(defclass my_robot_move_msgs::SvgToPntssResponse
  :super ros::object
  :slots (_pts ))

(defmethod my_robot_move_msgs::SvgToPntssResponse
  (:init
   (&key
    ((:pts __pts) (instance my_robot_move_msgs::Points :init))
    )
   (send-super :init)
   (setq _pts __pts)
   self)
  (:pts
   (&rest __pts)
   (if (keywordp (car __pts))
       (send* _pts __pts)
     (progn
       (if __pts (setq _pts (car __pts)))
       _pts)))
  (:serialization-length
   ()
   (+
    ;; my_robot_move_msgs/Points _pts
    (send _pts :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; my_robot_move_msgs/Points _pts
       (send _pts :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; my_robot_move_msgs/Points _pts
     (send _pts :deserialize buf ptr-) (incf ptr- (send _pts :serialization-length))
   ;;
   self)
  )

(defclass my_robot_move_msgs::SvgToPntss
  :super ros::object
  :slots ())

(setf (get my_robot_move_msgs::SvgToPntss :md5sum-) "60816149316c144de894d769a72c05f1")
(setf (get my_robot_move_msgs::SvgToPntss :datatype-) "my_robot_move_msgs/SvgToPntss")
(setf (get my_robot_move_msgs::SvgToPntss :request) my_robot_move_msgs::SvgToPntssRequest)
(setf (get my_robot_move_msgs::SvgToPntss :response) my_robot_move_msgs::SvgToPntssResponse)

(defmethod my_robot_move_msgs::SvgToPntssRequest
  (:response () (instance my_robot_move_msgs::SvgToPntssResponse :init)))

(setf (get my_robot_move_msgs::SvgToPntssRequest :md5sum-) "60816149316c144de894d769a72c05f1")
(setf (get my_robot_move_msgs::SvgToPntssRequest :datatype-) "my_robot_move_msgs/SvgToPntssRequest")
(setf (get my_robot_move_msgs::SvgToPntssRequest :definition-)
      "float32 ori_x
float32 ori_y
float32 ori_z
float32 tran_z

float32 rx
float32 ry
float32 rz

float32 width
float32 height

float32 svg_width
float32 svg_height
string[] svg_pathds

---

my_robot_move_msgs/Points pts


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

(setf (get my_robot_move_msgs::SvgToPntssResponse :md5sum-) "60816149316c144de894d769a72c05f1")
(setf (get my_robot_move_msgs::SvgToPntssResponse :datatype-) "my_robot_move_msgs/SvgToPntssResponse")
(setf (get my_robot_move_msgs::SvgToPntssResponse :definition-)
      "float32 ori_x
float32 ori_y
float32 ori_z
float32 tran_z

float32 rx
float32 ry
float32 rz

float32 width
float32 height

float32 svg_width
float32 svg_height
string[] svg_pathds

---

my_robot_move_msgs/Points pts


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



(provide :my_robot_move_msgs/SvgToPntss "60816149316c144de894d769a72c05f1")


