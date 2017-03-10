package com.android.kaffka.arduinoledpainel.activities;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;

import com.android.kaffka.arduinoledpainel.R;
import com.android.kaffka.arduinoledpainel.adapter.DesignsAdapter;
import com.android.kaffka.arduinoledpainel.models.Design;

import java.util.List;

/**
 * Created by kaffka on 02/03/2017.
 */

public class DesignsActivity extends AppCompatActivity {

    private List<Design> designList;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_designs);
        initDesignList();
        initRecyclerView();
    }

    private void initRecyclerView() {
        RecyclerView recyclerView = (RecyclerView) findViewById(R.id.designsList);
        recyclerView.setLayoutManager(new LinearLayoutManager(this));
        recyclerView.setAdapter(new DesignsAdapter(designList));
    }

    private void initDesignList() {
        designList = Design.listAll(Design.class);
    }
}
