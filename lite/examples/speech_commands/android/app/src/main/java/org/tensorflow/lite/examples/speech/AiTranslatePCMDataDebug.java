package org.tensorflow.lite.examples.speech;

import android.os.Handler;
import android.os.HandlerThread;
import android.util.Log;

import java.io.FileOutputStream;
import java.io.IOException;


public class AiTranslatePCMDataDebug {
  public static final String TAG = "wenshuai";

  private FileOutputStream mFileOutputStream;
  private HandlerThread mWorkThread = null;
  private Handler mWorkThreadHandler = null;

  public AiTranslatePCMDataDebug(FileOutputStream outputStream) {
    mFileOutputStream = outputStream;
    mWorkThread = new HandlerThread("record-pcm-data");
    mWorkThread.start();
    mWorkThreadHandler = new Handler(mWorkThread.getLooper());
  }

  public void storeAudioData2File(final byte[] buffer, final int cntRead) {

    if (mWorkThread != null) {
      final byte[] data = new byte[cntRead];
      System.arraycopy(buffer, 0, data, 0, cntRead);

      mWorkThreadHandler.post(new Runnable() {
        @Override
        public void run() {
          try {
            mFileOutputStream.write(data);
          } catch (IOException e) {
            Log.e(TAG, "" + e);
          }
        }
      });
    }
  }

  public void endAudioData2File(String pcmFile) {
    if (mWorkThread != null) {
      mWorkThreadHandler.post(new Runnable() {
        @Override
        public void run() {
          try {
            mFileOutputStream.close();
            String waveFile = pcmFile.replace(".pcm", ".wav");
            Log.v(TAG, "wav file name: " + waveFile);
            WaveFileUtils.copyWaveFile(pcmFile, waveFile, 16000, 16, 1);
          } catch (IOException e) {
            Log.e(TAG, "" + e);
          }
          mWorkThread.quitSafely();
        }
      });
    }
  }
}
