package com.example.projet_2022_2023

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import androidx.lifecycle.ViewModelProvider
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView.Adapter
import com.example.projet_2022_2023.databinding.ActivityBddictionnaireBinding

class BDDictionnaire : AppCompatActivity() {

    val binding by lazy { ActivityBddictionnaireBinding.inflate(layoutInflater)}
    lateinit var model : ViewModel
    lateinit var adapter : AdapterDict

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(binding.root)

        model = ViewModelProvider(this).get(ViewModel::class.java)
        val recycler = binding.recycler
        adapter = AdapterDict(model.chargerDico())
        recycler.layoutManager = LinearLayoutManager(this)
        recycler.adapter = adapter


    }

    fun add_dict(view : View){
        val iii = Intent(this, Parametre::class.java)
        startActivity(iii)
    }
}