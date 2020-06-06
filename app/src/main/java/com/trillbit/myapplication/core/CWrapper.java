package com.trillbit.myapplication.core;

public class CWrapper {
    static {
        System.loadLibrary("native-lib");
    }
    private static native void setUp();
    private static native float[] getAudioSamples(String payload);
    private static native void addBuffer(short [] samples, int len);
    private static native int processBuffer();
    private static native String getDecodedString();

    public CWrapper() {
        setUp();
    }

    public float[] GenerateSamples(String payload) {
        return getAudioSamples(payload);
    }

    public void AddBuffer(short[] samples) {
        addBuffer(samples, samples.length);
    }

    public int ProcessBuffer() {
        return processBuffer();
    }

    public String GetDecodedString() { return getDecodedString();}
}
