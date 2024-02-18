package com.example.projet_2022_2023

import android.content.Context
import androidx.room.Database
import androidx.room.Room
import androidx.room.RoomDatabase

@Database(entities = [Mots::class , Dictionnaires::class], version = 6)
abstract class MyDatabase : RoomDatabase() {

    abstract fun myDao(): MyDao

    companion object {
        @Volatile
        private var instance: MyDatabase? = null

        fun getDatabase(context: Context): MyDatabase {
            if (instance != null)
                return instance!!
            val db = Room.databaseBuilder(
                context.applicationContext,
                MyDatabase::class.java, "database"
            )
                .fallbackToDestructiveMigration()
                .build()
            instance = db
            return instance!!
        }
    }

}