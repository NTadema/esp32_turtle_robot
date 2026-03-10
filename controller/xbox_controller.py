import socket
import time

import pygame

ROBOT_IP = "192.168.4.1"
ROBOT_PORT = 4210

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

pygame.init()
pygame.joystick.init()

joystick = pygame.joystick.Joystick(0)
joystick.init()

print("Controller:", joystick.get_name())

deadzone = 0.3
last_command = None

try:
    while True:
        pygame.event.pump()

        y = joystick.get_axis(1)
        x = joystick.get_axis(0)

        if abs(x) < deadzone:
            x = 0
        if abs(y) < deadzone:
            y = 0

        command = "STOP"

        if y < -0.6:
            command = "UP"
        elif y > 0.6:
            command = "DOWN"
        elif x < -0.6:
            command = "LEFT"
        elif x > 0.6:
            command = "RIGHT"

        sock.sendto(command.encode(), (ROBOT_IP, ROBOT_PORT))

        if command != last_command:
            print("Sent:", command)
            last_command = command

        time.sleep(0.08)

except KeyboardInterrupt:
    print("Controller stopped")
    sock.sendto("STOP".encode(), (ROBOT_IP, ROBOT_PORT))
