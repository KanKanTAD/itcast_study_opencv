
(cl:in-package :asdf)

(defsystem "my_robot_move_msgs-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :my_robot_move_msgs-msg
)
  :components ((:file "_package")
    (:file "SvgToPntss" :depends-on ("_package_SvgToPntss"))
    (:file "_package_SvgToPntss" :depends-on ("_package"))
  ))