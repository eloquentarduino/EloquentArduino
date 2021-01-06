from serial import Serial


if __name__ == '__main__':
    with Serial('/dev/cu.usbserial-01BB622A', baudrate=115200) as camera:
        idx = 0
        buffer = ''
        jpeg = None

        while True:
            try:
                line = camera.readline().decode('utf-8').strip()
                if line == 'START OF FRAME':
                    print('new frame')
                    jpeg = []
                    text = ''
                    while True:
                        byte = camera.read(1)
                        jpeg.append(byte)
                        try:
                            text += byte.decode('utf-8')
                            if text.endswith('END OF FRAME'):
                                with open('frame%d.jpg' % idx, 'wb') as file:
                                    for byte in jpeg[:-len('END OF FRAME')]:
                                        file.write(byte)
                                print('done', idx)
                                idx += 1
                                break
                        except UnicodeDecodeError:
                            pass
            except UnicodeDecodeError:
                pass