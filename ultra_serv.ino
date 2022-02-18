#include <Servo.h>


const int echoPin = 11;
const int triggerPin = 12;

int dir1 = 6;
int dir2 = 5;
int mot1 = 10;// moteur dans le premier sens (avance);
int mot2 = 7;//moteur dans le deuxiemz sens (arriere);
int led = 8;
int distanceAvant;
int distanceDroite;
int distanceGauche;
float intervalle;

Servo myservo; //Création de l'objet servo
const int delay_time = 250; //Temps accordé au servo pour la mesure de la distance de chaque côté

//---------------------------------------------------------------------------------------------------------------------
void setup()
{
  
  Serial.begin(9600);
  pinMode(echoPin, INPUT);
  pinMode(triggerPin, OUTPUT);
   pinMode(led, OUTPUT);
   pinMode(mot1, OUTPUT);
   pinMode(mot2, OUTPUT);
   pinMode(dir1, OUTPUT);
   pinMode(dir2, OUTPUT);
  myservo.attach(9); //Associe myservo à la pin 9 (PWM)
}

//----------------------------------------------------------------------------------------------------------
void mesurerDistanceAvant()
{
  myservo.write(100);//90
      delay(delay_time);
        digitalWrite(triggerPin, LOW);
          delayMicroseconds(2);
            digitalWrite(triggerPin, HIGH); //Envoie d'une onde sonore
              delayMicroseconds(10);
                digitalWrite(triggerPin, LOW);
              intervalle = pulseIn(echoPin, HIGH); //Réception de l'écho
             intervalle = intervalle/5.8/10; //Conversion de la différence de temps entre l'envoie de l'onde sonore et la réception de l'écho en distance (cm)
            Serial.println("Distance avant:");
          Serial.println(intervalle);
       distanceAvant = intervalle; //Arrondissement de la distance
}

//-----------------------------------------------------------------------------------------------------------------------------
void mesurerDistanceGauche()// fonction permettent de prendre des mesures a gauch
{
        myservo.write(180);
          delay(delay_time);
           digitalWrite(triggerPin, LOW);
             delayMicroseconds( 2);
               digitalWrite(triggerPin, HIGH); //Envoie d'une onde sonore
                 delayMicroseconds( 10);
                    digitalWrite(triggerPin, LOW);
                   intervalle = pulseIn(echoPin, HIGH); //Réception de l'écho
                 intervalle = intervalle/5.8/10; //Conversion de la différence de temps entre l'envoie de l'onde sonore et la réception de l'écho en distance (cm)
                Serial.println("Distance gauche:");
              Serial.println(intervalle);
                distanceGauche = intervalle;
}

//------------------------------------------------------------------------------------------------------------
void mesurerDistanceDroite()
{
  myservo.write(60);//0
    delay(delay_time);
      digitalWrite(triggerPin, LOW);
         delayMicroseconds( 2);
            digitalWrite(triggerPin, HIGH); //Envoie d'une onde sonore
             delayMicroseconds( 10);
          digitalWrite(triggerPin, LOW);
        intervalle = pulseIn(echoPin, HIGH); //Réception de l'écho
       intervalle = intervalle/5.8/10; //Conversion de la différence de temps entre l'envoie de l'onde sonore et la réception de l'écho en distance (cm)
         Serial.println("Distance droite:");
            Serial.println(intervalle);
               distanceDroite = intervalle;
}

//------------------------------------------------------------------------------------------------------------
void recul()
{
   digitalWrite(mot1,LOW );
   digitalWrite(mot2, HIGH);
   delay(2500);
   digitalWrite(mot2,LOW );
 //digitalWrite(dir1,LOW);
  //digitalWrite(dir2,);
  }
  //------------------------------------------------------------------------------------------------------
  void avance()
  {
    digitalWrite(mot1, HIGH);
   digitalWrite(mot2, LOW);
   
  }
  //---------------------------------------------------------------------------------------------------------
  void gauche()
  {
    recul();
    digitalWrite(dir2,LOW);
    digitalWrite(dir1,HIGH);
    delay(3500);
    digitalWrite(dir1,LOW);
    avance();
  }
  //-----------------------------------------------------------------------------------------------------------*
  void droite()
  {
    recul();
    digitalWrite(dir1,LOW);
    digitalWrite(dir2,HIGH);
    delay(3500);
    digitalWrite(dir2,LOW);
    avance();
  }
//------------------------------------------------------------------------------------------------------------
void modeUltrason() // fonction permettent d'effectuer des testes pour determiner un obstacle
{
   avance();
  mesurerDistanceAvant();
  delay(delay_time);
             
  if(distanceAvant < 25) //Si la distance avant est de moins de 25cm
  {
       Serial.println("Obstacle à l'avant");
       digitalWrite(led,HIGH);
         Serial.println();
           mesurerDistanceGauche();
            delay(delay_time);
               mesurerDistanceDroite();
               delay(delay_time);
               digitalWrite(mot1,LOW);
             digitalWrite(mot2, HIGH );
                 delay(1000);
    if(distanceGauche < 15 && distanceDroite < 15) //Si la distance à gauche et la distance à droite sont de moins de 15cm
    {
             Serial.println("Obstacles à gauche et à droite, reculer");
            Serial.println();
            recul();
    }
    else if(distanceGauche > distanceDroite) //Si la distance gauche est plus grande que la distance droite
    {
            Serial.println("Obstacle à droite, tourner à gauche");
              Serial.println();
              gauche();
    }          
              
    else if(distanceGauche <= distanceDroite) //Si la distance gauche est plus petite ou égale à la distance droite
    {
           Serial.println("Obstacle à gauche, tourner à droite");
          Serial.println();
          droite();
              
    }      
    }
  else //Si la distance avant est de plus de 25cm
   {
            Serial.println("Aucun obstacle, continuer tout droit");
          Serial.println();
          digitalWrite(led,LOW);
          avance ();
   }
}

//-------------------------------------------------------------------------------------------------
void loop(){
  
  modeUltrason(); // appel de la fonction
}
