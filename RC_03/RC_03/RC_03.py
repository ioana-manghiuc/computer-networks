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

def all_true(vector: np.ndarray) -> bool:
    return np.all(vector)

def slide_window(window: np.ndarray, memory: np.ndarray, received_ack: np.ndarray):
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

def random_index(range: int) -> int:
    return np.random.randint(0, range - 1)

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
    lost_packet = random_index(source.memory_size)
    print("Lost packet index:", lost_packet)
    
    while not (np.all(destination.sent_ack) and np.all(source.received_ack)):
        if len(source.window) < source.window_size:  # adjust window size if needed
            source.window_size = len(source.window)

        if all(not destination.sent_ack[np.where(source.memory == packet_value)[0][0]] for packet_value in source.window):
            for packet_value in source.window:
                time.sleep(1)
                print(f"Sending packet {packet_value}...")

            for packet_value in source.window:  # mark packets as sent/lost and handle acknowledgments
                packet_index = np.where(source.memory == packet_value)[0][0]
                if packet_index != lost_packet:
                    destination.memory[packet_index] = packet_value
                    print(f"Packet {packet_value} received by destination!")
                    destination.sent_ack[packet_index] = True
                    print(f"Sending ACK {packet_value}...")
                    source.received_ack[packet_value] = True
                else:
                    destination.sent_ack[packet_index] = False
                    source.received_ack[packet_value] = False
                    time.sleep(5)  # simulate timeout 
                    print(f"Timeout! Resending packet {packet_value}...")

                    # resend lost packet
                    destination.memory[packet_index] = packet_value
                    print(f"Packet {packet_value} received by destination!")
                    destination.sent_ack[packet_index] = True
                    print(f"Sending ACK {packet_value}...")
                    source.received_ack[packet_value] = True

                time.sleep(1)
                if source.received_ack[packet_value]:
                    print(f"ACK {packet_value} received\n")

        source.window = slide_window(source.window, source.memory, source.received_ack)

    print("All packets sent and acknowledged.")
    print("Destination memory:", destination.memory)



if __name__ == "__main__":
    source = Source(8, 3)
    print("Source memory: ", source.memory)
    destination = Destination(source)
    send_packet(source, destination)


