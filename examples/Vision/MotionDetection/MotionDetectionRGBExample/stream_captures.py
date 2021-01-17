import numpy as np
from serial import Serial
from PIL import Image


def infer_size(arr, ratio):
    """
    Try to infer image sizes given the ratio width / height
    :param arr:
    :param ratio:
    :return:
    """
    for height in range(2, 129, 2):
        width = int(height * ratio)
        size = width * height
        if size == len(arr):
            return width, height
    raise AssertionError('Cannot find image size (len=%d, ratio=%.2f)' % (len(arr), ratio))


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
                                with open('captures/frame%d.jpg' % idx, 'wb') as file:
                                    for byte in jpeg[:-len('END OF FRAME')]:
                                        file.write(byte)
                                print('done', idx)
                                idx += 1
                                break
                        except UnicodeDecodeError:
                            pass
                elif line == 'START OF DOWNSCALED':
                    print('new downscaled')
                    raw = camera.readline().decode('utf-8').strip()
                    arr = np.asarray([int(pixel) for pixel in raw.split(',')], dtype=np.uint8)
                    w, h = infer_size(arr, 4/3)
                    img = arr.reshape((h, w))
                    img = Image.fromarray(img, 'L')
                    img.save('downscaled/%d.jpg' % idx)
                    print('done', idx)
                    idx += 1

            except UnicodeDecodeError:
                pass