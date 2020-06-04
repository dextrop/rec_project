package com.trillbit.myapplication.player;

import android.annotation.TargetApi;
import android.content.Context;
import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;
import android.os.Build;
import android.util.Log;

import androidx.annotation.RequiresApi;

import com.trillbit.myapplication.core.CWrapper;


public class Player {
    final AudioManager audioManager;

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }


    private final Context context;
    private final config player_config;
    private boolean setAudioLevel = true;
    private String TAG = "TrillPlayer";

    AudioTrack track;
    int max_play = 50;
    int play_counter = 0;
    CWrapper cWrapper;
    public class config {
        double volume_normal = -1;
        public double volume_player = .8;
        boolean is_playing = false;

        public void set_vol_normal(double vol_normal) {
            this.volume_normal = vol_normal;
        }

        public double get_vol_normal() {
            return this.volume_normal;
        }

        public double get_vol_playing() {
            return this.volume_player;
        }

        public void change_player_state() {
            this.is_playing = !this.is_playing;
        }

        public boolean get_player_state() {
            return this.is_playing;
        }

    }

    public Player(Context context) {
        this.context = context;
        this.player_config = new config();
        this.audioManager = (AudioManager) this.context.getSystemService(Context.AUDIO_SERVICE);
        this.cWrapper = new CWrapper();
    }

    private void set_player_volume(double volume_variable) {
        int volume_change = (int) (audioManager.getStreamMaxVolume(AudioManager.STREAM_MUSIC) * volume_variable);
        audioManager.setStreamVolume(AudioManager.STREAM_MUSIC, volume_change, 0);
    }

    @RequiresApi(api = Build.VERSION_CODES.LOLLIPOP)
    private void playAudio(final float[] audio_samples) {
        if (this.player_config.get_player_state()) {
            int length = audio_samples.length;
            Log.e(TAG, "Length =>  " + length);
            set_player_volume(0.9);
            int PLAYER_MODE = AudioTrack.MODE_STATIC;
            int PLAYER_STREAM_TYPE = AudioManager.STREAM_MUSIC;
            int PLAYER_FORMAT = AudioFormat.ENCODING_PCM_FLOAT;
            int PLAYER_CONF = AudioFormat.CHANNEL_OUT_MONO;
            int PLAYER_SR = 44100;
            track = new AudioTrack(PLAYER_STREAM_TYPE, PLAYER_SR, PLAYER_CONF, PLAYER_FORMAT, audio_samples.length * 4, PLAYER_MODE);

            track.write(audio_samples, 0, length, AudioTrack.WRITE_NON_BLOCKING);
            track.setNotificationMarkerPosition(length);
            track.setPlaybackPositionUpdateListener(new AudioTrack.OnPlaybackPositionUpdateListener() {


                @Override
                public void onMarkerReached(AudioTrack track) {
                    Log.e(TAG, "Playing Completed");
                    if (play_counter <= max_play ) {
                        track.stop();
                        track.release();
                        playAudio(audio_samples);
                        play_counter += 1;
                    }


                }

                @Override
                public void onPeriodicNotification(AudioTrack track) {

                }
            });
            track.play();
        }
    }

    @TargetApi(Build.VERSION_CODES.LOLLIPOP)
    public void play(String payload) {
        if (!this.player_config.get_player_state()) {
            this.player_config.change_player_state();
            if (setAudioLevel) {
                set_player_volume(this.player_config.get_vol_playing());
            }


            float[] audio = this.cWrapper.GenerateSamples(payload);
            if (audio.length < 1000) {
                this.player_config.change_player_state();
                Log.e(TAG, "Unable to generate audio");
                return;
            }
            int wait_for = 3 * 44100;
            float[] final_audio = new float[audio.length + wait_for];

            for (int i = 0; i < audio.length + wait_for; i++) {
                if (i < audio.length) {
                    final_audio[i] = audio[i];
                } else {
                    final_audio[i] = 0;
                }
            }
            playAudio(final_audio);
        } else {
            Log.e(TAG, "Player Already Playing....");
        }
    }

    public void stop() {
        if (this.player_config.get_player_state()) {
            track.stop();
            track.release();
            track = null;
            this.player_config.change_player_state();
            if (setAudioLevel) {
                double normal_volumne = this.player_config.get_vol_normal();
                if (normal_volumne > 0)
                    set_player_volume(normal_volumne);
            }
        } else {
            Log.e(TAG, "Nothing Playing");
        }
    }
}
