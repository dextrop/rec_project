package com.trillbit.myapplication.player;

import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;

public class PlayerConf {
    /**
     *  Player Config.
     */
    public static final int PLAYER_MODE = AudioTrack.MODE_STATIC;
    public static final int PLAYER_STREAM_TYPE = AudioManager.STREAM_MUSIC;
    public static final int PLAYER_FORMAT = AudioFormat.ENCODING_PCM_FLOAT;
    public static final int PLAYER_CONF = AudioFormat.CHANNEL_OUT_MONO;
    public static final int PLAYER_SR = 44100;
}
