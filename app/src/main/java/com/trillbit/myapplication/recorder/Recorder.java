package com.trillbit.myapplication.recorder;

import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.util.Log;

public class Recorder {

    private final RecCallbacks recCallbacks;
    private AudioRecord recorder;
    private Thread collectorThread;
    private int bufferSize;
    private int recState;
    RecorderErrorHandler recErrorHandler;

    int wait_for = 3;

    public Recorder(RecCallbacks recCallbacks) {
        this.recCallbacks = recCallbacks;
        recState = RecState.UNINITIALIZED;
        recErrorHandler = new RecorderErrorHandler(this.recCallbacks);
    }

    public int getState() {
        /*
         * return current recorder state
         */
        return recState;
    }

    public void initRecorder() {
        if (recState == RecState.UNINITIALIZED) {
            recState = RecState.INITIALIZING;

            /*
             * Get device minimum buffer size
             */
            bufferSize = AudioRecord.getMinBufferSize(44100, AudioFormat.CHANNEL_IN_MONO, AudioFormat.ENCODING_PCM_16BIT);

            /*
             * Initialize recorder with configuration
             */
            recorder = new AudioRecord(
                    MediaRecorder.AudioSource.DEFAULT,
                    44100,
                    AudioFormat.CHANNEL_IN_MONO,
                    AudioFormat.ENCODING_PCM_16BIT,
                    bufferSize);

            /*
             * Adding noise suppressor
             */
//            int sessionId = recorder.getAudioSessionId();
//            NoiseSuppressor.create(sessionId);
            int recorderState = recorder.getState();

            /*
             * Check if recorder is properly INITIALIZED
             */
            if (recorderState == AudioRecord.STATE_INITIALIZED) {
                try {
                    /*
                     * if AudioRecord is INITIALIZED properly
                     * change recording state to RecState.INITIALIZED
                     */
                    recState = RecState.INITIALIZED;
                    this.recCallbacks.onRecStateChange(recState);
                    startRecorder();

                } catch (Exception e) {
                    /*
                     * if AudioRecord is not INITIALIZED properly
                     * return error
                     */
                    e.printStackTrace();
                    this.recCallbacks.onError("Unable to INITIALIZED recorder, check permissions");
                    this.recCallbacks.onRecStateChange(RecState.UNINITIALIZED);
                }
            } else {

            }
        } else {
            recErrorHandler.handleError("init", recState);
        }
    }

    public void startRecorder() {
        /*
         * Start Recorder and Collection Thread
         */

        if (recState == RecState.INITIALIZED) {
            recorder.startRecording();
            recState = RecState.STARTING_RECORDER;
            Log.e("Stating Recorder", "Recorder Class " + recState);
            collectorThread = new Thread() {
                @Override
                public void run() {
                    try {

                        do {
                            try {
                                short[] currentBuffer = new short[bufferSize];
                                int record = recorder.read(currentBuffer, 0, bufferSize);

                                if (record < 0) {
                                    Log.e("Buffer Unavalible ", "Buffer Size Obtained: " + record);
                                } else {
                                    if (bufferSize != record) {
                                        Log.e("Buffer Size Error", "Buffer Size Obtained: " + record + " Buffer Size Set : " + bufferSize);
                                        bufferSize = record;
                                    }

                                    /*
                                     * Check if recorder is able to start recording.
                                     */
                                    if (recState == RecState.STARTING_RECORDER) {
                                        if (record == 0) {
                                            recState = RecState.INITIALIZED;
                                            recErrorHandler.handleError("rec_in_use", recState);
                                            Log.e("Rec Not Started", "Unable to Start Recorder");
                                            break;
                                        } else {
                                            recState = RecState.RECORDING;
                                            recCallbacks.onRecStateChange(recState);
                                        }
                                    }

                                    /*
                                     * Callback to send recording buffer.
                                     */
                                    recCallbacks.onBufferReceived(currentBuffer);
                                }



                            } catch (OutOfMemoryError e) {

                                e.printStackTrace();
                                System.gc();
                            }
                        } while (recState == RecState.RECORDING);

                        /*
                         * Once the recording state is changed from RecState.RECORDING
                         * interrupt collector Thread and mark it null.
                         */
                        collectorThread.interrupt();
                        collectorThread = null;
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            };
            collectorThread.start();
        } else {
            recErrorHandler.handleError("start", recState);
        }
    }

    public void stopRecorder() {
        /*
         * Stop Recording, but recorder will not be
         * released and same recorder can be used again
         */
        if (recState == RecState.RECORDING) {
            recorder.stop();
            recState = RecState.INITIALIZED;
            destroyRec();
            recCallbacks.onRecStateChange(RecState.INITIALIZED);
        } else {
            recErrorHandler.handleError("stop", recState);
        }
    }

    public void destroyRec() {
        /*
         * Stop Recording,
         * released recorder and mark it null
         */
        if (recState == RecState.RECORDING) {
            recState = RecState.UNINITIALIZED;
            stopRecorder();
            recorder.release();
            recorder = null;
            recCallbacks.onRecStateChange(RecState.UNINITIALIZED);
        }
        else if (recState == RecState.INITIALIZED) {
            recorder.release();
            recorder = null;

            recState = RecState.UNINITIALIZED;
            recCallbacks.onRecStateChange(RecState.UNINITIALIZED);
        } else {
            recErrorHandler.handleError("destroy", recState);
        }
    }


}
