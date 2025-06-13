import serial
import subprocess
import time

PORT = "/dev/ttyACM0"  # Update if needed
BAUD = 115200

while True:
    try:
        with serial.Serial(PORT, BAUD, timeout=1) as ser:
            print(f"Listening on {PORT}...")
            while True:
                line = ser.readline().decode('utf-8').strip()
                print(line)
                if line == "NEXT":
                    print("Button pressed! Skipping track...")
                    subprocess.run(["playerctl", "next"])
    except serial.SerialException as e:
        print(f"Serial error: {e}")
        print("Retrying in 5 seconds...")
        time.sleep(5)
