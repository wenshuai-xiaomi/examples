import wave
import os
from pydub import AudioSegment
from pydub.silence import split_on_silence
import hashlib
import random
import argparse
import sys

FLAGS = None

def split_wav():
    sound = AudioSegment.from_file(FLAGS.input_wav, format="wav")
    # sound = sound[:3*60*1000] #如果文件较大，先取前3分钟测试，根据测试结果，调整参数
    duration = sound.duration_seconds * 1000  # 音频时长（ms）
    print(sound.duration_seconds)
    num = sound.duration_seconds / FLAGS.input_slip_s  #切割成多少个文件
    file_num = int(num)
    print('wav file num = ', num, 'loss 1')

    filepath = os.path.split(FLAGS.input_wav)[0]  #获取当前处理音频的路径
    cuts_path = filepath + '/cuts/'
    print(cuts_path)

    if not os.path.isdir(cuts_path):
        os.makedirs(cuts_path)

    md5 = hashlib.md5()

    for i in range(file_num):
        begin = 0 + FLAGS.input_slip_s * i * 1000
        end = begin + FLAGS.input_slip_s * 1000

        if end / 1000 > file_num:
            end = sound.duration_seconds * 1000

        print('begin= ', begin, 'end= ', end)

        md5.update((cuts_path + str(i) +
                    str(random.randint(0, 10000))).encode('utf-8'))
        cut_file_path = cuts_path + md5.hexdigest() + '.wav'

        cut_wav = sound[begin:end]  #以毫秒为单位截取[begin, end]区间的音频

        cut_wav.export(cut_file_path, format='wav')  #存储新的wav文件
    print('保存完毕')


def main():
    split_wav()


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--input_wav',
                        type=str,
                        default=None,
                        help='Path to a wav file to split')

    parser.add_argument('--input_slip_s',
                        type=int,
                        default=1,
                        help='slipped lengh')

    # FLAGS: namespace, what's type? what's unparsed?
    FLAGS, unparsed = parser.parse_known_args()
    print('FLAGS: {0}, unparsed: {1}, program name: {2}'.format(
        FLAGS, unparsed, sys.argv[0]))
    main()
