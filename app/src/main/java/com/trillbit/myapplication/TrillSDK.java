package com.trillbit.myapplication;

import android.content.Context;

import com.trillbit.myapplication.core.CWrapper;
import com.trillbit.myapplication.player.Player;
import com.trillbit.myapplication.processsor.TrillProcesssor;
import com.trillbit.myapplication.recorder.RecCallbacks;
import com.trillbit.myapplication.recorder.RecState;
import com.trillbit.myapplication.recorder.Recorder;

public class TrillSDK {
    private final Context context;
    private final CWrapper cWrapper;
    private final TrillProcesssor processor;
    private final Recorder recorder;
    private final Player player;
    private RecCallbacks rec_callback;

    private int rec_state = -1;
    private int processor_state = -1;
    private int player_state = -1;
    private TrillCallbacks trillCallbacks;

    public TrillSDK(Context context) {
        this.context = context;
        this.cWrapper = new CWrapper();
        this.processor = new TrillProcesssor(this.cWrapper);

        attach_rec_callback();
        this.recorder = new Recorder(this.rec_callback);

        this.player = new Player(context);
    }

    public void attach_callback(TrillCallbacks trillCallbacks) {
        this.trillCallbacks = trillCallbacks;
    }

    public void start() {
        this.recorder.initRecorder();
        rec_state = 0;
    }

    public void stop() {
        this.recorder.destroyRec();
        processor.stopProcess();
    }

    public void play(String payload) {
        this.player.play(payload);
    }

    public void stopPlay(String payload) {
        this.player.stop();
    }

    private void attach_rec_callback() {
        this.rec_callback = new RecCallbacks(){
            @Override
            public void onRecStateChange(int status) {
                super.onRecStateChange(status);
                if (rec_state == 0 && status == RecState.RECORDING) {
                    processor.start(trillCallbacks);
                    rec_state = 1;
                    processor_state = 1;
                } else if (rec_state == 1 && status == RecState.UNINITIALIZED) {
                    rec_state = -1;
                    processor_state = -1;
                }
            }

            @Override
            public void onBufferReceived(short[] buffer) {
                super.onBufferReceived(buffer);
                if (processor_state == 1) {
                    processor.addBuffer(buffer);
                }
            }

            @Override
            public void onError(String errMessage) {
                super.onError(errMessage);
            }
        };
    }
}
