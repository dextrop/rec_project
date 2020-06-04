package com.trillbit.myapplication;

public abstract class TrillCallbacks {
    public void onSDKReady(int status) {}
    public void onReceived(String payload) {}
    public void onError(String errMessage) {}
}
