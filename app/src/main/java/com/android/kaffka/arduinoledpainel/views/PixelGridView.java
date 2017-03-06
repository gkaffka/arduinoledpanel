package com.android.kaffka.arduinoledpainel.views;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.View;

import com.android.kaffka.arduinoledpainel.interfaces.PixelDrawnListener;
import com.android.kaffka.arduinoledpainel.models.Cell;
import com.android.kaffka.arduinoledpainel.interfaces.ColorSamplerListener;
import com.android.kaffka.arduinoledpainel.interfaces.EraserListener;

/**
 * Created by gabrielkaffka on 17/02/17.
 */

public class PixelGridView extends View {
    private int numColumns, numRows;
    private int cellWidth, cellHeight;
    private Paint blackPaint = new Paint();
    private Paint gridPaint = new Paint();
    private Cell[][] cellChecked;
    private int currentColor;
    private ColorSamplerListener colorSamplerListener;
    private EraserListener eraserListener;
    private PixelDrawnListener pixelDrawnListener;

    public PixelGridView(Context context) {
        this(context, null);
        init();
    }

    public PixelGridView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    public void setNumColumns(int numColumns) {
        this.numColumns = numColumns;
        calculateDimensions();
    }

    public int getNumColumns() {
        return numColumns;
    }

    public void setNumRows(int numRows) {
        this.numRows = numRows;
        calculateDimensions();
    }

    public void setOnColorSamplerListener(ColorSamplerListener colorSamplerListener) {
        this.colorSamplerListener = colorSamplerListener;
    }

    public void setOnEraserSelectedListener(EraserListener eraserListener) {
        this.eraserListener = eraserListener;
    }

    public void setOnPixelDrawnListener(PixelDrawnListener pixelDrawnListener) {
        this.pixelDrawnListener = pixelDrawnListener;
    }

    public int getNumRows() {
        return numRows;
    }

    public void changeColor(int color) {
        currentColor = color;
        blackPaint.setColor(color);
    }

    @Override
    protected void onSizeChanged(int w, int h, int oldw, int oldh) {
        super.onSizeChanged(w, h, oldw, oldh);
        calculateDimensions();
    }

    private void calculateDimensions() {
        if (numColumns < 1 || numRows < 1) {
            return;
        }

        cellWidth = getWidth() / numColumns;
        cellHeight = getWidth() / numRows;

        cellChecked = new Cell[numColumns][numRows];

        for (int i = 0; i < numRows; i++)
            for (int j = 0; j < numColumns; j++)
                cellChecked[i][j] = new Cell(null, false);
        this.getLayoutParams().height = getResources().getDisplayMetrics().widthPixels;
        invalidate();
    }

    @Override
    protected void onDraw(Canvas canvas) {
        canvas.drawColor(Color.BLACK);

        if (numColumns == 0 || numRows == 0 || cellChecked == null) {
            return;
        }

        int width = getWidth();
        int height = getWidth();

        for (int i = 0; i < numColumns; i++) {
            for (int j = 0; j < numRows; j++) {

                if (cellChecked[i][j].isChecked()) {
                    if (cellChecked[i][j].getColor() != null)
                        blackPaint.setColor(cellChecked[i][j].getColor());
                    canvas.drawRect(i * cellWidth, j * cellHeight,
                            (i + 1) * cellWidth, (j + 1) * cellHeight,
                            blackPaint);
                }
            }
        }

        for (int i = 1; i < numColumns; i++) {
            canvas.drawLine(i * cellWidth, 0, i * cellWidth, height, gridPaint);
        }

        for (int i = 0; i <= numRows; i++) {
            canvas.drawLine(0, i * cellHeight, width, i * cellHeight, gridPaint);
        }
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        if (event.getAction() == MotionEvent.ACTION_DOWN) {
            int column = (int) (event.getX() / cellWidth);
            int row = (int) (event.getY() / cellHeight);

            if (row < cellChecked[0].length && column < cellChecked.length) {
                if (colorSamplerListener.isColorSamplerEnabled()) {
                    colorSamplerListener.onCellSelected(cellChecked[column][row]);
                    return true;
                }
                if (eraserListener.isEraserEnabled()) {
                    cellChecked[column][row].setChecked(false);
                    cellChecked[column][row].setColor(Color.rgb(0, 0, 0));
                    pixelDrawnListener.onPixelDrawListener(cellChecked[column][row], column, row);
                    invalidate();
                    return true;
                }
                cellChecked[column][row].setChecked(true);
                cellChecked[column][row].setColor(currentColor);
                pixelDrawnListener.onPixelDrawListener(cellChecked[column][row], column, row);
                invalidate();
            }
        } else if (event.getAction() == MotionEvent.ACTION_MOVE) {
            int column = (int) (event.getX() / cellWidth);
            int row = (int) (event.getY() / cellHeight);

            if (row < cellChecked[0].length && column < cellChecked.length
                    && row >= 0 && column >= 0) {
                if (colorSamplerListener.isColorSamplerEnabled()) {
                    colorSamplerListener.onCellSelected(cellChecked[column][row]);
                    return true;
                }
                if (eraserListener.isEraserEnabled()) {
                    cellChecked[column][row].setChecked(false);
                    cellChecked[column][row].setColor(Color.rgb(0, 0, 0));
                    pixelDrawnListener.onPixelDrawListener(cellChecked[column][row], column, row);
                    invalidate();
                    return true;
                }
                cellChecked[column][row].setChecked(true);
                cellChecked[column][row].setColor(currentColor);
                pixelDrawnListener.onPixelDrawListener(cellChecked[column][row], column, row);
                invalidate();
            }
        }

        return true;
    }

    private void init() {
        blackPaint.setStyle(Paint.Style.FILL_AND_STROKE);
        gridPaint.setStyle(Paint.Style.FILL_AND_STROKE);
        gridPaint.setColor(Color.rgb(80, 80, 80));

    }

    public Cell[][] getCells() {
        return cellChecked;
    }

    public void clearPixelScreen() {
        for (Cell[] cells : getCells())
            for (Cell c : cells)
                c.setChecked(false);

        invalidate();
    }

    public void fillPixelScreen(int color) {
        for (Cell[] cells : getCells())
            for (Cell c : cells) {
                c.setChecked(true);
                c.setColor(color);
            }
        invalidate();
    }

    public int getCurrentColor() {
        if (currentColor == 0) return Color.rgb(0, 0, 0);
        return currentColor;
    }

}