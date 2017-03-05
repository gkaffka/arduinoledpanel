package com.android.kaffka.arduinoledpainel.interfaces;

import com.android.kaffka.arduinoledpainel.models.Cell;

/**
 * Created by kaffka on 05/03/2017.
 */

public interface PixelDrawnListener {
    void onPixelDrawListener(Cell cell, int x, int y);
}
