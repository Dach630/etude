package com.example.projet_2022_2023

import android.app.Application

class DBApplication : Application(){

    val database by lazy{
        MyDatabase.getDatabase(this)
    }
}