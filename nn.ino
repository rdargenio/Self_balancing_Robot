#include <math.h>

/******************************************************************
 * Network Configuration - customized per network 
 ******************************************************************/

const int PatternCount = 17;
const int InputNodes = 2;
const int HiddenNodes = 8;
const int OutputNodes = 1;
const float LearningRate = 0.3;
const float Momentum = 0.9;
const float InitialWeightMax = 0.5;
const float Success = 0.0004;

//lines 4 - 20
const float Input[PatternCount][InputNodes] = {
  {1.14,  0.49},
  {-1.63, 0.22},
  {1.90,  0.35},
  {-1.40, 0.45},
  {1.17,  0.33},
  {-1.52, 0.19},
  {1.07,  0.80},
  {-2.23, -0.14},
  {0.76,  1.19},
  {-1.21, 0.57},
  {1.20,  0.36},
  {-1.63, -0.50},
  {1.15,  -0.40},
  {-1.48, 0.04},
  {1.56,  -0.15},
  {-0.55, 0.12},
  {2.57,  -0.38}
}; 

const float Target[PatternCount][OutputNodes] = {
  {0},
  {1},
  {0},
  {1},
  {0},
  {1},
  {0},
  {1},
  {0},
  {1},
  {0},
  {1},
  {0},
  {1},
  {0},
  {1},
  {0}
};

//lines 30 - 46
const float TestData[PatternCount][InputNodes] = {
  {-1.31,  0.48},
  {0.61, 0.20},
  {-1.35,  0.70},
  {0.86, 0.79},
  {-1.45,  1.25},
  {1.67, 0.64},
  {-1.63,  0.76},
  {1.93, -0.02},
  {-0.54,  0.03},
  {-0.60, 0.02},
  {2.22,  -1.02},
  {-1.28, -0.09},
  {-1.62,  -0.40},
  {1.91, -0.16},
  {-1.71,  -0.55},
  {0.70, -0.80},
  {-2.11,  -0.53}
}; 

const float TestData_Target[PatternCount][OutputNodes] = {
  {255},
  {-255},
  {255},
  {-255},
  {255},
  {-255},
  {255},
  {-255},
  {-255},
  {255},
  {-255},
  {-255},
  {255},
  {-255},
  {255},
  {-255},
  {255}
};

/******************************************************************
 * End Network Configuration
 ******************************************************************/


int i, j, p, q, r;
int ReportEvery1000;
int RandomizedIndex[PatternCount];
long  TrainingCycle;
float Rando;
float Error;
float Test_Error;
float Accum;


float Hidden[HiddenNodes];
float Output[OutputNodes];
float HiddenWeights[InputNodes+1][HiddenNodes];
float OutputWeights[HiddenNodes+1][OutputNodes];
float HiddenDelta[HiddenNodes];
float OutputDelta[OutputNodes];
float ChangeHiddenWeights[InputNodes+1][HiddenNodes];
float ChangeOutputWeights[HiddenNodes+1][OutputNodes];

void setup(){
  Serial.begin(9600);
  randomSeed(analogRead(3));
  ReportEvery1000 = 1;
  for( p = 0 ; p < PatternCount ; p++ ) {    
    RandomizedIndex[p] = p ;
  }
}  

