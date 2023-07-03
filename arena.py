import RPi.GPIO as GPIO
import time

# Button mappings
button_mappings = {
    35: {"name": "Button_Start"},
    37: {"name": "Button_Stop"},
    33: {"name": "Button_Pit_up"},
    31: {"name": "Button_Pit_Down"},
    29: {"name": "Button_spinner_1"},
    23: {"name": "Button_spinner_1_counter"},
    21: {"name": "Button_Spinner_1_Low"},
    19: {"name": "Button_Spinner_1_High"},
    15: {"name": "Button_spinner_2"},
    13: {"name": "Button_spinner_2_counter"},
    11: {"name": "Button_Spinner_2_Low"},
    10: {"name": "Button_Spinner_2_High"},
    8: {"name": "Button_spinner_3"},
    7: {"name": "Button_spinner_3_counter"},
    5: {"name": "Button_Spinner_3_Low"},
    3: {"name": "Button_Spinner_3_High"},
    18: {"name": "Button_Flipper"},
}

# Output mappings
output_mappings = {
    12: {"name": "Spinner_1_out"},
    16: {"name": "Spinner_1_out_counter"},
    22: {"name": "Spinner_2_out"},
    24: {"name": "Spinner_2_out_counter"},
    26: {"name": "Spinner_3_out"},
    32: {"name": "Spinner_3_out_counter"},
    36: {"name": "FLipper_Out"},
    38: {"name": "CS1"},
    40: {"name": "UD1"},
    35: {"name": "INC1"},
    37: {"name": "CS2"},
    33: {"name": "UD2"},
    31: {"name": "INC2"},
    29: {"name": "CS3"},
    23: {"name": "UD3"},
    21: {"name": "INC3"},
}

# Variables
Active = GPIO.LOW
Weapons_Enabled = GPIO.LOW
Flipper_Fire = GPIO.LOW
StepsRequired = 2048
Start_millis = 0
STEPS_PER_REV = 32
GEAR_RED = 64
STEPS_PER_OUT_REV = STEPS_PER_REV * GEAR_RED
Pit_Stepper = None

def setup():
    # Inputs
    GPIO.setmode(GPIO.BOARD)
    for button_pin in button_mappings:
        GPIO.setup(button_pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
        GPIO.add_event_detect(button_pin, GPIO.RISING, callback=button_callback, bouncetime=200)

    # Outputs
    for output_pin in output_mappings:
        GPIO.setup(output_pin, GPIO.OUT)

def button_callback(channel):
    button_pin = channel
    button_info = button_mappings[button_pin]
    button_name = button_info["name"]
    
    global Active, Start_millis, Weapons_Enabled, Flipper_Fire

    if button_name == "Button_Start":
        Active = GPIO.HIGH
        Start_millis = int(time.time() * 1000)
    elif button_name == "Button_Stop":
        Active = GPIO.LOW
        Weapons_Enabled = GPIO.LOW
        Start_millis = 0
        for output_pin in output_mappings:
            GPIO.output(output_pin, GPIO.LOW)
    elif button_name == "Button_Pit_up":
        if Weapons_Enabled == GPIO.HIGH:
            Pit_Stepper.setSpeed(1)
            Pit_Stepper.step(StepsRequired)
    elif button_name == "Button_Pit_Down":
        if Weapons_Enabled == GPIO.HIGH:
            Pit_Stepper.setSpeed(1)
            Pit_Stepper.step(-StepsRequired)
    elif button_name == "Button_Flipper":
        if Weapons_Enabled == GPIO.HIGH:
            Flipper_Fire = GPIO.HIGH
    else:
        # Handle other button actions
        if Weapons_Enabled == GPIO.HIGH:
            output_pin = output_mappings[button_pin]
            GPIO.output(output_pin, GPIO.HIGH)

def timer():
    global Active, Start_millis, Weapons_Enabled

    if Active == GPIO.HIGH:
        current_millis = int(time.time() * 1000)
        if Start_millis != 0:
            if current_millis - Start_millis >= 33000:
                Weapons_Enabled = GPIO.HIGH
            if current_millis - Start_millis >= 183000:
                Weapons_Enabled = GPIO.LOW
                Active = GPIO.LOW

def flipper():
    global Flipper_Fire, Weapons_Enabled

    if Flipper_Fire == GPIO.HIGH:
        if Weapons_Enabled == GPIO.HIGH:
            GPIO.output(output_mappings[36], GPIO.HIGH)
            time.sleep(0.05)
            GPIO.output(output_mappings[36], GPIO.LOW)

def main():
    while True:
        timer()
        flipper()
        time.sleep(0.01)  # Small delay to avoid excessive CPU usage

if __name__ == "__main__":
    setup()
    try:
        main()
    except KeyboardInterrupt:
        pass
    finally:
        GPIO.cleanup()
