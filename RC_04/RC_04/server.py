import socket

def create_order(key):
    return [sorted(key).index(char) + 1 for char in key]

def decrypt(key, encrypted_text):
    order = create_order(key) # order of the columns based on alphabetical order of the key
    num_cols = len(key)
    num_rows = len(encrypted_text) // num_cols

    cols = [''] * num_cols # list of empty strings, one for each column
    col_lengths = [num_rows] * num_cols # chars per column

    index = 0
    for i in range(num_cols):
        col_index = order.index(i + 1)
        cols[col_index] = encrypted_text[index:index + col_lengths[i]]
        index += col_lengths[i] # move to the next segment of the encrypted text

    decrypted_text = ''
    for row in range(num_rows):
        for col in range(num_cols):
            decrypted_text += cols[col][row]      

    return decrypted_text

def start_server(host='127.0.0.1', port=65432):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((host, port))
        s.listen()
        print(f'Server listening on {host}:{port}')
        conn, addr = s.accept()
        with conn:
            print(f'Connected by {addr}')
            print("\n\n")
            data = conn.recv(2048).decode('utf-8')
            if data:
                encrypted_message, key = data.split('||')
                print(f'Encrypted message received: {encrypted_message}')
                print(f'Key received: {key}')
                decrypted_message = decrypt(key, encrypted_message)
                print(f'Decrypted message: {decrypted_message}')

if __name__ == '__main__':
    start_server()