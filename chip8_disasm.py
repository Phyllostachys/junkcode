import os, sys

if len(sys.argv) == 1:
    sys.exit(-1)

f = open(sys.argv[1], 'rb')

# get file size
filesize = f.seek(0,2)
f.seek(0,0)
print("File size:", filesize)
if filesize % 2 == 0:
    filesize = (filesize >> 1)
else:
    filesize = (filesize >> 1) + 1

# iterate over data
for i in range(filesize):
    byte = 0
    try:
        byte = int.from_bytes(f.read(2), 'big')
    except:
        break

    # 0x00E0 - CLS
    if byte == 0x00E0:
        print("{:3d}".format(i), "0x{0:04X}".format(byte), "\t", "CLS")

    # 0x00EE - RET
    elif byte == 0x00EE:
        print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "RET")

    # 0x0nnn - SYS addr
    elif (byte >> 12) == 0x0:
        print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "SYS 0x{0:03X}".format(byte & 0xFFF))

    # 0x1nnn - JP addr
    elif (byte >> 12) == 0x1:
        print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "JP {}\t\t".format(byte & 0xFFF))

    # 0x2nnn - CALL addr
    elif (byte >> 12) == 0x2:
        print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "CALL 0x{0:03X}".format(byte & 0xFFF))

    # 0x3xkk - SE Vx, byte
    elif (byte >> 12) == 0x3:
        print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "SE V{},".format(byte >> 8 & 0xF), "0x{0:02X}".format(byte & 0xFF))

    # 0x4xkk - SNE Vx, byte
    elif (byte >> 12) == 0x4:
        print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "SNE V{},".format(byte >> 8 & 0xF), "0x{0:02X}".format(byte & 0xFF))

    # 0x5xy0 - SE Vx, Vy
    elif ((byte >> 12) == 0x5) and ((byte & 0xF) == 0):
        print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "SE V{},".format(byte >> 8 & 0xF), "V{}".format((byte >> 4) & 0xF))

    # 0x6xkk - LD Vx, byte
    elif ((byte >> 12) == 0x6):
        print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "LD V{},".format(byte >> 8 & 0xF), "0x{0:02X}".format(byte & 0xFF))

    # 0x7xkk - ADD Vx, byte
    elif ((byte >> 12) == 0x7):
        print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "ADD V{},".format(byte >> 8 & 0xF), "0x{0:02X}".format(byte & 0xFF))

    elif (byte >> 12 == 0x8):
        # 0x8xy0 - LD Vx, Vy
        if byte & 0xF == 0:
            print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "LD V{},".format(byte >> 8 & 0xF), "V{}".format(byte >> 4 & 0xF))

        # 0x8xy1 - OR Vx, Vy
        elif byte & 0xF == 0x1:
            print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "OR V{},".format(byte >> 8 & 0xF), "V{}".format(byte >> 4 & 0xF))

        # 0x8xy2 - AND Vx, Vy
        elif byte & 0xF == 0x1:
            print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "AND V{},".format(byte >> 8 & 0xF), "V{}".format(byte >> 4 & 0xF))

        # 0x8xy3 - XOR Vx, Vy
        elif byte & 0xF == 0x1:
            print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "XOR V{},".format(byte >> 8 & 0xF), "V{}".format(byte >> 4 & 0xF))

        # 0x8xy4 - ADD Vx, Vy
        elif byte & 0xF == 0x1:
            print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "ADD V{},".format(byte >> 8 & 0xF), "V{}".format(byte >> 4 & 0xF))

        # 0x8xy5 - SUB Vx, Vy
        elif byte & 0xF == 0x1:
            print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "SUB V{},".format(byte >> 8 & 0xF), "V{}".format(byte >> 4 & 0xF))

        # 0x8xy6 - SHR Vx {, Vy}
        elif byte & 0xF == 0x1:
            print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "SHR V{},".format(byte >> 8 & 0xF), "V{}".format(byte >> 4 & 0xF))

        # 0x8xy7 - SUBN Vx, Vy
        elif byte & 0xF == 0x1:
            print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "SUBN V{},".format(byte >> 8 & 0xF), "V{}".format(byte >> 4 & 0xF))

        # 0x8xyE - SHL Vx {, Vy}
        elif byte & 0xF == 0x1:
            print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "SHL V{},".format(byte >> 8 & 0xF), "V{}".format(byte >> 4 & 0xF))

    # 0x9xy0 - SNE Vx, Vy
    elif ((byte >> 12) == 0x9) and (byte & 0xF == 0):
        print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "SNE V{},".format(byte >> 8 & 0xF), "V{}".format(byte >> 4 & 0xF))

    # 0xAnnn - LD I, addr
    elif (byte >> 12) == 0xA:
        print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "LD I, 0x{0:03X}".format(byte & 0xFFF))

    # 0xBnnn - JP V0, addr
    elif (byte >> 12) == 0xB:
        print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "JP V0, {}".format(byte & 0xFFF))

    # 0xCxkk - RND Vx, byte
    elif ((byte >> 12) == 0xC):
        print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "RND V{},".format(byte >> 8 & 0xF), "0x{0:02X}".format(byte & 0xFF))

    # 0xDxyn - DRW Vx, Vy, nibble
    elif ((byte >> 12) == 0xD):
        print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "DRW V{},".format(byte >> 8 & 0xF), "V{},".format(byte >> 4 & 0xF), "0x{0:01X}".format(byte & 0xF))

    # 0xEx9E - SKP Vx
    elif (byte >> 12 == 0xE) and (byte & 0xFF == 0x9E):
        print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "SKP V{}".format(byte >> 8 & 0xF))

    # 0xExA1 - SKNP Vx
    elif (byte >> 12 == 0xE) and (byte & 0xFF == 0xA1):
        print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "SKNP V{}".format(byte >> 8 & 0xF))

    # 0xFx07 - LD Vx, DT
    elif ((byte >> 12) == 0xF) and ((byte & 0xFF) == 0x07):
        print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "LD V{}, DT".format(byte >> 8 & 0xF))

    # 0xFx0A - LD Vx, K
    elif ((byte >> 12) == 0xF) and ((byte & 0xFF) == 0x0A):
        print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "LD V{}, K".format(byte >> 8 & 0xF))

    # 0xFx15 - LD DT, Vx
    elif ((byte >> 12) == 0xF) and ((byte & 0xFF) == 0x15):
        print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "LD DT, V{}".format(byte >> 8 & 0xF))

    # 0xFx18 - LD ST, Vx
    elif ((byte >> 12) == 0xF) and ((byte & 0xFF) == 0x18):
        print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "LD ST, V{}".format(byte >> 8 & 0xF))

    # 0xFx1E - ADD I, Vx
    elif ((byte >> 12) == 0xF) and ((byte & 0xFF) == 0x1E):
        print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "ADD I, V{}".format(byte >> 8 & 0xF))

    # 0xFx29 - LD F, Vx
    elif ((byte >> 12) == 0xF) and ((byte & 0xFF) == 0x29):
        print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "LD F, V{}".format(byte >> 8 & 0xF))

    # 0xFx33 - LD B, Vx
    elif ((byte >> 12) == 0xF) and ((byte & 0xFF) == 0x33):
        print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "LD B, V{}".format(byte >> 8 & 0xF))

    # 0xFx55 - LD [I], Vx
    elif ((byte >> 12) == 0xF) and ((byte & 0xFF) == 0x55):
        print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "LD [I], V{}".format(byte >> 8 & 0xF))

    # 0xFx65 - LD Vx, [I]
    elif ((byte >> 12) == 0xF) and ((byte >> 4) & 0xF == 0x6) and (byte & 0xF == 0x5):
        print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "LD V{}, [I]".format(byte >> 8 & 0xF))

    else:
        print("{:3d}\t".format(i), "0x{0:04X}".format(byte), "\t", "NOP")
