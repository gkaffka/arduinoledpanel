package com.android.kaffka.arduinoledpainel.interfaces;

import com.android.kaffka.arduinoledpainel.models.Cell;

/**
 * Created by kaffka on 02/03/2017.
 */

public interface ColorSamplerListener {
    void onCellSelected(Cell cell);
    boolean isColorSamplerEnabled();

}
