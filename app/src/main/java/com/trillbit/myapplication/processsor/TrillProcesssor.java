package com.trillbit.myapplication.processsor;


import android.util.Log;

import com.trillbit.myapplication.TrillCallbacks;
import com.trillbit.myapplication.core.CWrapper;

public class TrillProcesssor {
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    private final CWrapper cWrapper;

    private TrillCallbacks callbacks;
    String TAG = "ProcessorThread";
    Thread ProcessorThread;
    private boolean isProcessing = false;

    private int sdkState = 0;

    public TrillProcesssor(CWrapper cWrapper) {
        this.cWrapper = cWrapper;
    }

    public void start(TrillCallbacks callback) {

        this.callbacks = callback;
        isProcessing = true;
        startProcess();

    }

    public void addBuffer(short[] buffer) {
        this.cWrapper.AddBuffer(buffer);
    }

    private void processOutput(String result) {
        int len = result.length();
        if (len > 3) {
            Log.e(TAG, "Decoded: " + result.length() + ", " + result);
            this.callbacks.onReceived(result);
        }
    }

    private void startProcess() {
        if (isProcessing && sdkState == 0) {
            sdkState = 1;
            ProcessorThread = new Thread(new Runnable() {
                @Override
                public void run() {
                    while (isProcessing) {
                        int result = cWrapper.ProcessBuffer();
//                        Log.e(TAG, "Demodulation state : "+ result);
                        String decodedString = cWrapper.GetDecodedString();
                        processOutput(decodedString);
                    }
                    sdkState = 0;
                    ProcessorThread.interrupt();
                    ProcessorThread = null;
                }
            });

            ProcessorThread.start();
        }

    }

    public void stopProcess() {
        isProcessing = false;

    }
}