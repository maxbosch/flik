/****************************************************************************
Copyright (c) 2015 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import android.app.Application;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.util.JsonReader;
import android.util.Log;

import com.aeskreis.flik.android.R;
import com.crashlytics.android.Crashlytics;
import com.crashlytics.android.answers.Answers;
import com.crashlytics.android.answers.CustomEvent;
import com.sdkbox.plugin.SDKBox;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.json.JSONException;
import org.json.JSONObject;
import org.json.JSONStringer;
import org.json.JSONTokener;

import java.util.Iterator;
import java.util.Locale;
import java.util.UUID;

import io.fabric.sdk.android.Fabric;

public class AppActivity extends Cocos2dxActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Load crashlytics
        Fabric fabric = new Fabric.Builder(this).appInstallIdentifier(getPackageName()).debuggable(true)
                .kits(new Crashlytics(), new Answers())
                .build();

        Fabric.with(fabric);

        Log.d("Activity", "Fabric loaded");
    }

    static void openURL(String url)
    {
        Intent urlIntent = new Intent(Intent.ACTION_VIEW);
        urlIntent.setData(Uri.parse(url));
        getContext().startActivity(urlIntent);
    }

    static void presentMailIntent(String toAddress, String subject, String body)
    {
        Intent intent = new Intent(Intent.ACTION_SENDTO, Uri.fromParts("mailto", toAddress, null));
        intent.putExtra(Intent.EXTRA_SUBJECT, subject);
        intent.putExtra(Intent.EXTRA_TEXT, body);
        getContext().startActivity(Intent.createChooser(intent, getContext().getString(R.string.email_us)));
    }

    static void logEvent(String eventName, String attributesJson)
    {
        CustomEvent event = new CustomEvent(eventName);

        // OS Specific properties
        event.putCustomAttribute("os", "android");
        event.putCustomAttribute("os_version", String.valueOf(Build.VERSION.SDK_INT));

        JSONTokener reader = new JSONTokener(attributesJson);
        try {
            JSONObject attributesObject = new JSONObject(reader);
            Iterator<String> keys = attributesObject.keys();
            while (keys.hasNext()) {
                String key = keys.next();
                double number = attributesObject.optDouble(key, Double.NEGATIVE_INFINITY);
                if (number != Double.NEGATIVE_INFINITY) {
                    event.putCustomAttribute(key, number);
                } else {
                    String string = attributesObject.optString(key);
                    if (string != null) {
                        event.putCustomAttribute(key, string);
                    }
                }
            }

            Answers.getInstance().logCustom(event);

            Log.d(AppActivity.getAppPackageName(), String.format("Analytics Event: %s, attributes: %s", eventName, attributesJson));
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    static String getAppPackageName()
    {
        return getContext().getPackageName();
    }

    static String getLanguage() {
        return Locale.getDefault().getLanguage();
    }

    static String newUUID() {
        return UUID.randomUUID().toString();
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if(!SDKBox.onActivityResult(requestCode, resultCode, data)) {
            super.onActivityResult(requestCode, resultCode, data);
        }
    }
    @Override
    protected void onStart() {
        super.onStart();
        SDKBox.onStart();
    }
    @Override
    protected void onStop() {
        super.onStop();
        SDKBox.onStop();
    }
    @Override
    protected void onResume() {
        super.onResume();
        SDKBox.onResume();
    }
    @Override
    protected void onPause() {
        super.onPause();
        SDKBox.onPause();
    }
    @Override
    public void onBackPressed() {
        if(!SDKBox.onBackPressed()) {
            super.onBackPressed();
        }
    }

}
