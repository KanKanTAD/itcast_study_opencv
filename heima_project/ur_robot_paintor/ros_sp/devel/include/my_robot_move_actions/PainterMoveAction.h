// Generated by gencpp from file my_robot_move_actions/PainterMoveAction.msg
// DO NOT EDIT!


#ifndef MY_ROBOT_MOVE_ACTIONS_MESSAGE_PAINTERMOVEACTION_H
#define MY_ROBOT_MOVE_ACTIONS_MESSAGE_PAINTERMOVEACTION_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <my_robot_move_actions/PainterMoveActionGoal.h>
#include <my_robot_move_actions/PainterMoveActionResult.h>
#include <my_robot_move_actions/PainterMoveActionFeedback.h>

namespace my_robot_move_actions
{
template <class ContainerAllocator>
struct PainterMoveAction_
{
  typedef PainterMoveAction_<ContainerAllocator> Type;

  PainterMoveAction_()
    : action_goal()
    , action_result()
    , action_feedback()  {
    }
  PainterMoveAction_(const ContainerAllocator& _alloc)
    : action_goal(_alloc)
    , action_result(_alloc)
    , action_feedback(_alloc)  {
  (void)_alloc;
    }



   typedef  ::my_robot_move_actions::PainterMoveActionGoal_<ContainerAllocator>  _action_goal_type;
  _action_goal_type action_goal;

   typedef  ::my_robot_move_actions::PainterMoveActionResult_<ContainerAllocator>  _action_result_type;
  _action_result_type action_result;

   typedef  ::my_robot_move_actions::PainterMoveActionFeedback_<ContainerAllocator>  _action_feedback_type;
  _action_feedback_type action_feedback;





