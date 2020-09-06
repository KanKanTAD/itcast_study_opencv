// Auto-generated. Do not edit!

// (in-package my_robot_move_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let Point = require('./Point.js');

//-----------------------------------------------------------

class PainterMoveFeedback {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.current_pose = null;
      this.percent = null;
      this.code = null;
    }
    else {
      if (initObj.hasOwnProperty('current_pose')) {
        this.current_pose = initObj.current_pose
      }
      else {
        this.current_pose = new Point();
      }
      if (initObj.hasOwnProperty('percent')) {
        this.percent = initObj.percent
      }
      else {
        this.percent = 0.0;
      }
      if (initObj.hasOwnProperty('code')) {
        this.code = initObj.code
      }
      else {
        this.code = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type PainterMoveFeedback
    // Serialize message field [current_pose]
    bufferOffset = Point.serialize(obj.current_pose, buffer, bufferOffset);
    // Serialize message field [percent]
    bufferOffset = _serializer.float32(obj.percent, buffer, bufferOffset);
    // Serialize message field [code]
    bufferOffset = _serializer.int32(obj.code, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type PainterMoveFeedback
    let len;
    let data = new PainterMoveFeedback(null);
    // Deserialize message field [current_pose]
    data.current_pose = Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [percent]
    data.percent = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [code]
    data.code = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 32;
  }

  static datatype() {
    // Returns string type for a message object
    return 'my_robot_move_msgs/PainterMoveFeedback';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '0b33f5916a868314488e7fbc873d6eb9';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
    
    my_robot_move_msgs/Point current_pose
    float32 percent
    int32 code
    
    
    
    ================================================================================
    MSG: my_robot_move_msgs/Point
    float32 x
    float32 y
    float32 z
    float32 rx
    float32 ry
    float32 rz
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new PainterMoveFeedback(null);
    if (msg.current_pose !== undefined) {
      resolved.current_pose = Point.Resolve(msg.current_pose)
    }
    else {
      resolved.current_pose = new Point()
    }

    if (msg.percent !== undefined) {
      resolved.percent = msg.percent;
    }
    else {
      resolved.percent = 0.0
    }

    if (msg.code !== undefined) {
      resolved.code = msg.code;
    }
    else {
      resolved.code = 0
    }

    return resolved;
    }
};

module.exports = PainterMoveFeedback;