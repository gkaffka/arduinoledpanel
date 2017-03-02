package com.android.kaffka.arduinoledpainel.models;

/**
 * Created by kaffka on 02/03/2017.
 */

public class Design {
    private Cell[][] cells;
    private String title;

    public Design(Cell[][] cells, String title) {
        this.cells = cells;
        this.title = title;
    }

    public Cell[][] getCells() {
        return cells;
    }

    public void setCells(Cell[][] cells) {
        this.cells = cells;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }
}
