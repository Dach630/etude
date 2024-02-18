package com.example.projet_2022_2023

import android.content.Intent
import android.net.Uri
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.Toast
import androidx.lifecycle.ViewModelProvider
import com.example.projet_2022_2023.databinding.ActivityShareBinding

class ActivityShare : AppCompatActivity() {

    lateinit var model : ViewModel
    val binding by lazy { ActivityShareBinding.inflate(layoutInflater)}


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_share)

        val  tv = binding.urlMot
        tv.text = intent.getStringExtra("lien").toString()
        model = ViewModelProvider(this).get(ViewModel::class.java)

    }

    fun add (view: View){
        if(binding.mot.text.toString() == "" ||
            binding.langue1.text.toString() == "" ||
            binding.langue2.text.toString() == ""){
            Toast.makeText(this, "Tout les champs doivent être remplis.", Toast.LENGTH_SHORT).show()
        }else{
            model.insertMot(Mots(binding.mot.text.toString(), binding.langue1.text.toString(), binding.langue2.text.toString(), intent.getStringExtra("lien").toString()))
            finish();
        }
    }


}