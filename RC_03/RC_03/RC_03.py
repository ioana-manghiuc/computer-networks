import threading
import time
import numpy as np
from numpy import ndarray

def create_packets(size: int):
    packet = np.random.randint(0, 50, size=size)
    return packet

class Source:
    def __init__(self, memory_size:int, window_size:int):
        self.memory = create_packets(memory_size)
        self.memory_size = memory_size
        self.window = np.zeros(window_size, dtype=int)
        self.window_size = window_size
        self.received_ack = np.zeros(memory_size, dtype=bool) 
     
class Destination:
    def __init__(self, source:Source):
        self.memory = np.zeros(source.memory_size, dtype=int)
        self.sent_ack = np.zeros(source.memory_size, dtype=bool)
