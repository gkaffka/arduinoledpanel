package com.android.kaffka.arduinoledpainel.models;

import com.orm.SugarRecord;

import java.util.List;

/**
 * Created by kaffka on 02/03/2017.
 */

public class Design extends SugarRecord {
    String title;

    public Design() {
    }

    public Design(String title) {
        this.title = title;
    }

    public List<Cell> getCells() {
        return Cell.find(Cell.class, "design = ?", String.valueOf(getId()));
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }
}
