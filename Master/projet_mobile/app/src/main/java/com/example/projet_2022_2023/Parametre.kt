package com.example.projet_2022_2023

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.Toast
import com.example.projet_2022_2023.databinding.ActivityParametreBinding

class Parametre : AppCompatActivity() {

    val binding by lazy { ActivityParametreBinding.inflate(layoutInflater)}

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(binding.root)
    }

    fun save(view: View){
        if(binding.nbMot.text.toString() != ""
            || binding.nbJeu.text.toString() != ""){
            val data = Intent()
            data.putExtra("nbMot", binding.nbMot.text.toString().toInt())
            data.putExtra("nbJeu", binding.nbJeu.text.toString().toInt())
            //todo mettre d'autre donnee comme jour de la semaine,
            finish()
        }else{
            Toast.makeText(this, "il faut remplir tous les champs", Toast.LENGTH_SHORT).show()
        }
    }

    fun back (view: View){
        finish()
    }


}