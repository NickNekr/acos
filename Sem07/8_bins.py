import struct

with open('file.bin', 'wb') as f:
    f.write(struct.pack('<i4xd', 42, 3.5))
