import threading
import numpy as np
import keyboard
import random
import time

def create_packets(size: int):
    packet = np.arange(size)
    return packet

def initialize_window(memory: np.ndarray, window_size: int):
    window = np.zeros(window_size, dtype=int)
    for i in range(window_size):
        window[i] = memory[i]
    return window

def slide_window(window: np.ndarray, memory: np.ndarray, received_ack: np.ndarray):
    if len(window) == 0:
        return window
    window_start = np.where(memory == window[0])[0][0]
    window_end = window_start + len(window)
    
    if window_end >= len(memory):
        return window
    
    remaining_packets = np.sum(~received_ack)
    if remaining_packets < len(window) and window_end >= len(memory) - 1:
        new_window_size = min(remaining_packets, len(memory) - window_start)
        new_window = memory[window_start:window_start + new_window_size]
    else:
        new_window = memory[window_start + 1: window_end + 1]
    
    return new_window

def has_new_elements_in_window(window: np.ndarray, ack_vector: np.ndarray) -> bool:
    for packet_value in window:
        if ack_vector[packet_value]:
            return False
    return True

class Source:
    def __init__(self, memory_size: int, window_size: int):
        self.memory = create_packets(memory_size)
        self.memory_size = memory_size
        self.window_size = window_size
        self.initial_window = self.memory[:window_size]
        self.window = np.copy(self.initial_window)
        self.received_ack = np.zeros(memory_size, dtype=bool)

class Destination:
    def __init__(self, source: Source):
        self.memory = np.zeros(source.memory_size, dtype=int)
        self.sent_ack = np.zeros(source.memory_size, dtype=bool)

def send_packet(source: Source, destination: Destination):
    try:
        while not (np.all(destination.sent_ack) and np.all(source.received_ack)):
            
            if len(source.window) < source.window_size: # adjust window size if needed
                source.window_size = len(source.window)
            
            if all(not destination.sent_ack[i] for i in source.window): # send all packets in window
                for packet_value in source.window:
                    time.sleep(1)
                    print(f"Sending packet {packet_value}...")
               
                for packet_value in source.window:  # mark all packets as sent and send acknowledgments
                    packet_index = np.where(source.memory == packet_value)[0][0]
                    destination.memory[packet_index] = packet_value
                    destination.sent_ack[packet_index] = True
                    source.received_ack[packet_value] = True
                    time.sleep(1)
                    if source.received_ack[packet_value]:
                        print(f"ACK {packet_value} received!")

                source.window = slide_window(source.window, source.memory, source.received_ack)
            else:
                source.window = slide_window(source.window, source.memory, source.received_ack)  # slide the window even if not all packets are new

        print("All packets sent and acknowledged.")
        print("Destination memory:", destination.memory)

    except KeyboardInterrupt:
        print("Program interrupted.")


if __name__ == "__main__":
    source = Source(10, 3)
    print(source.memory)
    destination = Destination(source)
    send_packet(source, destination)


