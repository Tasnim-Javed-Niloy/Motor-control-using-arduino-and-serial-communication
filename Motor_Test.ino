// Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;

float CSA;

#define numOfValsRec 2
#define digitsPerValRec 3

int valsRec[numOfValsRec];
int stringLength = numOfValsRec * digitsPerValRec + 1;
int counter = 0;
bool counterStart = false;
String receivedString;

void receiveData()
{
  while (Serial.available())
  {
    char c = Serial.read();
    if (c=='$')
    {
      counterStart = true;
    }
    if (counterStart)
    {
      if (counter < stringLength)
      {
        receivedString = String(receivedString+c);
        counter++;
      }
      if (counter >= stringLength)
      {
        for (int i=0; i<numOfValsRec; i++)
        {
          int num = (i*digitsPerValRec)+1;
          valsRec[i] = receivedString.substring(num,num+digitsPerValRec).toInt();
        }
        receivedString = "";
        counter = 0;
        counterStart = false;
      }
    }
  }
}

void setup() {
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  Serial.begin(9600);
}

void loop() {
  receiveData();
  if (valsRec[1] == 255){
    analogWrite(enA, 255);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
  else {
    analogWrite(enA, 255);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
////  CSA = (analogRead(A0)/1024)*5000; // reading in milivolt
//  CSA = analogRead(A0);
//  CSA = CSA/1.5; // I = V/R
//  Serial.print("Motor A Current= ");
//  Serial.print(CSA);
//  Serial.println(" ");
}
