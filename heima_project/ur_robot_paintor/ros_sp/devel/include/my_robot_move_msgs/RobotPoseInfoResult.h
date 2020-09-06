// Generated by gencpp from file my_robot_move_msgs/RobotPoseInfoResult.msg
// DO NOT EDIT!


#ifndef MY_ROBOT_MOVE_MSGS_MESSAGE_ROBOTPOSEINFORESULT_H
#define MY_ROBOT_MOVE_MSGS_MESSAGE_ROBOTPOSEINFORESULT_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace my_robot_move_msgs
{
template <class ContainerAllocator>
struct RobotPoseInfoResult_
{
  typedef RobotPoseInfoResult_<ContainerAllocator> Type;

  RobotPoseInfoResult_()
    : code(0)
    , info()  {
    }
  RobotPoseInfoResult_(const ContainerAllocator& _alloc)
    : code(0)
    , info(_alloc)  {
  (void)_alloc;
    }



   typedef int32_t _code_type;
  _code_type code;

   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _info_type;
  _info_type info;





  typedef boost::shared_ptr< ::my_robot_move_msgs::RobotPoseInfoResult_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::my_robot_move_msgs::RobotPoseInfoResult_<ContainerAllocator> const> ConstPtr;

}; // struct RobotPoseInfoResult_

typedef ::my_robot_move_msgs::RobotPoseInfoResult_<std::allocator<void> > RobotPoseInfoResult;

typedef boost::shared_ptr< ::my_robot_move_msgs::RobotPoseInfoResult > RobotPoseInfoResultPtr;
typedef boost::shared_ptr< ::my_robot_move_msgs::RobotPoseInfoResult const> RobotPoseInfoResultConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::my_robot_move_msgs::RobotPoseInfoResult_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::my_robot_move_msgs::RobotPoseInfoResult_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::my_robot_move_msgs::RobotPoseInfoResult_<ContainerAllocator1> & lhs, const ::my_robot_move_msgs::RobotPoseInfoResult_<ContainerAllocator2> & rhs)
{
  return lhs.code == rhs.code &&
    lhs.info == rhs.info;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::my_robot_move_msgs::RobotPoseInfoResult_<ContainerAllocator1> & lhs, const ::my_robot_move_msgs::RobotPoseInfoResult_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace my_robot_move_msgs

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::my_robot_move_msgs::RobotPoseInfoResult_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::my_robot_move_msgs::RobotPoseInfoResult_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::my_robot_move_msgs::RobotPoseInfoResult_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::my_robot_move_msgs::RobotPoseInfoResult_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::my_robot_move_msgs::RobotPoseInfoResult_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::my_robot_move_msgs::RobotPoseInfoResult_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::my_robot_move_msgs::RobotPoseInfoResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "fc7e56391443c8f99621eadd9bab8ce4";
  }

  static const char* value(const ::my_robot_move_msgs::RobotPoseInfoResult_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xfc7e56391443c8f9ULL;
  static const uint64_t static_value2 = 0x9621eadd9bab8ce4ULL;
};

template<class ContainerAllocator>
struct DataType< ::my_robot_move_msgs::RobotPoseInfoResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "my_robot_move_msgs/RobotPoseInfoResult";
  }

  static const char* value(const ::my_robot_move_msgs::RobotPoseInfoResult_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::my_robot_move_msgs::RobotPoseInfoResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"\n"
"int32 code\n"
"string info\n"
"\n"
;
  }

  static const char* value(const ::my_robot_move_msgs::RobotPoseInfoResult_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::my_robot_move_msgs::RobotPoseInfoResult_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.code);
      stream.next(m.info);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct RobotPoseInfoResult_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::my_robot_move_msgs::RobotPoseInfoResult_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::my_robot_move_msgs::RobotPoseInfoResult_<ContainerAllocator>& v)
  {
    s << indent << "code: ";
    Printer<int32_t>::stream(s, indent + "  ", v.code);
    s << indent << "info: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.info);
  }
};

} // namespace message_operations
} // namespace ros

#endif // MY_ROBOT_MOVE_MSGS_MESSAGE_ROBOTPOSEINFORESULT_H