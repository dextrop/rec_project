package com.trillbit.myapplication.recorder;

public class RecState {
    /**
     *  indicates AudioRecord state is not successfully initialized.
     */
    public static final int UNINITIALIZED = 0;
    /**
     *  indicates AudioRecord state is ready to be used
     */
    public static final int INITIALIZING   = 1;

    /**
     *  indicates AudioRecord state is ready to be used
     */
    public static final int INITIALIZED   = 2;

    /**
     * indicates AudioRecord recording state is not recording
     */
    public static final int STARTING_RECORDER = 3;

    /**
     * indicates AudioRecord recording state is recording
     */
    public static final int RECORDING = 4;
}
