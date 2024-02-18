package com.example.projet_2022_2023

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.lifecycle.LiveData
import androidx.recyclerview.widget.RecyclerView

class AdapterDict (dictlist : LiveData<List<Dictionnaires>>) : RecyclerView.Adapter<RecyclerView.ViewHolder>(){

    val dicts : MutableList<Dictionnaires> = dictlist.value as MutableList<Dictionnaires>

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): RecyclerView.ViewHolder {
        val view : View = LayoutInflater.from(parent.context).inflate(R.layout.model_dict, parent,false)
        return VH(view)
    }

    override fun onBindViewHolder(holder: RecyclerView.ViewHolder, position: Int) {
        holder.itemView.findViewById<TextView>(R.id.url_dict)
        holder.itemView.findViewById<TextView>(R.id.nom_dict)
    }

    override fun getItemCount(): Int {
        return dicts.size
    }


}
class VH(itemView : View) : RecyclerView.ViewHolder(itemView)
