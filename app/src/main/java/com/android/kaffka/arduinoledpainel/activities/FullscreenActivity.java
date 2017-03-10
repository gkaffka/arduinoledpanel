package com.android.kaffka.arduinoledpainel.activities;

import android.app.ProgressDialog;
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

import com.android.kaffka.arduinoledpainel.R;
import com.android.kaffka.arduinoledpainel.interfaces.ColorSamplerListener;
import com.android.kaffka.arduinoledpainel.interfaces.EraserListener;
import com.android.kaffka.arduinoledpainel.interfaces.PixelDrawnListener;
import com.android.kaffka.arduinoledpainel.io.Bluetooth;
import com.android.kaffka.arduinoledpainel.models.Cell;
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
public class FullscreenActivity extends AppCompatActivity implements ColorPickerDialogListener, ColorSamplerListener, EraserListener, PixelDrawnListener {
    public static final String TAG = "PAINEL_KAFFKA";
    private View colorShowerView;
    private SeekBar delay;
    private TextView textSavedFrames, textDelay, textBluetooth;
    private CheckBox clearScreenCbox;
    private PixelGridView pixelGrid;
    private ArrayList<String> code;
    private int savedFrames;
    private ImageView imgColorSampler, imgEraser;
    private boolean isColorSamplerEnabled, isEraserEnabled;
    private Bluetooth bt;
    private ProgressDialog bluetoothDialog;

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
        pixelGrid.setOnPixelDrawnListener(this);
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
        if (BluetoothAdapter.getDefaultAdapter() == null) return;
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
        textBluetooth = (TextView) findViewById(R.id.text_bluetooth_status);
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

    public void savePersistent(View v) {

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

    private void generateBluetoothCode(boolean clearCode) {
        if (code == null || clearCode)
            code = new ArrayList<>();
        Cell[][] cells_array = pixelGrid.getCells();
        for (int i = 0; i < cells_array.length; i++)
            for (int j = 0; j < cells_array[i].length; j++) {
                if (cells_array[i][j].isChecked())
                    code.add(getArduinoFastLedCodeBluetooth(cells_array[i][j].getColor(), i, j));
            }
    }

    private String getArduinoFastLedCodeBluetooth(int color, int x, int y) {
        int red = Color.red(color);
        int green = Color.green(color);
        int blue = Color.blue(color);
        return String.format("%03d,%03d,%03d,%03d", getRealLedCoordinate(x, y), red, green, blue);
    }

    private String getArduinoFastLedCode(int color, int x, int y) {
        int red = Color.red(color);
        int green = Color.green(color);
        int blue = Color.blue(color);
        return String.format("leds[%d] = CRGB(%d,%d,%d);", getRealLedCoordinate(x, y), red, green, blue);
    }

    public void fillScreen(View v) {
        unselectControls();
        pixelGrid.fillPixelScreen(pixelGrid.getCurrentColor());
        if (bt != null) {
            bt.sendMessage("$" + getArduinoFastLedCodeBluetooth(pixelGrid.getCurrentColor(), 0, 0));
        }
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
        bt.sendMessage("@");
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
                if (bt.getState() == 3) {
                    generateBluetoothCode(true);
                    bluetoothDialog = new ProgressDialog(this);
                    bluetoothDialog.setMax(100);
                    bluetoothDialog.setMessage("Enviando a tela... 0%");
                    bluetoothDialog.show();
                    bt.sendMessage(code);
                } else connectService();
                return true;
            case R.id.action_run_demo:
                if (bt.getState() == 3) {
                    bt.sendMessage("d");
                } else connectService();
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
                    switch (msg.arg1) {
                        case Bluetooth.STATE_CONNECTED:
                            textBluetooth.setText("Conectado");
                            break;
                        case Bluetooth.STATE_CONNECTING:
                            textBluetooth.setText("Conectando...");
                            break;
                        case Bluetooth.STATE_LISTEN:
                            textBluetooth.setText("Aguardando Conexão");
                            break;
                        case Bluetooth.STATE_NONE:
                            textBluetooth.setText("Indisponível");
                            break;
                    }

                    break;
                case Bluetooth.MESSAGE_WRITE:
                    Log.d(TAG, "MESSAGE_WRITE ");
                    textBluetooth.setText("Conectado");
                    break;
                case Bluetooth.MESSAGE_SENT:
                    Log.d(TAG, "MESSAGE_SENT");
                    textBluetooth.setText("Conectado");
                    break;
                case Bluetooth.MESSAGE_SENT_ERROR:
                    Log.d(TAG, "MESSAGE_SENT_ERROR ");
                    textBluetooth.setText("Erro no envio");
                    break;
                case Bluetooth.MESSAGE_READ:
                    Log.d(TAG, "MESSAGE_READ ");
                    textBluetooth.setText("Recebendo...");
                    break;
                case Bluetooth.MESSAGE_DEVICE_NAME:
                    Log.d(TAG, "MESSAGE_DEVICE_NAME " + msg);
                    break;
                case Bluetooth.MESSAGE_TOAST:
                    Log.d(TAG, "MESSAGE_TOAST " + msg);
                    textBluetooth.setText("Conexão perdida...");
                    break;
                case Bluetooth.MESSAGE_SEND_PROGRESS:
                    Log.d(TAG, "MESSAGE_SEND_PROGRESS " + msg);
                    if (bluetoothDialog != null) {
                        bluetoothDialog.setMessage(String.format("Enviando a tela... %d%%", msg.arg1));
                        if (msg.arg1 >= 100) bluetoothDialog.dismiss();
                    }
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
            Log.e(TAG, "Unable to start bt ", e);
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

    private int getRealLedCoordinate(int x, int y) {
        y = 15 - y;
        x = 15 - x;
        if (y == 0)
            return x;
        else if (y == 1)
            return 31 - x;
        else if (y == 2)
            return x + 32;
        else if (y == 3)
            return 63 - x;
        else if (y == 4)
            return x + 64;
        else if (y == 5)
            return 95 - x;
        else if (y == 6)
            return x + 96;
        else if (y == 7)
            return 127 - x;
        else if (y == 8)
            return x + 128;
        else if (y == 9)
            return 159 - x;
        else if (y == 10)
            return x + 160;
        else if (y == 11)
            return 191 - x;
        else if (y == 12)
            return x + 192;
        else if (y == 13)
            return 223 - x;
        else if (y == 14)
            return x + 224;
        else if (y == 15)
            return 255 - x;
        else
            return 0;
    }

    @Override
    public void onPixelDrawListener(Cell cell, int x, int y) {
        if (bt == null) return;
        String message = getArduinoFastLedCodeBluetooth(cell.getColor(), x, y);
        bt.sendMessage(message);
    }
}
