// Auto-generated. Do not edit!

// (in-package my_robot_move_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class RobotPoseInfoGoal {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.host = null;
      this.port = null;
    }
    else {
      if (initObj.hasOwnProperty('host')) {
        this.host = initObj.host
      }
      else {
        this.host = '';
      }
      if (initObj.hasOwnProperty('port')) {
        this.port = initObj.port
      }
      else {
        this.port = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type RobotPoseInfoGoal
    // Serialize message field [host]
    bufferOffset = _serializer.string(obj.host, buffer, bufferOffset);
    // Serialize message field [port]
    bufferOffset = _serializer.int32(obj.port, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type RobotPoseInfoGoal
    let len;
    let data = new RobotPoseInfoGoal(null);
    // Deserialize message field [host]
    data.host = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [port]
    data.port = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += _getByteLength(object.host);
    return length + 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'my_robot_move_msgs/RobotPoseInfoGoal';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '55932133259e8c3335a553618447da45';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
    string host
    int32 port
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new RobotPoseInfoGoal(null);
    if (msg.host !== undefined) {
      resolved.host = msg.host;
    }
    else {
      resolved.host = ''
    }

    if (msg.port !== undefined) {
      resolved.port = msg.port;
    }
    else {
      resolved.port = 0
    }

    return resolved;
    }
};

module.exports = RobotPoseInfoGoal;