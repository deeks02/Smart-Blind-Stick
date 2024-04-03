//BLIND STICK FINAL

//pin declaration
const int trigpin_l = 3;
const int echopin_l = 2;
const int trigpin_d = 5;
const int echopin_d = 4;
const int buzzer = 6;

const int led = 9;


const int water_source = 7;
const int water_sense = A0;

//variable declaration
double duration = 0.0;
double distance = 0.0;
double safe_distance;
double depth= 0.0;
double safe_depth;
double water= 0.0;
double safe_water;


//distance/depth function for US sensor
double getdistance(int trigpin, int echopin)
{
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigpin, LOW);

  duration= pulseIn(echopin, HIGH);
  distance= duration*0.017;
  return distance;
}



//water function to read water levels
double getwater()
{
  digitalWrite(water_source, HIGH);
  delayMicroseconds(5);
  water = analogRead(water_sense);
  digitalWrite(water_source, LOW);
  return water;
}



void setup() 
{
  pinMode(trigpin_l, OUTPUT);
  pinMode(echopin_l, INPUT);
  pinMode(trigpin_d, OUTPUT);
  pinMode(echopin_d, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(water_source, OUTPUT);
  pinMode(water_sense, INPUT);
  Serial.begin(9600);
}



void loop()
{
  
  digitalWrite(led, HIGH);

  //distance block
  {
    distance = getdistance(trigpin_l, echopin_l);
    safe_distance = distance;
    Serial.print("Distance=");
    Serial.println(distance);
    if(safe_distance <= 30)
    {
     digitalWrite(buzzer, HIGH); 
    }
    else
    {
      digitalWrite(buzzer, LOW);
    }
  }



  //depth block
  {
    depth = getdistance(trigpin_d, echopin_d);
    safe_depth = depth;
    Serial.print("Depth=");
    Serial.println(depth);
    if(safe_depth >= 60)
    {
     digitalWrite(buzzer, HIGH);
     delay(30);
     digitalWrite(buzzer, LOW);
     delay(30); 
    }
    else
    {
      digitalWrite(buzzer, LOW);
    }
  }



  //water level block
  {
    water = getwater();
    safe_water = water;
    Serial.print("Water=");
    Serial.println(water);
    if(safe_water >= 180)
    {
      //fading sound
      for(int i = 30; i <= 100; i++)
      {
        analogWrite(buzzer, i);
        delay(10);
      }
    }
    else
    {
      digitalWrite(buzzer, LOW);
    }
  }
}



