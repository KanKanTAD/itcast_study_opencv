// Auto-generated. Do not edit!

// (in-package my_robot_move_msgs.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

let Points = require('../msg/Points.js');

//-----------------------------------------------------------

class SvgToPntssRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.ori_x = null;
      this.ori_y = null;
      this.ori_z = null;
      this.tran_z = null;
      this.rx = null;
      this.ry = null;
      this.rz = null;
      this.width = null;
      this.height = null;
      this.svg_width = null;
      this.svg_height = null;
      this.svg_pathds = null;
    }
    else {
      if (initObj.hasOwnProperty('ori_x')) {
        this.ori_x = initObj.ori_x
      }
      else {
        this.ori_x = 0.0;
      }
      if (initObj.hasOwnProperty('ori_y')) {
        this.ori_y = initObj.ori_y
      }
      else {
        this.ori_y = 0.0;
      }
      if (initObj.hasOwnProperty('ori_z')) {
        this.ori_z = initObj.ori_z
      }
      else {
        this.ori_z = 0.0;
      }
      if (initObj.hasOwnProperty('tran_z')) {
        this.tran_z = initObj.tran_z
      }
      else {
        this.tran_z = 0.0;
      }
      if (initObj.hasOwnProperty('rx')) {
        this.rx = initObj.rx
      }
      else {
        this.rx = 0.0;
      }
      if (initObj.hasOwnProperty('ry')) {
        this.ry = initObj.ry
      }
      else {
        this.ry = 0.0;
      }
      if (initObj.hasOwnProperty('rz')) {
        this.rz = initObj.rz
      }
      else {
        this.rz = 0.0;
      }
      if (initObj.hasOwnProperty('width')) {
        this.width = initObj.width
      }
      else {
        this.width = 0.0;
      }
      if (initObj.hasOwnProperty('height')) {
        this.height = initObj.height
      }
      else {
        this.height = 0.0;
      }
      if (initObj.hasOwnProperty('svg_width')) {
        this.svg_width = initObj.svg_width
      }
      else {
        this.svg_width = 0.0;
      }
      if (initObj.hasOwnProperty('svg_height')) {
        this.svg_height = initObj.svg_height
      }
      else {
        this.svg_height = 0.0;
      }
      if (initObj.hasOwnProperty('svg_pathds')) {
        this.svg_pathds = initObj.svg_pathds
      }
      else {
        this.svg_pathds = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SvgToPntssRequest
    // Serialize message field [ori_x]
    bufferOffset = _serializer.float32(obj.ori_x, buffer, bufferOffset);
    // Serialize message field [ori_y]
    bufferOffset = _serializer.float32(obj.ori_y, buffer, bufferOffset);
    // Serialize message field [ori_z]
    bufferOffset = _serializer.float32(obj.ori_z, buffer, bufferOffset);
    // Serialize message field [tran_z]
    bufferOffset = _serializer.float32(obj.tran_z, buffer, bufferOffset);
    // Serialize message field [rx]
    bufferOffset = _serializer.float32(obj.rx, buffer, bufferOffset);
    // Serialize message field [ry]
    bufferOffset = _serializer.float32(obj.ry, buffer, bufferOffset);
    // Serialize message field [rz]
    bufferOffset = _serializer.float32(obj.rz, buffer, bufferOffset);
    // Serialize message field [width]
    bufferOffset = _serializer.float32(obj.width, buffer, bufferOffset);
    // Serialize message field [height]
    bufferOffset = _serializer.float32(obj.height, buffer, bufferOffset);
    // Serialize message field [svg_width]
    bufferOffset = _serializer.float32(obj.svg_width, buffer, bufferOffset);
    // Serialize message field [svg_height]
    bufferOffset = _serializer.float32(obj.svg_height, buffer, bufferOffset);
    // Serialize message field [svg_pathds]
    bufferOffset = _arraySerializer.string(obj.svg_pathds, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SvgToPntssRequest
    let len;
    let data = new SvgToPntssRequest(null);
    // Deserialize message field [ori_x]
    data.ori_x = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [ori_y]
    data.ori_y = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [ori_z]
    data.ori_z = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [tran_z]
    data.tran_z = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [rx]
    data.rx = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [ry]
    data.ry = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [rz]
    data.rz = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [width]
    data.width = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [height]
    data.height = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [svg_width]
    data.svg_width = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [svg_height]
    data.svg_height = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [svg_pathds]
    data.svg_pathds = _arrayDeserializer.string(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    object.svg_pathds.forEach((val) => {
      length += 4 + _getByteLength(val);
    });
    return length + 48;
  }

  static datatype() {
    // Returns string type for a service object
    return 'my_robot_move_msgs/SvgToPntssRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'b21a7eada4f3de7e883b7afd845e0a94';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 ori_x
    float32 ori_y
    float32 ori_z
    float32 tran_z
    
    float32 rx
    float32 ry
    float32 rz
    
    float32 width
    float32 height
    
    float32 svg_width
    float32 svg_height
    string[] svg_pathds
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SvgToPntssRequest(null);
    if (msg.ori_x !== undefined) {
      resolved.ori_x = msg.ori_x;
    }
    else {
      resolved.ori_x = 0.0
    }

    if (msg.ori_y !== undefined) {
      resolved.ori_y = msg.ori_y;
    }
    else {
      resolved.ori_y = 0.0
    }

    if (msg.ori_z !== undefined) {
      resolved.ori_z = msg.ori_z;
    }
    else {
      resolved.ori_z = 0.0
    }

    if (msg.tran_z !== undefined) {
      resolved.tran_z = msg.tran_z;
    }
    else {
      resolved.tran_z = 0.0
    }

    if (msg.rx !== undefined) {
      resolved.rx = msg.rx;
    }
    else {
      resolved.rx = 0.0
    }

    if (msg.ry !== undefined) {
      resolved.ry = msg.ry;
    }
    else {
      resolved.ry = 0.0
    }

    if (msg.rz !== undefined) {
      resolved.rz = msg.rz;
    }
    else {
      resolved.rz = 0.0
    }

    if (msg.width !== undefined) {
      resolved.width = msg.width;
    }
    else {
      resolved.width = 0.0
    }

    if (msg.height !== undefined) {
      resolved.height = msg.height;
    }
    else {
      resolved.height = 0.0
    }

    if (msg.svg_width !== undefined) {
      resolved.svg_width = msg.svg_width;
    }
    else {
      resolved.svg_width = 0.0
    }

    if (msg.svg_height !== undefined) {
      resolved.svg_height = msg.svg_height;
    }
    else {
      resolved.svg_height = 0.0
    }

    if (msg.svg_pathds !== undefined) {
      resolved.svg_pathds = msg.svg_pathds;
    }
    else {
      resolved.svg_pathds = []
    }

    return resolved;
    }
};

class SvgToPntssResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.pts = null;
    }
    else {
      if (initObj.hasOwnProperty('pts')) {
        this.pts = initObj.pts
      }
      else {
        this.pts = new Points();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SvgToPntssResponse
    // Serialize message field [pts]
    bufferOffset = Points.serialize(obj.pts, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SvgToPntssResponse
    let len;
    let data = new SvgToPntssResponse(null);
    // Deserialize message field [pts]
    data.pts = Points.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += Points.getMessageSize(object.pts);
    return length;
  }

  static datatype() {
    // Returns string type for a service object
    return 'my_robot_move_msgs/SvgToPntssResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '483f7d3077cf442487d1afffe2c7d29b';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    
    my_robot_move_msgs/Points pts
    
    
    ================================================================================
    MSG: my_robot_move_msgs/Points
    Point[] data
    
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
    const resolved = new SvgToPntssResponse(null);
    if (msg.pts !== undefined) {
      resolved.pts = Points.Resolve(msg.pts)
    }
    else {
      resolved.pts = new Points()
    }

    return resolved;
    }
};

module.exports = {
  Request: SvgToPntssRequest,
  Response: SvgToPntssResponse,
  md5sum() { return '60816149316c144de894d769a72c05f1'; },
  datatype() { return 'my_robot_move_msgs/SvgToPntss'; }
};
