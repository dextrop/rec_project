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

    int DECODE_STATE = 0;


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

    private void processOutput(int result) {
        if (result == 1 && DECODE_STATE == 0) {
            Log.e(TAG, "CTS Detected");
            DECODE_STATE = 1;
        } else if (result == 2 && DECODE_STATE == 1) {
            Log.e(TAG, "FTS Detected");
            DECODE_STATE = 2;
        } else if (result == 3 && DECODE_STATE == 2) {
            String decodedString = cWrapper.GetDecodedString();
            cWrapper.ResetDecodedString();
            this.callbacks.onReceived(decodedString);
            DECODE_STATE = 0;
            Log.e(TAG, "Data Decoded " + decodedString);
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
                        processOutput(result);
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