void loop (){

/******************************************************************
* Initialize HiddenWeights and ChangeHiddenWeights 
******************************************************************/

  for( i = 0 ; i < HiddenNodes ; i++ ) {    
    for( j = 0 ; j <= InputNodes ; j++ ) { 
      ChangeHiddenWeights[j][i] = 0.0 ;
      Rando = float(random(100))/100;
      HiddenWeights[j][i] = 2.0 * ( Rando - 0.5 ) * InitialWeightMax ;
    }
  }
/******************************************************************
* Initialize OutputWeights and ChangeOutputWeights
******************************************************************/

  for( i = 0 ; i < OutputNodes ; i ++ ) {    
    for( j = 0 ; j <= HiddenNodes ; j++ ) {
      ChangeOutputWeights[j][i] = 0.0 ;  
      Rando = float(random(100))/100;        
      OutputWeights[j][i] = 2.0 * ( Rando - 0.5 ) * InitialWeightMax ;
    }
  }
  Serial.println();
  Serial.println();
  Serial.print("--------------------------");
  Serial.println();
  Serial.println("Initial/Untrained Outputs: ");
  Serial.print("--------------------------");
  Serial.println();
  toTerminal();
/******************************************************************
* Begin training 
******************************************************************/

  for( TrainingCycle = 1 ; TrainingCycle < 2147483647 ; TrainingCycle++) {    

/******************************************************************
* Randomize order of training patterns
******************************************************************/

    for( p = 0 ; p < PatternCount ; p++) {
      q = random(PatternCount);
      r = RandomizedIndex[p] ; 
      RandomizedIndex[p] = RandomizedIndex[q] ; 
      RandomizedIndex[q] = r ;
    }
    Error = 0.0 ;
/******************************************************************
* Cycle through each training pattern in the randomized order
******************************************************************/
    for( q = 0 ; q < PatternCount ; q++ ) {    
      p = RandomizedIndex[q];

/******************************************************************
* Compute hidden layer activations
******************************************************************/

      for( i = 0 ; i < HiddenNodes ; i++ ) {    
        Accum = HiddenWeights[InputNodes][i] ;
        for( j = 0 ; j < InputNodes ; j++ ) {
          Accum += Input[p][j] * HiddenWeights[j][i] ;
        }
        Hidden[i] = 1.0/(1.0 + exp(-Accum)) ;
      }

/******************************************************************
* Compute output layer activations and calculate errors
******************************************************************/

      for( i = 0 ; i < OutputNodes ; i++ ) {    
        Accum = OutputWeights[HiddenNodes][i] ;
        for( j = 0 ; j < HiddenNodes ; j++ ) {
          Accum += Hidden[j] * OutputWeights[j][i] ;
        }
        Output[i] = 1.0/(1.0 + exp(-Accum)) ;   
        OutputDelta[i] = (Target[p][i] - Output[i]) * Output[i] * (1.0 - Output[i]) ;   
        Error += 0.5 * (Target[p][i] - Output[i]) * (Target[p][i] - Output[i]) ;
      }

/******************************************************************
* Backpropagate errors to hidden layer
******************************************************************/

      for( i = 0 ; i < HiddenNodes ; i++ ) {    
        Accum = 0.0 ;
        for( j = 0 ; j < OutputNodes ; j++ ) {
          Accum += OutputWeights[i][j] * OutputDelta[j] ;
        }
        HiddenDelta[i] = Accum * Hidden[i] * (1.0 - Hidden[i]) ;
      }


/******************************************************************
* Update Inner-->Hidden Weights
******************************************************************/


      for( i = 0 ; i < HiddenNodes ; i++ ) {     
        ChangeHiddenWeights[InputNodes][i] = LearningRate * HiddenDelta[i] + Momentum * ChangeHiddenWeights[InputNodes][i] ;
        HiddenWeights[InputNodes][i] += ChangeHiddenWeights[InputNodes][i] ;
        for( j = 0 ; j < InputNodes ; j++ ) { 
          ChangeHiddenWeights[j][i] = LearningRate * Input[p][j] * HiddenDelta[i] + Momentum * ChangeHiddenWeights[j][i];
          HiddenWeights[j][i] += ChangeHiddenWeights[j][i] ;
        }
      }

/******************************************************************
* Update Hidden-->Output Weights
******************************************************************/

      for( i = 0 ; i < OutputNodes ; i ++ ) {    
        ChangeOutputWeights[HiddenNodes][i] = LearningRate * OutputDelta[i] + Momentum * ChangeOutputWeights[HiddenNodes][i] ;
        OutputWeights[HiddenNodes][i] += ChangeOutputWeights[HiddenNodes][i] ;
        for( j = 0 ; j < HiddenNodes ; j++ ) {
          ChangeOutputWeights[j][i] = LearningRate * Hidden[j] * OutputDelta[i] + Momentum * ChangeOutputWeights[j][i] ;
          OutputWeights[j][i] += ChangeOutputWeights[j][i] ;
        }
      }
    }

/******************************************************************
* Every 1000 cycles send data to terminal for display
******************************************************************/
    ReportEvery1000 = ReportEvery1000 - 1;
    if (ReportEvery1000 == 0)
    {
      Serial.println(); 
      Serial.println(); 
      Serial.print ("TrainingCycle: ");
      Serial.print (TrainingCycle);
      Serial.print ("  Error = ");
      Serial.println (Error, 5);

      toTerminal();

      if (TrainingCycle==1)
      {
        ReportEvery1000 = 999;
      }
      else
      {
        ReportEvery1000 = 1000;
      }
    }    


/******************************************************************
* If error rate is less than pre-determined threshold then end
******************************************************************/

    if( Error < Success ) break ;  
  }
  Serial.println ();
  Serial.println(); 
  Serial.print ("TrainingCycle: ");
  Serial.print (TrainingCycle);
  Serial.print ("  Error = ");
  Serial.println (Error, 5);

  toTerminal();

  Serial.println ();  
  Serial.println ();
  Serial.println ("Training Set Solved! ");
  Serial.println ("----------------"); 
  Serial.println ();
  Serial.println ();  
  ReportEvery1000 = 1;


  /******************************************************************
  * Test experimental data accuracy
  ******************************************************************/
  
  while(1)
  {
    for( i = 0 ; i < HiddenNodes ; i++ ) {    
        Accum = HiddenWeights[InputNodes][i] ;
        for( j = 0 ; j < InputNodes ; j++ ) {
          Accum += TestData[p][j] * HiddenWeights[j][i] ;
        }
        Hidden[i] = 1.0/(1.0 + exp(-Accum)) ;
      }
      

    for( i = 0 ; i < OutputNodes ; i++ ) {    
        Accum = OutputWeights[HiddenNodes][i] ;
        for( j = 0 ; j < HiddenNodes ; j++ ) {
          Accum += Hidden[j] * OutputWeights[j][i] ;
        }
        Output[i] = 1.0/(1.0 + exp(-Accum)) ;   
        OutputDelta[i] = (TestData_Target[p][i] - Output[i]) * Output[i] * (1.0 - Output[i]) ;   
        Error += 0.5 * (TestData_Target[p][i] - Output[i]) * (TestData_Target[p][i] - Output[i]) ;
      }
     
     toTerminal_Test();

     // functional end of loop 
     while(1)
     {
      
     }
  }
}


