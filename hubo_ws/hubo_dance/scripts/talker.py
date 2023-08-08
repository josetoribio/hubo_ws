#!/usr/bin/env python

import rospy
from std_msgs.msg import String
from sensor_msgs.msg import JointState
from std_msgs.msg import Header
import time
run = True

def received_callback():
    run = False

def wave(pub):
    state = JointState()
    state.name = ["RHY", "RHR", "RHP", "RKN", "RAP", "RAR",
        "LHY", "LHR", "LHP", "LKN", "LAP", "LAR",
        "RSP", "RSR", "RSY", "REB", "RWY", "RWP",
        "LSP", "LSR", "LSY", "LEB", "LWY", "LWP",
        "WST",
        "RWY2", "RHAND", "LWY2", "LHAND",
        "RWH", "LWH"]
    state.position = [0,0,0,0,0,0,0,0,0,0,0,0,0,-70,-80,-110,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    state.header = Header()
    state.header.stamp = rospy.Time.now()
    state.velocity = [3]
    state.effort = []
    pub.publish(state)
    time.sleep(3)
    wavespeed = 1
    state.position = [0,0,0,0,0,0,0,0,0,0,0,0,0,-70,-80,-40,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    state.velocity = [wavespeed]
    pub.publish(state)
    time.sleep(wavespeed)
    state.position = [0,0,0,0,0,0,0,0,0,0,0,0,0,-70,-80,-110,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    state.velocity = [wavespeed]
    pub.publish(state)
    time.sleep(wavespeed)
    state.position = [0,0,0,0,0,0,0,0,0,0,0,0,0,-70,-80,-40,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    state.velocity = [wavespeed]
    pub.publish(state)
    time.sleep(wavespeed)
    state.position = [0,0,0,0,0,0,0,0,0,0,0,0,0,-70,-80,-70,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    state.velocity = [wavespeed]
    pub.publish(state)
    time.sleep(wavespeed)

def dance(pub):
    state = JointState()
    state.name = ["RHY", "RHR", "RHP", "RKN", "RAP", "RAR",
        "LHY", "LHR", "LHP", "LKN", "LAP", "LAR",
        "RSP", "RSR", "RSY", "REB", "RWY", "RWP",
        "LSP", "LSR", "LSY", "LEB", "LWY", "LWP",
        "WST",
        "RWY2", "RHAND", "LWY2", "LHAND",
        "RWH", "LWH"]
    state.position = [0,0,0,0,0,0,0,0,0,0,0,0,0,-70,-80,-70,0,0,0,70,80,-70,0,0,0,80,0,80,0,0,0]
    state.header = Header()
    state.header.stamp = rospy.Time.now()
    state.velocity = [3]
    state.effort = []
    pub.publish(state)
    time.sleep(3)
    state.position = [0,-20,0,0,0,0,0,0,0,0,0,0,0,-70,-80,-110,0,0,0,70,80,-40,0,0,0,80,0,80,0,0,0]
    state.velocity = [3]
    pub.publish(state)
    time.sleep(3)
    state.position = [0,0,0,0,0,0,0,20,0,0,0,0,0,-70,-80,-40,0,0,0,70,80,-110,0,0,0,80,0,80,0,0,0]
    state.velocity = [3]
    pub.publish(state)
    time.sleep(3)
    state.position = [0,-20,0,0,0,0,0,0,0,0,0,0,0,-70,-80,-110,0,0,0,70,80,-40,0,0,0,80,0,80,0,0,0]
    state.velocity = [3]
    pub.publish(state)
    time.sleep(3)
    state.position = [0,0,0,0,0,0,0,20,0,0,0,0,0,-70,-80,-40,0,0,0,70,80,-110,0,0,0,80,0,80,0,0,0]
    state.velocity = [3]
    pub.publish(state)
    time.sleep(3)

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

def hubo_act(choice):
    pub = rospy.Publisher('joint_refs', JointState, queue_size=1)
    rospy.init_node('talker', anonymous=True)
    time.sleep(5)
    if choice == 0:
        home(pub)
    elif choice == 1:
        wave(pub)
    elif choice == 2:
        dance(pub)

    

if __name__ == '__main__':
    try:
        while True:
            action = int(input("Enter a command (0: Home , 1: Wave, 2: Dance) \n Choice: "))
            hubo_act(action)
    except rospy.ROSInterruptException:
        pass
