package com.example.projet_2022_2023

import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity
data class Mots(val mot:String, val langueD:String, val langueA:String, @PrimaryKey val url:String)