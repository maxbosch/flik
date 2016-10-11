package org.cocos2dx.cpp;

import android.app.Application;
import android.support.multidex.MultiDex;

/**
 * Created by adam on 10/7/16.
 */

public class MultiDexApplicationImpl extends Application {

    @Override
    public void onCreate() {
        MultiDex.install(this);

        super.onCreate();
    }
}