  typedef boost::shared_ptr< ::my_robot_move_actions::PainterMoveAction_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::my_robot_move_actions::PainterMoveAction_<ContainerAllocator> const> ConstPtr;

}; // struct PainterMoveAction_

typedef ::my_robot_move_actions::PainterMoveAction_<std::allocator<void> > PainterMoveAction;

typedef boost::shared_ptr< ::my_robot_move_actions::PainterMoveAction > PainterMoveActionPtr;
typedef boost::shared_ptr< ::my_robot_move_actions::PainterMoveAction const> PainterMoveActionConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::my_robot_move_actions::PainterMoveAction_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::my_robot_move_actions::PainterMoveAction_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::my_robot_move_actions::PainterMoveAction_<ContainerAllocator1> & lhs, const ::my_robot_move_actions::PainterMoveAction_<ContainerAllocator2> & rhs)
{
  return lhs.action_goal == rhs.action_goal &&
    lhs.action_result == rhs.action_result &&
    lhs.action_feedback == rhs.action_feedback;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::my_robot_move_actions::PainterMoveAction_<ContainerAllocator1> & lhs, const ::my_robot_move_actions::PainterMoveAction_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace my_robot_move_actions

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::my_robot_move_actions::PainterMoveAction_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::my_robot_move_actions::PainterMoveAction_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::my_robot_move_actions::PainterMoveAction_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::my_robot_move_actions::PainterMoveAction_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::my_robot_move_actions::PainterMoveAction_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::my_robot_move_actions::PainterMoveAction_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::my_robot_move_actions::PainterMoveAction_<ContainerAllocator> >
{
  static const char* value()
  {
    return "eb61653dd1bd2eb9b161497bd46daa38";
  }

  static const char* value(const ::my_robot_move_actions::PainterMoveAction_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xeb61653dd1bd2eb9ULL;
  static const uint64_t static_value2 = 0xb161497bd46daa38ULL;
};

template<class ContainerAllocator>
struct DataType< ::my_robot_move_actions::PainterMoveAction_<ContainerAllocator> >
{
  static const char* value()
  {
    return "my_robot_move_actions/PainterMoveAction";
  }

  static const char* value(const ::my_robot_move_actions::PainterMoveAction_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::my_robot_move_actions::PainterMoveAction_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"\n"
"PainterMoveActionGoal action_goal\n"
"PainterMoveActionResult action_result\n"
"PainterMoveActionFeedback action_feedback\n"
"\n"
"================================================================================\n"
"MSG: my_robot_move_actions/PainterMoveActionGoal\n"
"# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"\n"
"Header header\n"
"actionlib_msgs/GoalID goal_id\n"
"PainterMoveGoal goal\n"
"\n"
"================================================================================\n"
"MSG: std_msgs/Header\n"
"# Standard metadata for higher-level stamped data types.\n"
"# This is generally used to communicate timestamped data \n"
"# in a particular coordinate frame.\n"
"# \n"
"# sequence ID: consecutively increasing ID \n"
"uint32 seq\n"
"#Two-integer timestamp that is expressed as:\n"
"# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n"
"# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n"
"# time-handling sugar is provided by the client library\n"
"time stamp\n"
"#Frame this data is associated with\n"
"string frame_id\n"
"\n"
"================================================================================\n"
"MSG: actionlib_msgs/GoalID\n"
"# The stamp should store the time at which this goal was requested.\n"
"# It is used by an action server when it tries to preempt all\n"
"# goals that were requested before a certain time\n"
"time stamp\n"
"\n"
"# The id provides a way to associate feedback and\n"
"# result message with specific goal requests. The id\n"
"# specified must be unique.\n"
"string id\n"
"\n"
"\n"
"================================================================================\n"
"MSG: my_robot_move_actions/PainterMoveGoal\n"
"# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"float32 acceleration\n"
"float32 velocity \n"
"float32 z_coef\n"
"my_robot_move_msgs/Pointss ways\n"
"\n"
"================================================================================\n"
"MSG: my_robot_move_msgs/Pointss\n"
"Points[] data\n"
"\n"
"================================================================================\n"
"MSG: my_robot_move_msgs/Points\n"
"Point[] data\n"
"\n"
"================================================================================\n"
"MSG: my_robot_move_msgs/Point\n"
"float32 x\n"
"float32 y\n"
"float32 z\n"
"float32 rx\n"
"float32 ry\n"
"float32 rz\n"
"\n"
"================================================================================\n"
"MSG: my_robot_move_actions/PainterMoveActionResult\n"
"# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"\n"
"Header header\n"
"actionlib_msgs/GoalStatus status\n"
"PainterMoveResult result\n"
"\n"
"================================================================================\n"
"MSG: actionlib_msgs/GoalStatus\n"
"GoalID goal_id\n"
"uint8 status\n"
"uint8 PENDING         = 0   # The goal has yet to be processed by the action server\n"
"uint8 ACTIVE          = 1   # The goal is currently being processed by the action server\n"
"uint8 PREEMPTED       = 2   # The goal received a cancel request after it started executing\n"
"                            #   and has since completed its execution (Terminal State)\n"
"uint8 SUCCEEDED       = 3   # The goal was achieved successfully by the action server (Terminal State)\n"
"uint8 ABORTED         = 4   # The goal was aborted during execution by the action server due\n"
"                            #    to some failure (Terminal State)\n"
"uint8 REJECTED        = 5   # The goal was rejected by the action server without being processed,\n"
"                            #    because the goal was unattainable or invalid (Terminal State)\n"
"uint8 PREEMPTING      = 6   # The goal received a cancel request after it started executing\n"
"                            #    and has not yet completed execution\n"
"uint8 RECALLING       = 7   # The goal received a cancel request before it started executing,\n"
"                            #    but the action server has not yet confirmed that the goal is canceled\n"
"uint8 RECALLED        = 8   # The goal received a cancel request before it started executing\n"
"                            #    and was successfully cancelled (Terminal State)\n"
"uint8 LOST            = 9   # An action client can determine that a goal is LOST. This should not be\n"
"                            #    sent over the wire by an action server\n"
"\n"
"#Allow for the user to associate a string with GoalStatus for debugging\n"
"string text\n"
"\n"
"\n"
"================================================================================\n"
"MSG: my_robot_move_actions/PainterMoveResult\n"
"# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"\n"
"int32 code\n"
"float32 percent\n"
"\n"
"\n"
"================================================================================\n"
"MSG: my_robot_move_actions/PainterMoveActionFeedback\n"
"# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"\n"
"Header header\n"
"actionlib_msgs/GoalStatus status\n"
"PainterMoveFeedback feedback\n"
"\n"
"================================================================================\n"
"MSG: my_robot_move_actions/PainterMoveFeedback\n"
"# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"\n"
"my_robot_move_msgs/Point current_pose\n"
"float32 percent\n"
"\n"
"\n"
;
  }

  static const char* value(const ::my_robot_move_actions::PainterMoveAction_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::my_robot_move_actions::PainterMoveAction_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.action_goal);
      stream.next(m.action_result);
      stream.next(m.action_feedback);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct PainterMoveAction_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::my_robot_move_actions::PainterMoveAction_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::my_robot_move_actions::PainterMoveAction_<ContainerAllocator>& v)
  {
    s << indent << "action_goal: ";
    s << std::endl;
    Printer< ::my_robot_move_actions::PainterMoveActionGoal_<ContainerAllocator> >::stream(s, indent + "  ", v.action_goal);
    s << indent << "action_result: ";
    s << std::endl;
    Printer< ::my_robot_move_actions::PainterMoveActionResult_<ContainerAllocator> >::stream(s, indent + "  ", v.action_result);
    s << indent << "action_feedback: ";
    s << std::endl;
    Printer< ::my_robot_move_actions::PainterMoveActionFeedback_<ContainerAllocator> >::stream(s, indent + "  ", v.action_feedback);
  }
};

} // namespace message_operations
} // namespace ros

#endif // MY_ROBOT_MOVE_ACTIONS_MESSAGE_PAINTERMOVEACTION_H