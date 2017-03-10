package com.android.kaffka.arduinoledpainel.adapter;

import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.android.kaffka.arduinoledpainel.R;
import com.android.kaffka.arduinoledpainel.databinding.DesignsItemBinding;
import com.android.kaffka.arduinoledpainel.models.Design;
import com.android.kaffka.arduinoledpainel.viewmodels.DesignViewModel;

import java.util.List;

/**
 * Created by kaffka on 09/03/2017.
 */

public class DesignsAdapter extends RecyclerView.Adapter<DesignsAdapter.DesignViewHolder> {

    private final List<Design> designList;

    public DesignsAdapter(List<Design> designList) {
        this.designList = designList;
    }

    @Override
    public DesignViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        return new DesignViewHolder(LayoutInflater.from(parent.getContext()).inflate(R.layout.designs_item, parent, false));

    }

    @Override
    public void onBindViewHolder(DesignViewHolder holder, int position) {
        holder.designsItemBinding.setViewmodel(new DesignViewModel(designList.get(position)));
    }

    @Override
    public int getItemCount() {
        return designList.size();
    }

    public static class DesignViewHolder extends RecyclerView.ViewHolder {

        public final DesignsItemBinding designsItemBinding;

        public DesignViewHolder(View v) {
            super(v);
            designsItemBinding = DesignsItemBinding.bind(v);
        }
    }
}
