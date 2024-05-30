import socket

def create_order(key):
    return [sorted(key).index(char) + 1 for char in key]

def encrypt(key, message):
    order = create_order(key)
    num_cols = len(key)
    num_rows = (len(message) + num_cols - 1) // num_cols

    padded_message = message + ''.join(chr(97 + i % 26) for i in range(num_cols * num_rows - len(message)))

    matrix = [padded_message[i * num_cols:(i + 1) * num_cols] for i in range(num_rows)]

    encrypted_text = ''
    for col in range(num_cols):
        col_index = order.index(col + 1)
        for row in range(num_rows):
            encrypted_text += matrix[row][col_index]

    return encrypted_text

def start_client(message, key, host='127.0.0.1', port=65432):
    encrypted_message = encrypt(key, message)
    data_to_send = f'{encrypted_message}||{key}'
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((host, port))
        s.sendall(data_to_send.encode('utf-8'))
        print(f'Encrypted message sent: {encrypted_message}')

if __name__ == '__main__':
    key = 'salut'
    message = input('Enter the message: ')
    start_client(message, key)

