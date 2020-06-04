package com.trillbit.myapplication.player;


public abstract class PlayerCallback {
    public void onPlayerInitiated(int status) {}
    public void onPlayStarted(int status) {}
    public void onStopPlaying(int status) {}
    public void onError(String errMessage) {}
}