void toTerminal()
{

  for( p = 0 ; p < PatternCount ; p++ ) { 
    Serial.println(); 
    Serial.print ("  Training Pattern: ");
    Serial.println (p);      
    Serial.print ("  Input ");
    for( i = 0 ; i < InputNodes ; i++ ) {
      Serial.print (Input[p][i], DEC);
      Serial.print (" ");
    }
    Serial.print ("  Target ");
    for( i = 0 ; i < OutputNodes ; i++ ) {
      Serial.print (Target[p][i]*510 - 255, DEC);
      Serial.print (" ");
    }
/******************************************************************
* Compute hidden layer activations
******************************************************************/

    for( i = 0 ; i < HiddenNodes ; i++ ) {    
      Accum = HiddenWeights[InputNodes][i] ;
      for( j = 0 ; j < InputNodes ; j++ ) {
        Accum += Input[p][j] * HiddenWeights[j][i] ;
      }
      Hidden[i] = 1.0/(1.0 + exp(-Accum)) ;
    }

/******************************************************************
* Compute output layer activations and calculate errors
******************************************************************/

    for( i = 0 ; i < OutputNodes ; i++ ) {    
      Accum = OutputWeights[HiddenNodes][i] ;
      for( j = 0 ; j < HiddenNodes ; j++ ) {
        Accum += Hidden[j] * OutputWeights[j][i] ;
      }
      Output[i] = 1.0/(1.0 + exp(-Accum)) ; 
    }
    Serial.print ("  Output ");
    for( i = 0 ; i < OutputNodes ; i++ ) {       
      Serial.print (Output[i]*510 - 255, 5);
      Serial.print (" ");
    }
  }


}


void toTerminal_Test()
{
  Serial.print("------------");
  Serial.println();
  Serial.print("Testing Data");
  Serial.println();
  Serial.print("------------");
  Serial.println();
  for( p = 0 ; p < PatternCount ; p++ ) {  
    Serial.println();
    Serial.print ("  Training Pattern: ");
    Serial.println (p);     
    Serial.print ("  Input ");
    for( i = 0 ; i < InputNodes ; i++ ) {
      Serial.print (TestData[p][i], DEC);
      Serial.print (" ");
    }

    Serial.print ("  Target ");
    for( i = 0 ; i < OutputNodes ; i++ ) {
      Serial.print (TestData_Target[p][i], DEC);
      Serial.print (" ");
    }

    for( i = 0 ; i < HiddenNodes ; i++ ) {    
      Accum = HiddenWeights[InputNodes][i] ;
      for( j = 0 ; j < InputNodes ; j++ ) {
        Accum += TestData[p][j] * HiddenWeights[j][i] ;
      }
      Hidden[i] = 1.0/(1.0 + exp(-Accum)) ;
    }

    for( i = 0 ; i < OutputNodes ; i++ ) {    
      Accum = OutputWeights[HiddenNodes][i] ;
      for( j = 0 ; j < HiddenNodes ; j++ ) {
        Accum += Hidden[j] * OutputWeights[j][i] ;
      }
      Output[i] = 1.0/(1.0 + exp(-Accum)) ; 
      Output[i] = Output[i]*510 - 255;
    }
    Serial.print ("  Output ");
    for( i = 0 ; i < OutputNodes ; i++ ) {       
      Serial.print (Output[i], 5);
      Serial.print (" ");
    Serial.print ("  Error ");
    for( i = 0 ; i < OutputNodes ; i++ ) {  
      Test_Error = abs(Output[i] - TestData_Target[p][i])/Output[i];
      Serial.print (Test_Error, 5);
      Serial.print (" ");
    }
    }
  }
  Serial.println();
  Serial.println();
  Serial.print("Testing Data Finished");
  Serial.println();
  Serial.print("----------------");
  Serial.println();
  Serial.println();
}
