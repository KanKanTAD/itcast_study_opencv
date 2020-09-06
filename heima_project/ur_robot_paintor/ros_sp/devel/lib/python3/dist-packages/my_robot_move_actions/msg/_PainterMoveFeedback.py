# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from my_robot_move_actions/PainterMoveFeedback.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import my_robot_move_msgs.msg

class PainterMoveFeedback(genpy.Message):
  _md5sum = "2a2cbed681a69d3753ab21ff7902d952"
  _type = "my_robot_move_actions/PainterMoveFeedback"
  _has_header = False  # flag to mark the presence of a Header object
  _full_text = """# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======

my_robot_move_msgs/Point current_pose
float32 percent



================================================================================
MSG: my_robot_move_msgs/Point
float32 x
float32 y
float32 z
float32 rx
float32 ry
float32 rz
"""
  __slots__ = ['current_pose','percent']
  _slot_types = ['my_robot_move_msgs/Point','float32']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       current_pose,percent

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(PainterMoveFeedback, self).__init__(*args, **kwds)
      # message fields cannot be None, assign default values for those that are
      if self.current_pose is None:
        self.current_pose = my_robot_move_msgs.msg.Point()
      if self.percent is None:
        self.percent = 0.
    else:
      self.current_pose = my_robot_move_msgs.msg.Point()
      self.percent = 0.

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_get_struct_7f().pack(_x.current_pose.x, _x.current_pose.y, _x.current_pose.z, _x.current_pose.rx, _x.current_pose.ry, _x.current_pose.rz, _x.percent))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.current_pose is None:
        self.current_pose = my_robot_move_msgs.msg.Point()
      end = 0
      _x = self
      start = end
      end += 28
      (_x.current_pose.x, _x.current_pose.y, _x.current_pose.z, _x.current_pose.rx, _x.current_pose.ry, _x.current_pose.rz, _x.percent,) = _get_struct_7f().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_get_struct_7f().pack(_x.current_pose.x, _x.current_pose.y, _x.current_pose.z, _x.current_pose.rx, _x.current_pose.ry, _x.current_pose.rz, _x.percent))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.current_pose is None:
        self.current_pose = my_robot_move_msgs.msg.Point()
      end = 0
      _x = self
      start = end
      end += 28
      (_x.current_pose.x, _x.current_pose.y, _x.current_pose.z, _x.current_pose.rx, _x.current_pose.ry, _x.current_pose.rz, _x.percent,) = _get_struct_7f().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_7f = None
def _get_struct_7f():
    global _struct_7f
    if _struct_7f is None:
        _struct_7f = struct.Struct("<7f")
    return _struct_7f