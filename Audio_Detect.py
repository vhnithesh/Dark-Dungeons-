import pyaudio
import numpy as np
import pyttsx3
import time


FORMAT = pyaudio.paInt16
CHANNELS = 1
RATE = 44100
CHUNK = 1024
THRESHOLD = 4300

def speak(text):
    engine = pyttsx3.Engine()  
    engine.say(text)
    engine.runAndWait()
    engine.stop()  

def callback(in_data, frame_count, time_info, status):
    audio = np.frombuffer(in_data, dtype=np.int16)
    eng = np.sum(audio ** 2) / len(audio)
    if eng > THRESHOLD:
        speak("Human voice detected!!!")
        print("Human voice detected")
    return (in_data, pyaudio.paContinue)

audio = pyaudio.PyAudio()
stream = audio.open(format=FORMAT,
                    channels=CHANNELS,
                    rate=RATE,
                    input=True,
                    frames_per_buffer=CHUNK,
                    stream_callback=callback)

stream.start_stream()

try:
    while True:
        speak("This is a SOS message sent every 12 seconds,please respond")
        time.sleep(12 )
except KeyboardInterrupt:
    pass

stream.stop_stream()
stream.close()
audio.terminate()
