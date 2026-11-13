import serial

comPort = 'COM4'
baudrate = 115200

ser = serial.Serial(comPort, baudrate, timeout=0.1)

def create_paintPacket(x, y, z):
    return (x, y, z) 

def convert_pixelData(index, state):
    x_pos = int(index) % 128
    y_pos = int(index) // 128
    state = bool(state)
    p = create_paintPacket(x_pos, y_pos, state)
    return p

def packetSerial(p):
    ser.write(bytes(p))