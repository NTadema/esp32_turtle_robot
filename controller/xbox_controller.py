import socket
import time

import pygame

# Network configuration: IP and UDP port of the robot to send motor commands to.
ROBOT_IP = "192.168.4.1"
ROBOT_PORT = 4210

# Create a UDP socket for sending motor speed messages.
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Initialize pygame and its joystick subsystem.
pygame.init()
pygame.joystick.init()

# Initialize the first connected joystick and print its name.
joystick = pygame.joystick.Joystick(0)
joystick.init()
print("Controller:", joystick.get_name())

# Joystick deadzone to ignore small stick movements (noise).
deadzone = 0.2
# Track last sent command so we only log changes.
last_command = None


# Convert a joystick axis value in range [-1.0, 1.0] to an integer motor PWM value in range [-255, 255].
def axis_to_speed(value):
    return int(max(min(value * 255, 255), -255))


try:
    # Main loop: read joystick, apply deadzone, mix to left/right motor speeds,
    # send speeds to the robot via UDP, and print changes.
    while True:
        # Pump pygame events to keep joystick state updated.
        pygame.event.pump()

        # Read axes: y is forward/backward, x is left/right.
        y = joystick.get_axis(1)  # invert forward/backward
        x = joystick.get_axis(0)

        # Apply deadzone: zero small axis values to avoid drift.
        if abs(x) < deadzone:
            x = 0
        if abs(y) < deadzone:
            y = 0

        # Mix forward/backward (y) and turning (x) into left/right motor speeds.
        left = axis_to_speed(y + x)
        right = axis_to_speed(y - x)

        # Format and send the motor speed message as "left,right" over UDP.
        message = f"{left},{right}"
        sock.sendto(message.encode(), (ROBOT_IP, ROBOT_PORT))

        # Log sent message only when it changes from the last one.
        if (left, right) != last_command:
            print("Sent:", message)
            last_command = (left, right)

        # Small delay to limit message rate and CPU usage.
        time.sleep(0.08)

except KeyboardInterrupt:
    # On Ctrl-C, stop the controller and send a zero-speed command.
    print("Controller stopped")
    sock.sendto("0,0".encode(), (ROBOT_IP, ROBOT_PORT))
