;; Auto-generated. Do not edit!


(when (boundp 'my_robot_move_msgs::PainterMoveResult)
  (if (not (find-package "MY_ROBOT_MOVE_MSGS"))
    (make-package "MY_ROBOT_MOVE_MSGS"))
  (shadow 'PainterMoveResult (find-package "MY_ROBOT_MOVE_MSGS")))
(unless (find-package "MY_ROBOT_MOVE_MSGS::PAINTERMOVERESULT")
  (make-package "MY_ROBOT_MOVE_MSGS::PAINTERMOVERESULT"))

(in-package "ROS")
;;//! \htmlinclude PainterMoveResult.msg.html


(defclass my_robot_move_msgs::PainterMoveResult
  :super ros::object
  :slots (_code _result ))

(defmethod my_robot_move_msgs::PainterMoveResult
  (:init
   (&key
    ((:code __code) 0)
    ((:result __result) "")
    )
   (send-super :init)
   (setq _code (round __code))
   (setq _result (string __result))
   self)
  (:code
   (&optional __code)
   (if __code (setq _code __code)) _code)
  (:result
   (&optional __result)
   (if __result (setq _result __result)) _result)
  (:serialization-length
   ()
   (+
    ;; int32 _code
    4
    ;; string _result
    4 (length _result)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _code
       (write-long _code s)
     ;; string _result
       (write-long (length _result) s) (princ _result s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _code
     (setq _code (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; string _result
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _result (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(setf (get my_robot_move_msgs::PainterMoveResult :md5sum-) "2051888b170a61395fcf548db198dcfa")
(setf (get my_robot_move_msgs::PainterMoveResult :datatype-) "my_robot_move_msgs/PainterMoveResult")
(setf (get my_robot_move_msgs::PainterMoveResult :definition-)
      "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======

int32 code
string result


")



(provide :my_robot_move_msgs/PainterMoveResult "2051888b170a61395fcf548db198dcfa")

