package com.example.projet_2022_2023

import androidx.lifecycle.LiveData
import androidx.room.Dao
import androidx.room.Insert
import androidx.room.OnConflictStrategy
import androidx.room.Query

@Dao
interface MyDao {

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    fun insererMot(vararg m:Mots):List<Long>

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    fun insererDico(vararg d:Dictionnaires):List<Long>

    @Query("SELECT * FROM Mots")
    fun chargerMots(): LiveData<List<Mots>>

    @Query("SELECT * FROM Dictionnaires")
    fun chargerDico(): LiveData<List<Dictionnaires>>


}