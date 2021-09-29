import wave
import os
from pydub import AudioSegment
from pydub.silence import split_on_silence
import hashlib

# 初始化
audiopath = "/home/ws/datasets/backup/pcms/wavsfromBC/back_ground/20210929-101043358.wav"
audiotype = 'wav' #如果wav、mp4其他格式参看pydub.AudioSegment的API

cut_time=1  #音频切割间隔1s

# 读入音频
print('读入音频')
sound = AudioSegment.from_file(audiopath, format=audiotype)
# sound = sound[:3*60*1000] #如果文件较大，先取前3分钟测试，根据测试结果，调整参数
duration = sound.duration_seconds * 1000  # 音频时长（ms）
print(sound.duration_seconds)
num=sound.duration_seconds/cut_time     #切割成多少个文件
file_num=int(num)
print('wav file num = ',num, 'loss 1')

filepath = os.path.split(audiopath)[0]  #获取当前处理音频的路径
cuts_path = filepath + '/cuts/'
print(cuts_path)

if not os.path.isdir(cuts_path):
        os.makedirs(cuts_path)

md5 = hashlib.md5()

for i in range(file_num):     #加1是因为分割数可能是小数
    begin = 0 + cut_time * i *1000
    end = begin + cut_time * 1000

    if end/1000 > file_num:
        end = sound.duration_seconds*1000

    print('begin= ', begin, 'end= ', end)

    md5.update((cuts_path + str(i)).encode('utf-8'))
    cut_file_path = cuts_path + md5.hexdigest() + '.wav'
    
    cut_wav = sound[begin:end]   #以毫秒为单位截取[begin, end]区间的音频

    cut_wav.export(cut_file_path, format='wav')   #存储新的wav文件
print('保存完毕')

