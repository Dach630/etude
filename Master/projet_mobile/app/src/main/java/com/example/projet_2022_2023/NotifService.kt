package com.example.projet_2022_2023

import android.app.*
import android.content.Intent
import android.media.AudioAttributes
import android.media.MediaPlayer
import android.net.Uri
import android.os.Build
import android.os.IBinder
import android.util.Log
import android.widget.Toast
import androidx.core.app.NotificationCompat
import androidx.lifecycle.ViewModelProvider

class NotifService : Service() {

    val CHANNEL_ID = "la jeu"
    val notificationManager by lazy {getSystemService(NOTIFICATION_SERVICE)as NotificationManager }
    lateinit var  mediaPlayer: MediaPlayer

    override fun onBind(p0: Intent?): IBinder? {
        TODO("Not yet implemented")
    }

    override fun onCreate() {
        super.onCreate()
        mediaPlayer = MediaPlayer().apply {
            setVolume(1.0F, 1.0F)
            setAudioAttributes(
                AudioAttributes.Builder()
                    .setContentType(AudioAttributes.CONTENT_TYPE_MUSIC)
                    .setUsage(AudioAttributes.USAGE_ALARM).build()
            )
        }
        createNotificationChannel()
    }

    override fun onStartCommand(intent: Intent, flags: Int, startId: Int): Int {
        if( intent.action == "stop" ){
            mediaPlayer.stop()
            mediaPlayer.release()

            stopSelf()
            return START_NOT_STICKY
        }

        if( !intent.action.equals("start") ){
            Log.d("MyService", "l'action inconnue")
            return START_NOT_STICKY
        }
        //
        envNotif()
        //

        if( intent.data == null ) {
            return START_NOT_STICKY
        }

        mediaPlayer.setOnCompletionListener {
            mediaPlayer.release()
            Log.d("MyService", "onCompletionListener")
        }

        mediaPlayer.apply {
            setDataSource( this@NotifService, intent.data!! )
            setOnPreparedListener{
                it.start()
            }
            prepareAsync()
        }

        return START_NOT_STICKY
    }

    override fun onDestroy() {
        mediaPlayer.release()

        Log.d("NotifService", "OnDestroy")
        super.onDestroy()
    }

    private fun createNotificationChannel() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            val importance = NotificationManager.IMPORTANCE_DEFAULT
            val channel = NotificationChannel(CHANNEL_ID, "Le jeu de mot", importance)
            channel.description = "apprendre une langue"
            val notificationManager = getSystemService(NotificationManager::class.java)
            notificationManager.createNotificationChannel(channel)
        }
    }

    private fun envNotif(){
        val dao = (application as DBApplication).database.myDao()
        var listTmp = dao.chargerMots().value ?: return

        var listMots = listTmp.toMutableList()

        var n = if(listMots.size > 6){
            5
        }else{
            listMots.size
        }

        var v = 0
        for(i in 0 until n) {
            v = (0..listMots.size).random()
            val intent = Intent(Intent.ACTION_VIEW)
            intent.data = Uri.parse(listMots[v].url)

            val stackBuilder = TaskStackBuilder.create(this)
            stackBuilder.addParentStack(MainActivity::class.java)
            stackBuilder.addNextIntent(intent)

            val activityPendingIntent = PendingIntent.getActivity(
                this, i + 1, intent, PendingIntent.FLAG_IMMUTABLE
            )
            val serviceIntent = Intent(this, NotifService::class.java).apply{
                action="stop"
            }
            val delPInt = PendingIntent.getService(this, i + 1, serviceIntent, PendingIntent.FLAG_IMMUTABLE)

            val notification: Notification = NotificationCompat.Builder(this, CHANNEL_ID)
                .setContentTitle("Apprendre un mot")
                .setContentText(listMots[v].mot + " : " + listMots[v].langueD + " -> " + listMots[v].langueA )
                .setSmallIcon(R.drawable.small)
                .setContentIntent(activityPendingIntent)
                .setAutoCancel(true)
                .setDeleteIntent(delPInt)
                .build()

            notificationManager.notify(i + 1, notification)
            listMots.removeAt(v)
        }
    }

}