package com.android.kaffka.arduinoledpainel.views;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.DialogFragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.LinearLayout;

import com.android.kaffka.arduinoledpainel.R;
import com.android.kaffka.arduinoledpainel.interfaces.SaveDesignDialogListener;

/**
 * Created by kaffka on 10/03/2017.
 */

public class SaveDesignDialog extends DialogFragment {

    private ImageView done;
    private EditText title;
    private SaveDesignDialogListener saveDesignDialogListener;

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setStyle(DialogFragment.STYLE_NO_FRAME, android.R.style.Theme_DeviceDefault_Light);
    }

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View v = inflater.inflate(R.layout.save_design_dialog, container, false);
        initViews(v);
        return v;
    }

    public void setOnSaveDialogListener(SaveDesignDialogListener saveDesignDialogListener) {
        this.saveDesignDialogListener = saveDesignDialogListener;
    }

    private void initViews(View v) {
        done = (ImageView) v.findViewById(R.id.dialog_done);
        title = (EditText) v.findViewById(R.id.dialog_design_title);

        done.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (title.length() > 0) {
                    saveDesignDialogListener.onTitleSelected(title.getText().toString());
                    dismiss();
                }
            }
        });
    }

    @Override
    public void onStart() {
        super.onStart();
        getDialog().getWindow().setLayout(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT);
    }
}
