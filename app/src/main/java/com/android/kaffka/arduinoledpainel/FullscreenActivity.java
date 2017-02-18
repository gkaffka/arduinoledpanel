package com.android.kaffka.arduinoledpainel;

import android.graphics.Color;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.SeekBar;
import android.widget.TextView;

import com.android.kaffka.arduinoledpainel.views.PixelGridView;

/**
 * An example full-screen activity that shows and hides the system UI (i.e.
 * status bar and navigation/system bar) with user interaction.
 */
public class FullscreenActivity extends AppCompatActivity implements SeekBar.OnSeekBarChangeListener {
    private View v;
    private SeekBar red, blue, green;
    private TextView textRed, textGreen, textBlue;
    private PixelGridView pixelGrid;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_fullscreen);
        initPixelGrid();
        initText();
        initSeekBars();
        initColorShower();

    }

    private void initPixelGrid() {
        pixelGrid = (PixelGridView) findViewById(R.id.grid);
        pixelGrid.setNumColumns(7);
        pixelGrid.setNumRows(7);
    }

    private void initSeekBars() {
        red = (SeekBar) findViewById(R.id.seekRed);
        green = (SeekBar) findViewById(R.id.seekGreen);
        blue = (SeekBar) findViewById(R.id.seekBlue);
        red.setOnSeekBarChangeListener(this);
        green.setOnSeekBarChangeListener(this);
        blue.setOnSeekBarChangeListener(this);
    }

    private void initColorShower() {
        v = findViewById(R.id.color_show);
    }

    private void initText(){
        textRed = (TextView) findViewById(R.id.textRed);
        textBlue = (TextView) findViewById(R.id.textBlue);
        textGreen = (TextView) findViewById(R.id.textGreen);
    }

    @Override
    public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
        v.setBackgroundColor(Color.rgb(red.getProgress(), green.getProgress(), blue.getProgress()));
        pixelGrid.changeColor(Color.rgb(red.getProgress(), green.getProgress(), blue.getProgress()));
        textRed.setText("Red: "+red.getProgress());
        textGreen.setText("Green: "+green.getProgress());
        textBlue.setText("Blue: "+blue.getProgress());
    }

    @Override
    public void onStartTrackingTouch(SeekBar seekBar) {

    }

    @Override
    public void onStopTrackingTouch(SeekBar seekBar) {

    }
}
