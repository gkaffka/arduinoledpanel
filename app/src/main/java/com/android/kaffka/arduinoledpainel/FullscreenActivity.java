package com.android.kaffka.arduinoledpainel;

import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.support.annotation.ColorInt;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.text.TextUtils;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.CheckBox;
import android.widget.ImageView;
import android.widget.SeekBar;
import android.widget.TextView;

import com.android.kaffka.arduinoledpainel.views.PixelGridView;
import com.jrummyapps.android.colorpicker.ColorPickerDialog;
import com.jrummyapps.android.colorpicker.ColorPickerDialogListener;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;

/**
 * An example full-screen activity that shows and hides the system UI (i.e.
 * status bar and navigation/system bar) with user interaction.
 */
public class FullscreenActivity extends AppCompatActivity implements ColorPickerDialogListener {
    private View v;
    private SeekBar delay;
    private TextView textRed, textGreen, textBlue, textSavedFrames, textDelay;
    private CheckBox clearScreenCbox;
    private PixelGridView pixelGrid;
    private ArrayList<String> code;
    private ImageView colorPicker, colorSampler, fillScreen, clearScreen;
    private int savedFrames;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_fullscreen);
        initPixelGrid();
        initText();
        initSeekBars();
        initColorShower();
        initImageControls();
    }

    private void initPixelGrid() {
        pixelGrid = (PixelGridView) findViewById(R.id.grid);
        pixelGrid.setNumColumns(7);
        pixelGrid.setNumRows(7);
        pixelGrid.changeColor(Color.rgb(0,0,0));
    }

    private void initSeekBars() {
        delay = (SeekBar) findViewById(R.id.seekDelay);
    }

    private void initColorShower() {
        v = findViewById(R.id.color_show);
    }

    private void initText() {
        textSavedFrames = (TextView) findViewById(R.id.textFramesSaved);
        textDelay = (TextView) findViewById(R.id.textDelay);
        clearScreenCbox = (CheckBox) findViewById(R.id.checkboxClearScreen);
    }

    private void initImageControls(){
        colorPicker = (ImageView) findViewById(R.id.img_color_picker);
        colorSampler = (ImageView) findViewById(R.id.img_color_sampler);
        fillScreen = (ImageView) findViewById(R.id.img_fill);
        clearScreen = (ImageView) findViewById(R.id.img_clear);

        colorPicker.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ColorPickerDialog.newBuilder().setColor(pixelGrid.getCurrentColor()).show(FullscreenActivity.this);
            }
        });

       fillScreen.setOnClickListener(new View.OnClickListener() {
           @Override
           public void onClick(View v) {
               pixelGrid.fillPixelScreen(pixelGrid.getCurrentColor());
           }
       });

        clearScreen.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                pixelGrid.clearPixelScreen();
            }
        });
    }

    public void shareCode() {
        if (code == null || code.size() == 0) return;
        Intent sendIntent = new Intent();
        sendIntent.setAction(Intent.ACTION_SEND);
        String generated_code = TextUtils.join("\n", code);
        sendIntent.putExtra(Intent.EXTRA_TEXT, generated_code);
        sendIntent.setType("text/plain");
        startActivity(sendIntent);
    }

    public void exportCode(View v) {
        textSavedFrames.setText(String.format("Saved frames: %d", ++savedFrames));
        generateCode(false);
    }

    private void generateCode(boolean clearCode) {
        if (code == null || clearCode)
            code = new ArrayList<>();
        Cell[][] cells_array = pixelGrid.getCells();
        Collections.reverse(Arrays.asList(cells_array));
        for (int i = 0; i < cells_array.length; i++)
            for (int j = 0; j < cells_array[i].length; j++) {
                if (cells_array[i][j].isChecked())
                    code.add(getArduinoFastLedCode(cells_array[i][j].getColor(), i, j));
            }
        code.add("FastLED.show();");
        code.add(String.format("delay(%d);", delay.getProgress()));
        if (clearScreenCbox.isChecked())
            code.add(String.format("clearScreen();", delay.getProgress()));
        Collections.reverse(Arrays.asList(cells_array));
    }

    private String getArduinoFastLedCode(int color, int x, int y) {
        int red = Color.red(color);
        int green = Color.green(color);
        int blue = Color.blue(color);
        return String.format("leds[getRealLedCoordinate(%d,%d)] = CRGB(%d,%d,%d);", x, y, red, green, blue);
    }

    public void clearScreen(View v) {
        pixelGrid.clearPixelScreen();
    }

    public void clearCode(View v) {
        if (code != null) code.clear();
        textSavedFrames.setText(String.format("Saved frames: %d", 0));
        savedFrames = 0;
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.main_menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.action_share:
                shareCode();
                return true;
            default:
                finish();
                return true;
        }
    }

    @Override
    public void onColorSelected(int dialogId, @ColorInt int color) {
        pixelGrid.changeColor(color);
        v.setBackgroundColor(color);
    }

    @Override
    public void onDialogDismissed(int dialogId) {

    }
}
