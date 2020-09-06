// Generated by gencpp from file my_robot_move_msgs/PainterMoveActionGoal.msg
// DO NOT EDIT!


#ifndef MY_ROBOT_MOVE_MSGS_MESSAGE_PAINTERMOVEACTIONGOAL_H
#define MY_ROBOT_MOVE_MSGS_MESSAGE_PAINTERMOVEACTIONGOAL_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <actionlib_msgs/GoalID.h>
#include <my_robot_move_msgs/PainterMoveGoal.h>

namespace my_robot_move_msgs
{
template <class ContainerAllocator>
struct PainterMoveActionGoal_
{
  typedef PainterMoveActionGoal_<ContainerAllocator> Type;

  PainterMoveActionGoal_()
    : header()
    , goal_id()
    , goal()  {
    }
  PainterMoveActionGoal_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , goal_id(_alloc)
    , goal(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef  ::actionlib_msgs::GoalID_<ContainerAllocator>  _goal_id_type;
  _goal_id_type goal_id;

   typedef  ::my_robot_move_msgs::PainterMoveGoal_<ContainerAllocator>  _goal_type;
  _goal_type goal;





  typedef boost::shared_ptr< ::my_robot_move_msgs::PainterMoveActionGoal_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::my_robot_move_msgs::PainterMoveActionGoal_<ContainerAllocator> const> ConstPtr;

}; // struct PainterMoveActionGoal_

typedef ::my_robot_move_msgs::PainterMoveActionGoal_<std::allocator<void> > PainterMoveActionGoal;

typedef boost::shared_ptr< ::my_robot_move_msgs::PainterMoveActionGoal > PainterMoveActionGoalPtr;
typedef boost::shared_ptr< ::my_robot_move_msgs::PainterMoveActionGoal const> PainterMoveActionGoalConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::my_robot_move_msgs::PainterMoveActionGoal_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::my_robot_move_msgs::PainterMoveActionGoal_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::my_robot_move_msgs::PainterMoveActionGoal_<ContainerAllocator1> & lhs, const ::my_robot_move_msgs::PainterMoveActionGoal_<ContainerAllocator2> & rhs)
{
  return lhs.header == rhs.header &&
    lhs.goal_id == rhs.goal_id &&
    lhs.goal == rhs.goal;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::my_robot_move_msgs::PainterMoveActionGoal_<ContainerAllocator1> & lhs, const ::my_robot_move_msgs::PainterMoveActionGoal_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace my_robot_move_msgs

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::my_robot_move_msgs::PainterMoveActionGoal_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::my_robot_move_msgs::PainterMoveActionGoal_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::my_robot_move_msgs::PainterMoveActionGoal_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::my_robot_move_msgs::PainterMoveActionGoal_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::my_robot_move_msgs::PainterMoveActionGoal_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::my_robot_move_msgs::PainterMoveActionGoal_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::my_robot_move_msgs::PainterMoveActionGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "f04328232072a010d831742cfe85245f";
  }

  static const char* value(const ::my_robot_move_msgs::PainterMoveActionGoal_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xf04328232072a010ULL;
  static const uint64_t static_value2 = 0xd831742cfe85245fULL;
};

template<class ContainerAllocator>
struct DataType< ::my_robot_move_msgs::PainterMoveActionGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "my_robot_move_msgs/PainterMoveActionGoal";
  }

  static const char* value(const ::my_robot_move_msgs::PainterMoveActionGoal_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::my_robot_move_msgs::PainterMoveActionGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
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
"MSG: my_robot_move_msgs/PainterMoveGoal\n"
"# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"string host\n"
"int32 port\n"
"float32 acceleration\n"
"float32 velocity \n"
"float32 epsilon\n"
"my_robot_move_msgs/Points ways\n"
"\n"
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
;
  }

  static const char* value(const ::my_robot_move_msgs::PainterMoveActionGoal_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::my_robot_move_msgs::PainterMoveActionGoal_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.goal_id);
      stream.next(m.goal);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct PainterMoveActionGoal_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::my_robot_move_msgs::PainterMoveActionGoal_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::my_robot_move_msgs::PainterMoveActionGoal_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "goal_id: ";
    s << std::endl;
    Printer< ::actionlib_msgs::GoalID_<ContainerAllocator> >::stream(s, indent + "  ", v.goal_id);
    s << indent << "goal: ";
    s << std::endl;
    Printer< ::my_robot_move_msgs::PainterMoveGoal_<ContainerAllocator> >::stream(s, indent + "  ", v.goal);
  }
};

} // namespace message_operations
} // namespace ros

#endif // MY_ROBOT_MOVE_MSGS_MESSAGE_PAINTERMOVEACTIONGOAL_H
