
(cl:in-package :asdf)

(defsystem "my_robot_move_actions-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :actionlib_msgs-msg
               :my_robot_move_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "PainterMoveAction" :depends-on ("_package_PainterMoveAction"))
    (:file "_package_PainterMoveAction" :depends-on ("_package"))
    (:file "PainterMoveActionFeedback" :depends-on ("_package_PainterMoveActionFeedback"))
    (:file "_package_PainterMoveActionFeedback" :depends-on ("_package"))
    (:file "PainterMoveActionGoal" :depends-on ("_package_PainterMoveActionGoal"))
    (:file "_package_PainterMoveActionGoal" :depends-on ("_package"))
    (:file "PainterMoveActionResult" :depends-on ("_package_PainterMoveActionResult"))
    (:file "_package_PainterMoveActionResult" :depends-on ("_package"))
    (:file "PainterMoveFeedback" :depends-on ("_package_PainterMoveFeedback"))
    (:file "_package_PainterMoveFeedback" :depends-on ("_package"))
    (:file "PainterMoveGoal" :depends-on ("_package_PainterMoveGoal"))
    (:file "_package_PainterMoveGoal" :depends-on ("_package"))
    (:file "PainterMoveResult" :depends-on ("_package_PainterMoveResult"))
    (:file "_package_PainterMoveResult" :depends-on ("_package"))
  ))