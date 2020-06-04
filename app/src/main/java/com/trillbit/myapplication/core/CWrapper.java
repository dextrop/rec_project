package com.trillbit.myapplication.core;

public class CWrapper {
    static {
        System.loadLibrary("native-lib");
    }
    private static native void setUp();
    private static native float[] getAudioSamples(String payload);
    private static native void addBuffer(short [] samples, int len);
    private static native String processBuffer();

    public CWrapper() {
        setUp();
    }

    public float[] GenerateSamples(String payload) {
        return getAudioSamples(payload);
    }

    public void AddBuffer(short[] samples) {
        addBuffer(samples, samples.length);
    }

    public String ProcessBuffer() {
        return processBuffer();
    }
}
