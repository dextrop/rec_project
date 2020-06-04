package com.trillbit.myapplication;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    TrillSDK trillSDK;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

    }


    public void start_play(View v) {
        trillSDK.play("abcdef");
    }

    public void stop_play(View v) {
        trillSDK.stop();
    }

    public void start_rec(View v) {
        trillSDK.start();
    }

    public void stop_rec(View v) {
        trillSDK.stop();
    }

    public void initSDK() {
        trillSDK = new TrillSDK(this);
        trillSDK.attach_callback(new TrillCallbacks() {
            @Override
            public void onSDKReady(int status) {
                super.onSDKReady(status);
            }

            @Override
            public void onReceived(String payload) {
                super.onReceived(payload);
            }

            @Override
            public void onError(String errMessage) {
                super.onError(errMessage);
            }
        });

    }

    @Override
    protected void onResume() {
        super.onResume();
        String [] neededPermissions = {
                Manifest.permission.MODIFY_AUDIO_SETTINGS,
                Manifest.permission.RECORD_AUDIO
        };

        if ( ContextCompat.checkSelfPermission ( this, Manifest.permission.RECORD_AUDIO ) != PackageManager.PERMISSION_GRANTED ) {
            ActivityCompat.requestPermissions ( this, neededPermissions, 1 ) ;
        } else {
            initSDK();
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        initSDK();
    }
}
