package com.trillbit.myapplication.network;
import org.json.JSONException;
import org.json.JSONObject;

public abstract class NetworkCallbacks {
    public void workStatus(int STATUS, JSONObject payload) throws JSONException {}

    public void onError(int STATUS) {}

}
