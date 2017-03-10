package com.android.kaffka.arduinoledpainel;

import com.orm.SugarApp;
import com.orm.SugarContext;

/**
 * Created by kaffka on 10/03/2017.
 */

public class App extends SugarApp {
    @Override
    public void onCreate() {
        super.onCreate();
        SugarContext.init(this);
    }

    @Override
    public void onTerminate() {
        SugarContext.terminate();
        super.onTerminate();
    }
}
