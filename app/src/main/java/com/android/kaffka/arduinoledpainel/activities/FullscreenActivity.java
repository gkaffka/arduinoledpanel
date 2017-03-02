package com.android.kaffka.arduinoledpainel.activities;

import android.bluetooth.BluetoothAdapter;
import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.annotation.ColorInt;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.text.TextUtils;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.CheckBox;
import android.widget.ImageView;
import android.widget.SeekBar;
import android.widget.TextView;

import com.android.kaffka.arduinoledpainel.io.Bluetooth;
import com.android.kaffka.arduinoledpainel.models.Cell;
import com.android.kaffka.arduinoledpainel.R;
import com.android.kaffka.arduinoledpainel.interfaces.ColorSamplerListener;
import com.android.kaffka.arduinoledpainel.interfaces.EraserListener;
import com.android.kaffka.arduinoledpainel.models.Design;
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
public class FullscreenActivity extends AppCompatActivity implements ColorPickerDialogListener, ColorSamplerListener, EraserListener {
    public final String TAG = "PAINEL_KAFFKA";
    private View colorShowerView;
    private SeekBar delay;
    private TextView textSavedFrames, textDelay;
    private CheckBox clearScreenCbox;
    private PixelGridView pixelGrid;
    private ArrayList<String> code;
    private int savedFrames;
    private ImageView imgColorSampler, imgEraser;
    private boolean isColorSamplerEnabled, isEraserEnabled;
    private Bluetooth bt;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_fullscreen);
        initPixelGrid();
        initText();
        initSeekBars();
        initImageControls();
        initBluetooth();
    }

    private void initPixelGrid() {
        pixelGrid = (PixelGridView) findViewById(R.id.grid);
        pixelGrid.setNumColumns(16);
        pixelGrid.setNumRows(16);
        pixelGrid.setOnColorSamplerListener(this);
        pixelGrid.setOnEraserSelectedListener(this);
        pixelGrid.changeColor(Color.rgb(0, 0, 0));
    }

    private void initSeekBars() {
        delay = (SeekBar) findViewById(R.id.seekDelay);
        delay.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                textDelay.setText("Delay: " + progress);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
    }

    private void initBluetooth() {
        bt = new Bluetooth(this, mHandler);
        connectService();
    }

    private void initImageControls() {
        colorShowerView = findViewById(R.id.color_show);
        imgColorSampler = (ImageView) findViewById(R.id.img_color_sampler);
        imgEraser = (ImageView) findViewById(R.id.img_eraser);
    }

    private void initText() {
        textSavedFrames = (TextView) findViewById(R.id.textFramesSaved);
        textDelay = (TextView) findViewById(R.id.textDelay);
        clearScreenCbox = (CheckBox) findViewById(R.id.checkboxClearScreen);
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

    public void savePersistent(View v){

        Design design;
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

    public void fillScreen(View v) {
        unselectControls();
        pixelGrid.fillPixelScreen(pixelGrid.getCurrentColor());
    }

    public void openColorPicker(View v) {
        unselectControls();
        ColorPickerDialog.newBuilder().setColor(pixelGrid.getCurrentColor()).show(FullscreenActivity.this);
    }

    public void startColorSampler(View v) {
        isEraserEnabled = false;
        imgEraser.setSelected(false);
        if (!isColorSamplerEnabled) {
            isColorSamplerEnabled = true;
            v.setSelected(true);
        } else {
            isColorSamplerEnabled = false;
            v.setSelected(false);
        }
    }

    public void clearScreen(View v) {
        pixelGrid.clearPixelScreen();
        unselectControls();
    }

    public void clearCode(View v) {
        if (code != null) code.clear();
        textSavedFrames.setText(String.format("Saved frames: %d", 0));
        savedFrames = 0;
        unselectControls();
    }

    public void eraseCode(View v) {
        isColorSamplerEnabled = false;
        imgColorSampler.setSelected(false);

        if (!isEraserEnabled) {
            isEraserEnabled = true;
            v.setSelected(true);
        } else {
            isEraserEnabled = false;
            v.setSelected(false);
        }
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
            case R.id.action_send_bluetooth:
                bt.sendMessage("");
                return true;
            default:
                finish();
                return true;
        }
    }

    @Override
    public void onColorSelected(int dialogId, @ColorInt int color) {
        pixelGrid.changeColor(color);
        colorShowerView.setBackgroundColor(color);
    }

    @Override
    public void onDialogDismissed(int dialogId) {

    }

    @Override
    public void onCellSelected(Cell cell) {
        if (isColorSamplerEnabled) {
            isColorSamplerEnabled = false;
            if (cell.getColor() == null) return;
            pixelGrid.changeColor(cell.getColor());
            colorShowerView.setBackgroundColor(cell.getColor());
            imgColorSampler.setSelected(false);
        }
    }

    @Override
    public boolean isColorSamplerEnabled() {
        return isColorSamplerEnabled;
    }

    private final Handler mHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {

            switch (msg.what) {
                case Bluetooth.MESSAGE_STATE_CHANGE:
                    Log.d(TAG, "MESSAGE_STATE_CHANGE: " + msg.arg1);
                    break;
                case Bluetooth.MESSAGE_WRITE:
                    Log.d(TAG, "MESSAGE_WRITE ");
                    break;
                case Bluetooth.MESSAGE_READ:
                    Log.d(TAG, "MESSAGE_READ ");
                    break;
                case Bluetooth.MESSAGE_DEVICE_NAME:
                    Log.d(TAG, "MESSAGE_DEVICE_NAME " + msg);
                    break;
                case Bluetooth.MESSAGE_TOAST:
                    Log.d(TAG, "MESSAGE_TOAST " + msg);
                    break;
            }
        }
    };

    public void connectService() {
        try {
            BluetoothAdapter bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
            if (bluetoothAdapter.isEnabled()) {
                bt.start();
                bt.connectDevice("painel-do-kaffka");
                Log.d(TAG, "Btservice started - listening");
            } else {
                Log.w(TAG, "Btservice started - bluetooth is not enabled");
            }
        } catch (Exception e) {

        }
    }

    @Override
    public boolean isEraserEnabled() {
        return isEraserEnabled;
    }

    private void unselectControls() {
        imgColorSampler.setSelected(false);
        imgEraser.setSelected(false);
        isColorSamplerEnabled = false;
        isEraserEnabled = false;
    }
}
