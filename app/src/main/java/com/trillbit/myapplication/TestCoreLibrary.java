package com.trillbit.myapplication;

import android.content.Context;
import android.util.Log;

import com.trillbit.myapplication.core.CWrapper;
import com.trillbit.myapplication.network.HTTPS;
import com.trillbit.myapplication.player.Player;

public class TestCoreLibrary {

    CWrapper cWrapper;
    HTTPS https;
    public TestCoreLibrary(Context context) {
        cWrapper = new CWrapper();
        https = new HTTPS(context);
    }

    public float[] generateSymbols() {
        return cWrapper.GenerateSamples("abcdef");
    }

    public short[] convertToShort(float[] samples, int extraZerosBegin, int extraZerosEnd) {
        int sample_size = samples.length;
        short[] samples_short = new short[extraZerosBegin + sample_size + extraZerosEnd];
        int i;
        Log.e("Tag", "total size :" + samples_short.length);
        for (i=0; i<extraZerosBegin; i++) {
            samples_short[i] = 0;
        }
        Log.e("Tag", "I at :" + i);
        for (i=extraZerosBegin; i<extraZerosBegin + sample_size; i++) {
            int value = (int) (samples[i-extraZerosBegin] * 32768);
            samples_short[i] = (short) value;
        }
        Log.e("Tag", "I at :" + i);
        for (i=extraZerosBegin + sample_size; i< extraZerosBegin + extraZerosEnd + sample_size; i++) {
            samples_short[i] = 0;
        }
        Log.e("Tag", "I at :" + i);
        return samples_short;
    }

    public void test() {
        float[] samples = generateSymbols();
        short[] samples_short = convertToShort(samples, 12288, 12288);

        for (int i=0; i<samples_short.length; i+=1024) {
            int start = i;
            int end = i+1024;
            short[] temp = new short[1024];
            int counter = 0;
            for (int j=start; j<end; j++) {
                try {
                    temp[counter] = samples_short[j];
                } catch (Exception e) {
                    temp[counter] = 0;
                }
                counter += 1;
            }

            this.cWrapper.AddBuffer(temp);
            this.cWrapper.ProcessBuffer();
        }
    }

    public void testPlay(Context context) {
        Player player = new Player(context);
        player.play("abcdef");

    }


    public void collectFiles() {
        String[] payloads = { "NPHPuh", "edGTNr", "tSjQLz", "ZnrSrg", "fgAYGF", "nAJUNi", "ZYBoxl", "UxAvCd", "ZfCWea", "bZwVTN", "oiqIHI", "WqgJfM", "AemMaW", "vjKnft", "QFihKK", "FBsPfC", "sDYxfX", "oYqyfj", "EalaYu", "yGhkQk", "vvOhBK", "hqbgRs", "TRNWjZ", "PXcKIr", "XVrnMW", "BbPihp", "PbJYiz", "sTrxNM", "hwxpQC", "fjkqmQ", "HmfAmp", "FzNDkg", "burari", "WHEhJJ", "cEzDgQ", "LSIWRm", "gzlNdc", "qiRpVz", "pJIxbi", "KPxxtu", "OGBHSP", "WFdpxW", "TqyOwn", "FOGNaN", "HeMvpA", "eVToqF", "VffVzq", "QmmsDf", "GxWIbR", "leiihe", "QuhPah", "MbpBFh", "VZUSLW", "uVzHPK", "bRojxE", "KZZTkL", "RhsaYo", "GyfUEU", "dFPQcq", "HAIiKc", "gfJQyD", "oYncRc", "wjoZay", "lPJkUF", "DUODzY", "gXwiOC", "FgLVCh", "KUsISX", "QcWjiP", "SYXTaX", "eLyvQA", "oYWVQB", "viDLUf", "FozMhQ", "ooPMEO", "xmFKky", "YocIjE", "rmHaiS", "bUBkJb", "BDvCsv", "phZihe", "jsLzoi", "YJTyBg", "DVPrsj", "Zykpko", "twYnBh", "KuqRik", "VBvnwR", "hlqsvA", "xcgNKR", "HaKbcx", "WboJiS", "mYUXqX", "kmonLg", "jbyaBz", "bMDgmW", "bnXQpW", "mcuFko", "vwmRMH", "POXJIZ"};
        for (int i=0; i<payloads.length; i++) {
            String current_payload = payloads[i];
            float [] sampples = this.cWrapper.GenerateSamples(current_payload);
            https.sendSamplesToServer(sampples, current_payload);
        }
    }
}
