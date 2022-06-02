import rtde_control
import numpy as np

# Setup robot with robot IP address
rtde_c = rtde_control.RTDEControlInterface("192.168.1.20")

# Positions
position1_J = [-184.42, -91.86, -162.74, 68.81, 92.92, 1.25]
position2_J = [-273.23, -91.95, -162.73, 68.81, 92.92, 1.25]
position3_J = [-270.07, -121.02, -134.37, 68.81, 92.92, 1.25]
#position_final = [-284.17, -121.36, -130.60, 61.18, 92.92, 1.25]
# Speeds and accelerations
speed_J_fast = 0.7
acc_J_fast = 1

# Move robot between positions

# You can define position, speed and acceleration
#rtde_c.moveJ(np.deg2rad(home_J), speed_J_fast, acc_J_fast)
# You can define only position, default speed and acceleration will be applied
#rtde_c.moveJ(np.deg2rad(position1_J))
#rtde_c.moveJ(np.deg2rad(position2_J), speed_J_fast)
#rtde_c.moveJ(np.deg2rad(position3_J), speed_J_fast)
rtde_c.moveJ(np.deg2rad(position2_J), speed_J_fast)
rtde_c.moveJ(np.deg2rad(position1_J), speed_J_fast)
# You can define position and speed, default acceleration will be applied
#rtde_c.moveJ(np.deg2rad(position2_J), speed_J_fast)
# You can define whether movement will be blocking or non-blocking
# Default is False - blocking movement, True is non-blocking movement
#rtde_c.moveJ(np.deg2rad(home_J), speed_J_fast, acc_J_fast, True)

# Stop the RTDE control script
rtde_c.stopScript()
