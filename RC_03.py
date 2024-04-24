import threading
import time

class Source(threading.Thread):
    def __init__(self, destination):
        super().__init__()
        self.destination = destination
        self.window_size = 3
        self.packets = list(range(1, 8))
        self.unacknowledged = []
        self.lock = threading.Lock()

    def run(self):
        while self.packets or self.unacknowledged:
            with self.lock:
                while len(self.unacknowledged) < self.window_size and self.packets:
                    packet = self.packets.pop(0)
                    self.unacknowledged.append(packet)
                    print(f"Sending packet {packet}")
                    self.destination.receive(packet)

    def ack_received(self, ack):
        with self.lock:
            if ack in self.unacknowledged:
                self.unacknowledged.remove(ack)
                print(f"Acknowledgement {ack} received")
            if len(self.unacknowledged) == 0 and self.packets:
                self.run()

class Destination(threading.Thread):
    def __init__(self):
        super().__init__()
        self.received_packets = []

    def receive(self, packet):
        time.sleep(1)  # Simulating network delay
        self.received_packets.append(packet)
        print(f"Packet {packet} received")
        self.send_ack(packet)

    def send_ack(self, packet):
        print(f"Sending ACK {packet}")
        source.ack_received(packet)

    def run(self):
        pass  # Destination doesn't have an active role

source = Source(Destination())
destination = source.destination

source.start()
destination.start()

source.join()
destination.join()

print("All packets sent and acknowledged")
