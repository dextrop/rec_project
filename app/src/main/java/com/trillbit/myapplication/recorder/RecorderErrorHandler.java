package com.trillbit.myapplication.recorder;

public class RecorderErrorHandler {

    private final RecCallbacks recCallbacks;

    public RecorderErrorHandler(RecCallbacks recCallbacks) {
        this.recCallbacks = recCallbacks;
    }

    public void handleError(String event, int recState) {
        if (event.equals("init")) {
            if (recState >= RecState.INITIALIZED) {
                recCallbacks.onError("Recorder instance already created");
            }

            if (recState == RecState.INITIALIZING) {
                recCallbacks.onError("Recorder instance creation in process");
            }
        }

        if (event.equals("start")) {
            if (recState == RecState.UNINITIALIZED) {
                recCallbacks.onError("No Recorder instance found");
            }

            if (recState == RecState.INITIALIZING) {
                recCallbacks.onError("Recorder instance creation in process");
            }

            if (recState == RecState.STARTING_RECORDER) {
                recCallbacks.onError("Recorder starting still in progress");
            }

            if (recState == RecState.RECORDING) {
                recCallbacks.onError("Recorder already in progress");
            }
        }

        if (event.equals("stop")) {
            if (recState == RecState.UNINITIALIZED) {
                recCallbacks.onError("No Recorder instance found");
            }

            if (recState == RecState.INITIALIZING) {
                recCallbacks.onError("Recorder instance creation in process");
            }

            if (recState == RecState.STARTING_RECORDER) {
                recCallbacks.onError("Recorder starting still in progress");
            }

            if (recState == RecState.INITIALIZED) {
                recCallbacks.onError("Recorder not recording");
            }
        }

        if (event.equals("destroy")) {
            if (recState == RecState.UNINITIALIZED) {
                recCallbacks.onError("No Recorder instance found");
            }

            if (recState == RecState.INITIALIZING) {
                recCallbacks.onError("Recorder instance creation in process");
            }

            if (recState == RecState.STARTING_RECORDER) {
                recCallbacks.onError("Recorder starting still in progress");
            }
        }

        if (event.equals("rec_in_use")) {
            recCallbacks.onError("Recorder already in use");
        }

    }
}
