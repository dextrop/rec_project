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
    private static native void resetDecodedString();
    private static native void setExpectedData(String expectedData);

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

    public void ResetDecodedString() { resetDecodedString();}

    public void SetExpectedData(String expectedPayload) {setExpectedData(expectedPayload);}
}
