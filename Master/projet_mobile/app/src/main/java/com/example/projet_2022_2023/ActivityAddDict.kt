package com.example.projet_2022_2023

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Toast
import androidx.lifecycle.ViewModelProvider
import com.example.projet_2022_2023.databinding.ActivityAddDictBinding

class ActivityAddDict : AppCompatActivity() {

    lateinit var model : ViewModel
    val binding by lazy { ActivityAddDictBinding.inflate(layoutInflater)}

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(binding.root)

        var nom = binding.nomDict
        var url = binding.urlDict
        var add = binding.addDict
        model = ViewModelProvider(this).get(ViewModel::class.java)

        add.setOnClickListener{
            if(!nom.text.toString().equals("") && !url.text.toString().equals("")) {
                model.insertDico(Dictionnaires(nom.text.toString(), url.text.toString()))
                finish()
            }
            else{
                Toast.makeText(this, "Tout les champs doivent être remplis.", Toast.LENGTH_SHORT).show()
            }
        }


    }
}