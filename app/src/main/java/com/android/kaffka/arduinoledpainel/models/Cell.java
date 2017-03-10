package com.android.kaffka.arduinoledpainel.models;

import com.orm.SugarRecord;

/**
 * Created by kaffka on 17/02/2017.
 */

public class Cell extends SugarRecord {
     Integer color;
     boolean isChecked;
     int x, y;
     Design design;

    public Cell() {
    }

    public Cell(Integer color, boolean isChecked, int x, int y) {
        this.color = color;
        this.isChecked = isChecked;
        this.x = x;
        this.y = y;
    }

    public Cell(Integer color, boolean isChecked, int x, int y, Design design) {
        this.color = color;
        this.isChecked = isChecked;
        this.x = x;
        this.y = y;
        this.design = design;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public void setX(int x) {
        this.x = x;
    }

    public void setY(int y) {
        this.y = y;
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
