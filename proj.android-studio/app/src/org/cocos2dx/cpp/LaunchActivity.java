package org.cocos2dx.cpp;

import android.app.Activity;
import android.content.Intent;
import android.os.Handler;
import android.os.Looper;

/**
 * Created by adam on 8/10/16.
 */
public class LaunchActivity extends Activity {
    @Override
    protected void onResume() {
        super.onResume();

        new Handler(Looper.getMainLooper()).postDelayed(new Runnable() {
            @Override
            public void run() {
                completeLaunch();
            }
        }, 500);
    }

    private void completeLaunch() {
        Intent intent = new Intent(this, AppActivity.class);
        startActivity(intent);
        finish();
    }
}
