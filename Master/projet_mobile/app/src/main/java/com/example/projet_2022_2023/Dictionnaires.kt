package com.example.projet_2022_2023

import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity
data class Dictionnaires(@PrimaryKey val nom:String, val url:String)