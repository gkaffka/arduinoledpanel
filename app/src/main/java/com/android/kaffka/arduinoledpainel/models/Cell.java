package com.android.kaffka.arduinoledpainel.models;

/**
 * Created by kaffka on 17/02/2017.
 */

public class Cell {
    private Integer color;
    private boolean isChecked;

    public Cell(Integer color, boolean isChecked) {
        this.color = color;
        this.isChecked = isChecked;
    }

    public void setColor(int color) {
        this.color = color;
    }

    public void setChecked(boolean checked) {
        isChecked = checked;
    }

    public Integer getColor() {
        return color;
    }

    public boolean isChecked() {
        return isChecked;
    }
}
