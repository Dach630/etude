package com.example.projet_2022_2023


import android.app.Activity
import android.app.AlarmManager
import android.app.PendingIntent
import android.content.Intent
import android.net.Uri
import android.os.Bundle
import android.view.View
import android.widget.AdapterView
import android.widget.Spinner
import android.widget.TextView
import android.widget.Toast
import androidx.activity.result.ActivityResultLauncher
import androidx.activity.result.contract.ActivityResultContracts
import androidx.appcompat.app.AppCompatActivity
import com.example.projet_2022_2023.databinding.ActivityMainBinding
import java.util.*


class MainActivity : AppCompatActivity() {

    private val binding by lazy { ActivityMainBinding.inflate(layoutInflater)}

    var site = "https://www.larousse.fr"

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(binding.root)

        if( intent.action.equals( "android.intent.action.SEND" ) ){
            val txt = intent.extras?.getString( "android.intent.extra.TEXT" )
            if(txt != null){
                if (txt.toString() != "") {
                    val iii = Intent(this, ActivityShare::class.java)
                    iii.putExtra("lien", txt)
                    startActivity(iii)
                }
            }
        }
        /*
        spinner.onItemSelectedListener = object : AdapterView.OnItemSelectedListener {
            override fun onItemSelected(
                parent: AdapterView<*>,
                view: View?,
                pos: Int,
                id: Long
            ) {
                //todo selection du site
                site = (view as TextView).text.toString()
            }

            override fun onNothingSelected(parent: AdapterView<*>) {

            }
        }
        */
        setAlarm()
    }

    fun traduction (view: View){
        if(binding.ETLangueDepart.text.toString() == "" ||
            binding.ETLangueArrive.text.toString() == "" ||
            binding.ETTextMotATraduire.text.toString() == ""){
            Toast.makeText(this, "Tout les champs doivent être remplis.", Toast.LENGTH_SHORT).show()
        }else{
            val txt = url()
            val intent = Intent(Intent.ACTION_VIEW)
            intent.data = Uri.parse(txt)
            startActivity(intent)
        }
    }

    val launcher : ActivityResultLauncher<Intent> = registerForActivityResult(
        ActivityResultContracts.StartActivityForResult()){
        if( it.resultCode == Activity.RESULT_OK ){
            val intent = it.data
            if (intent != null) {
                //todo modififier le service
            }
        }else{
            Toast.makeText(this, "pas de changement", Toast.LENGTH_LONG).show()
        }
    }

    fun parametre (view: View){
        val iii = Intent(this, Parametre::class.java)
        launcher.launch(iii)
    }

    private fun url () : String{
        val suite ="/" + binding.ETLangueDepart.text.toString() + "-" + binding.ETLangueArrive.text.toString() + "/"+ binding.ETTextMotATraduire.text.toString()
        return site + suite
    }

    private fun setAlarm() {

        var serviceIntent = Intent(this, NotifService::class.java)
        serviceIntent.apply {
            action = "start"
        }

        val pendingIntent = PendingIntent.getService(this, 0, serviceIntent, PendingIntent.FLAG_IMMUTABLE)

        val calendar = Calendar.getInstance()
        calendar[Calendar.HOUR_OF_DAY] = 8
        calendar[Calendar.MINUTE] = 0
        calendar[Calendar.SECOND] = 0

        if (calendar.time < Date()) calendar.add(Calendar.DAY_OF_MONTH, 1)

        val alarmManager = getSystemService(ALARM_SERVICE) as AlarmManager
        alarmManager.setRepeating(
            AlarmManager.RTC_WAKEUP,
            calendar.timeInMillis,
            AlarmManager.INTERVAL_FIFTEEN_MINUTES,
            pendingIntent
        )
    }

    fun bd_dict(view : View){
        Toast.makeText(this, "listes des dictionnaires", Toast.LENGTH_SHORT).show()
        //val iii = Intent(this, BDDictionnaire::class.java)
        //startActivity(iii)
    }

    fun bd_mot(view : View){
        Toast.makeText(this, "listes des mots", Toast.LENGTH_SHORT).show()
    }

}