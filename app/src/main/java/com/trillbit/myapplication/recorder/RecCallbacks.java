package com.trillbit.myapplication.recorder;


public abstract class RecCallbacks {
    public void onRecStateChange(int status) {}
    public void onBufferReceived(short[] buffer) {}
    public void onError(String errMessage) {}

}
