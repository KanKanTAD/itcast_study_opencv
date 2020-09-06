// Generated by gencpp from file my_robot_move_msgs/SvgToPntssResponse.msg
// DO NOT EDIT!


#ifndef MY_ROBOT_MOVE_MSGS_MESSAGE_SVGTOPNTSSRESPONSE_H
#define MY_ROBOT_MOVE_MSGS_MESSAGE_SVGTOPNTSSRESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <my_robot_move_msgs/Points.h>

namespace my_robot_move_msgs
{
template <class ContainerAllocator>
struct SvgToPntssResponse_
{
  typedef SvgToPntssResponse_<ContainerAllocator> Type;

  SvgToPntssResponse_()
    : pts()  {
    }
  SvgToPntssResponse_(const ContainerAllocator& _alloc)
    : pts(_alloc)  {
  (void)_alloc;
    }



   typedef  ::my_robot_move_msgs::Points_<ContainerAllocator>  _pts_type;
  _pts_type pts;





  typedef boost::shared_ptr< ::my_robot_move_msgs::SvgToPntssResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::my_robot_move_msgs::SvgToPntssResponse_<ContainerAllocator> const> ConstPtr;

}; // struct SvgToPntssResponse_

typedef ::my_robot_move_msgs::SvgToPntssResponse_<std::allocator<void> > SvgToPntssResponse;

typedef boost::shared_ptr< ::my_robot_move_msgs::SvgToPntssResponse > SvgToPntssResponsePtr;
typedef boost::shared_ptr< ::my_robot_move_msgs::SvgToPntssResponse const> SvgToPntssResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::my_robot_move_msgs::SvgToPntssResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::my_robot_move_msgs::SvgToPntssResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::my_robot_move_msgs::SvgToPntssResponse_<ContainerAllocator1> & lhs, const ::my_robot_move_msgs::SvgToPntssResponse_<ContainerAllocator2> & rhs)
{
  return lhs.pts == rhs.pts;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::my_robot_move_msgs::SvgToPntssResponse_<ContainerAllocator1> & lhs, const ::my_robot_move_msgs::SvgToPntssResponse_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace my_robot_move_msgs

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::my_robot_move_msgs::SvgToPntssResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::my_robot_move_msgs::SvgToPntssResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::my_robot_move_msgs::SvgToPntssResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::my_robot_move_msgs::SvgToPntssResponse_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::my_robot_move_msgs::SvgToPntssResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::my_robot_move_msgs::SvgToPntssResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::my_robot_move_msgs::SvgToPntssResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "483f7d3077cf442487d1afffe2c7d29b";
  }

  static const char* value(const ::my_robot_move_msgs::SvgToPntssResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x483f7d3077cf4424ULL;
  static const uint64_t static_value2 = 0x87d1afffe2c7d29bULL;
};

template<class ContainerAllocator>
struct DataType< ::my_robot_move_msgs::SvgToPntssResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "my_robot_move_msgs/SvgToPntssResponse";
  }

  static const char* value(const ::my_robot_move_msgs::SvgToPntssResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::my_robot_move_msgs::SvgToPntssResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "\n"
"my_robot_move_msgs/Points pts\n"
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

  static const char* value(const ::my_robot_move_msgs::SvgToPntssResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::my_robot_move_msgs::SvgToPntssResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.pts);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct SvgToPntssResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::my_robot_move_msgs::SvgToPntssResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::my_robot_move_msgs::SvgToPntssResponse_<ContainerAllocator>& v)
  {
    s << indent << "pts: ";
    s << std::endl;
    Printer< ::my_robot_move_msgs::Points_<ContainerAllocator> >::stream(s, indent + "  ", v.pts);
  }
};

} // namespace message_operations
} // namespace ros

#endif // MY_ROBOT_MOVE_MSGS_MESSAGE_SVGTOPNTSSRESPONSE_H