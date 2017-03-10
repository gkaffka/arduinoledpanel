package com.android.kaffka.arduinoledpainel.viewmodels;

import android.app.Activity;
import android.content.Intent;
import android.databinding.BaseObservable;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

import com.android.kaffka.arduinoledpainel.models.Design;

/**
 * Created by kaffka on 10/03/2017.
 */

public class DesignViewModel extends BaseObservable {

    private Design design;

    public DesignViewModel(Design design) {
        this.design = design;
    }

    public String getTitle() {
        return design.getTitle();
    }

    public View.OnClickListener getClick() {
        return new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent result = new Intent();
                result.putExtra("design", design.getId());
                ((AppCompatActivity) v.getContext()).setResult(Activity.RESULT_OK, result);
                ((AppCompatActivity) v.getContext()).finish();
            }
        };
    }

}
