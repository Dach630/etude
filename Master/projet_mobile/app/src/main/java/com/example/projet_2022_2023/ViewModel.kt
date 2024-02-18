package com.example.projet_2022_2023

import android.app.Application
import androidx.lifecycle.AndroidViewModel
import androidx.lifecycle.MutableLiveData

class ViewModel (application:Application) : AndroidViewModel(application){
    val dao = (application as DBApplication).database.myDao()
    val insertInfo = MutableLiveData(-1)

    fun insertMot(m : Mots){
        Thread{
            val l = dao.insererMot(m)
            insertInfo.postValue(if (l[0] == -1L) 0 else 1)
        }.start()
    }

    fun chargerMots() = dao.chargerMots()

    fun insertDico(d : Dictionnaires){
        Thread{
            val l = dao.insererDico(d)
            insertInfo.postValue(if (l[0] == -1L) 0 else 1)
        }.start()
    }

    fun chargerDico() = dao.chargerDico()
}
