package com.trillbit.myapplication.network;

import android.annotation.SuppressLint;
import android.content.Context;
import android.provider.Settings;
import android.util.Log;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.URL;


public class HTTPS {

    private final Context context;

    public HTTPS(Context context) {
        this.context = context;
    }

    public void postReq(final String url, final JSONObject jsonDataObject, final NetworkCallbacks InternalCallbacks){
        Thread postRequest = new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject jsonObject = null;
                    URL obj = new URL(url);
                    HttpURLConnection con = (HttpURLConnection) obj.openConnection();
                    con.setRequestMethod("POST");
                    con.setRequestProperty ("Content-Type", "application/json");

                    OutputStream os = con.getOutputStream();
                    BufferedWriter writer = new BufferedWriter(
                            new OutputStreamWriter(os, "UTF-8"));
                    writer.write(String.valueOf(jsonDataObject));
                    writer.flush();
                    writer.close();
                    os.close();


                    Log.e("Sending request", url);

                    int responseCode = con.getResponseCode();

                    if (responseCode == HttpURLConnection.HTTP_OK) { // success
                        BufferedReader in = new BufferedReader(new InputStreamReader(
                                con.getInputStream()));
                        String inputLine;
                        StringBuffer response = new StringBuffer();


                        while ((inputLine = in.readLine()) != null) {
                            response.append(inputLine);
                        }
                        in.close();

                        try {
                            jsonObject = new JSONObject(String.valueOf(response));
                            InternalCallbacks.workStatus(200, jsonObject);
                        } catch (JSONException e) {
                            e.printStackTrace();

                        }
                    } else {
                        InternalCallbacks.workStatus(401, null);

                    }
                } catch (IOException e) {

                } catch (JSONException e) {
                    e.printStackTrace();
                }
            }
        });

        postRequest.start();
    }

    public void sendSamplesToServer(short[] samples) {
        String server_url = "http://192.168.0.5:8081/v1/welcome/";
        JSONObject jsonObject = new JSONObject();
        @SuppressLint("HardwareIds") String android_id = Settings.Secure.getString(context.getContentResolver(),
                Settings.Secure.ANDROID_ID);
        JSONArray jsonArray = new JSONArray();
        for (int i=0; i<samples.length; i++) {
            try {
                jsonArray.put(samples[i]/32768.0);
            } catch (JSONException e) {
                e.printStackTrace();
            }
        }

        try {
            jsonObject.put("data", jsonArray);
            jsonObject.put("device_id", android_id);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        Log.e("SamplesToServer", server_url);
        postReq(server_url, jsonObject, new NetworkCallbacks() {
            @Override
            public void workStatus(int STATUS, JSONObject payload) throws JSONException {
                super.workStatus(STATUS, payload);
            }

            @Override
            public void onError(int STATUS) {
                super.onError(STATUS);
                Log.e("SamplesToServer: Error", String.valueOf(STATUS));
            }
        });
    }

    public void sendSamplesToServer(float[] samples, String payload) {
        String server_url = "http://192.168.0.12:8081/v1/save/";
        JSONObject jsonObject = new JSONObject();
        JSONArray jsonArray = new JSONArray();
        for (int i=0; i<samples.length; i++) {
            try {
                jsonArray.put(samples[i]);
            } catch (JSONException e) {
                e.printStackTrace();
            }
        }

        try {
            jsonObject.put("data", jsonArray);
            jsonObject.put("payload", payload);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        Log.e("SamplesToServer", server_url);
        postReq(server_url, jsonObject, new NetworkCallbacks() {
            @Override
            public void workStatus(int STATUS, JSONObject payload) throws JSONException {
                super.workStatus(STATUS, payload);
            }

            @Override
            public void onError(int STATUS) {
                super.onError(STATUS);
                Log.e("SamplesToServer: Error", String.valueOf(STATUS));
            }
        });
    }
}
