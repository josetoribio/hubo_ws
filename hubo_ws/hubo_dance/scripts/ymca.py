#!/usr/bin/env python

import rospy
from std_msgs.msg import String
from sensor_msgs.msg import JointState
from std_msgs.msg import Header
import time

def home(pub):
    state = JointState()
    state.name = ["RHY", "RHR", "RHP", "RKN", "RAP", "RAR",
        "LHY", "LHR", "LHP", "LKN", "LAP", "LAR",
        "RSP", "RSR", "RSY", "REB", "RWY", "RWP",
        "LSP", "LSR", "LSY", "LEB", "LWY", "LWP",
        "WST",
        "RWY2", "RHAND", "LWY2", "LHAND",
        "RWH", "LWH"]
    state.position = [0 for _ in range(31)]
    state.header = Header()
    state.header.stamp = rospy.Time.now()
    state.velocity = [3]
    state.effort = []
    pub.publish(state)
    time.sleep(4)

def dance(pub):
    state = JointState()
    state.name = ["RHY", "RHR", "RHP", "RKN", "RAP", "RAR",
        "LHY", "LHR", "LHP", "LKN", "LAP", "LAR",
        "RSP", "RSR", "RSY", "REB", "RWY", "RWP",
        "LSP", "LSR", "LSY", "LEB", "LWY", "LWP",
        "WST",
        "RWY2", "RHAND", "LWY2", "LHAND",
        "RWH", "LWH"]
    state.position = [-0,0,-56.8,144,-7.9,-0,0,-0,-56.8,144,-7.9,-0,0,-120,-80,0,0,-20,0,120,80,0,0,20,0,0,0,0,0,0,0]
    state.header = Header()
    state.header.stamp = rospy.Time.now()
    state.velocity = [3]
    state.effort = []
    pub.publish(state)
    time.sleep(3)
    state.position = [-0,0,-56.8,144,-7.9,-0,0,-0,-56.8,144,-7.9,-0,0,-100,-80,-100,0,-60,0,100,80,-100,0,-60,0,0,0,0,0,0,0]
    state.header.stamp = rospy.Time.now()
    state.velocity = [3]
    pub.publish(state)
    time.sleep(3)
    state.position = [-0,0,-56.8,144,-7.9,-0,0,-0,-56.8,144,-7.9,-0,0,-140,-80,-40,0,-20,0,0,80,-50,0,-30,0,0,0,0,0,0,0]
    state.header.stamp = rospy.Time.now()
    state.velocity = [3]
    pub.publish(state)
    time.sleep(3)
    state.position = [-0,0,-56.8,144,-7.9,-0,0,-0,-56.8,144,-7.9,-0,0,-130,-80,-50,0,-30,0,130,80,-50,0,-30,0,0,0,0,0,0,0]
    state.header.stamp = rospy.Time.now()
    state.velocity = [3]
    pub.publish(state)
    time.sleep(3)
    state.position = [-1.85986e-05,7.61854e-07,-56.75,143.959,-7.95,-1.48507e-06,1.91345e-05,-3.53222e-06,-56.75,143.959,-7.95,-6.66184e-07,40,10,0,-130,0,20,40,-10,0,-130,0,20,0,0,0,0,0,0,0]
    state.header.stamp = rospy.Time.now()
    state.velocity = [3]
    pub.publish(state)
    time.sleep(3)

def updown(pub):
    state = JointState()
    state.name = ["RHY", "RHR", "RHP", "RKN", "RAP", "RAR",
        "LHY", "LHR", "LHP", "LKN", "LAP", "LAR",
        "RSP", "RSR", "RSY", "REB", "RWY", "RWP",
        "LSP", "LSR", "LSY", "LEB", "LWY", "LWP",
        "WST",
        "RWY2", "RHAND", "LWY2", "LHAND",
        "RWH", "LWH"]
    state.position = [0,0,-35.6,65.1,-29.6,0,0,0,-35.6,65.1,-29.6,0,40,10,0,-130,0,20,40,-10,0,-130,0,20,0,0,0,0,0,0,0]
    state.header = Header()
    state.header.stamp = rospy.Time.now()
    state.velocity = [1]
    state.effort = []
    pub.publish(state)
    time.sleep(2)
    for _ in range(3):
        newheight = 70
        state.position = [0,0,-newheight*(35.6/65.1),newheight,-newheight*(29.6/65.1),0,0,0,-newheight*(35.6/65.1),newheight,-newheight*(29.6/65.1),0,40,10,0,-130,0,20,40,-10,0,-130,0,20,0,0,0,0,0,0,0]
        state.header = Header()
        state.header.stamp = rospy.Time.now()
        state.velocity = [0.5]
        state.effort = []
        pub.publish(state)
        time.sleep(0.5)
        state.position = [0,0,-35.6,65.1,-29.6,0,0,0,-35.6,65.1,-29.6,0,40,10,0,-130,0,20,40,-10,0,-130,0,20,0,0,0,0,0,0,0]
        state.header = Header()
        state.header.stamp = rospy.Time.now()
        state.velocity = [0.5]
        state.effort = []
        pub.publish(state)
        time.sleep(0.5)

def talker():
    pub = rospy.Publisher('joint_refs', JointState, queue_size=1)
    rospy.init_node('ymca', anonymous=True)
    modepub = rospy.Publisher("robot_mode", String, queue_size=1)
    time.sleep(5)
    #input("Walk mode")
    #modepub.publish("walking_position")
    #input("Wheel mode")
    #modepub.publish("wheel_position")
    input("Dance")
    #updown(pub)
    dance(pub)
    

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
