#include <math.h>

/******************************************************************
 * Network Configuration - customized per network 
 ******************************************************************/

const int PatternCount = 30;
const int TestPatternCount = 17; //85
const int InputNodes = 2;
const int HiddenNodes = 8;
const int OutputNodes = 1;
const float LearningRate = 0.3;
const float Momentum = 0.9;
const float InitialWeightMax = 0.5;
const float Success = 0.0004;

// lines 1 - 120
// gyro, accel
const float Input[PatternCount][InputNodes] = {
 /* {-0.02,   -0.66},
{0.27,    -0.61},
{-0.29,   -0.90},
{-0.01,   -0.97},
{-0.89,   -1.28},
{-0.19,   -0.68},
{-0.07,   -0.59},
{0.18,    -0.95},
{0.47,    -0.58},
{0.44,    -0.69},
{-0.03,   -0.60},
{-1.00,   -0.43},
{-0.76,   -0.64},
{-0.74,   -0.65},
{-1.18,   -0.62},
{-2.20,   -0.53},
{-3.38,   -3.06},
{-1.75,   1.43},
{-0.70,   -2.24},
{-1.74,   -0.64},
{0.15 ,   -0.23},
{0.64 ,   -2.38},
{0.82 ,   -0.52},
{1.47 ,   -0.55},
{0.94 ,   -0.66},
{1.11 ,   -0.92},
{1.01 ,   -0.42},
{0.94 ,   -0.89},
{1.24 ,   -0.55},
{1.13 ,   -0.49},
{1.12 ,   -0.68},
{1.04 ,   -0.24},
{0.86 ,   -0.83},
{1.01 ,   -0.65},
{0.23 ,   -0.53},
{0.06 ,   -0.67},
{-0.81,   -0.45},
{-0.70,   -0.35},
{-0.34,   -0.80},
{-0.20,   -0.60}*/
{-0.18,   -0.71},
{-0.22,   -0.75},
{-0.42,   -0.62},
{1.79 ,   0.08},
{0.28 ,   -0.89},
{0.82 ,   -0.42},
{-0.08,   -0.48},
{-0.32,   -0.61},
{-0.76,   -0.68},
{-0.25,   -0.75},
{-0.36,   -1.14},
{-0.39,   -0.98},
{0.10 ,   -0.38},
{0.75 ,   -0.81},
{0.71 ,   -0.36},
{0.62 ,   -1.22},
{0.10 ,   -0.82},
{-0.54,   -0.94},
{-0.16,   -1.38},
{-0.03,   -0.74},
{0.15 ,   -0.56},
{-0.76,   -1.01},
{-0.64,   -1.17},
{-0.36,   -0.80},
{-0.29,   -1.16},
{0.61 ,   -1.13},
{1.07 ,   0.31},
{0.56 ,   -1.38},
{0.28 ,   -0.49},
{-0.30,   -0.53}/*
{-0.60,   -0.61},
{-0.53,   -0.39},
{0.03 ,   -0.69},
{0.37 ,   -0.85},
{-0.15,   -0.68},
{0.20 ,   -0.62},
{-0.29,   -1.09},
{0.06 ,   -0.50},
{-0.02,   -0.47},
{0.01 ,   -0.87},
/*{0.17  ,  -0.50},
{0.23  ,  -0.85},
{-0.02 ,  -0.86},
{-0.72 ,  -0.19},
{-0.02 ,  0.10},
{-0.06 ,  -0.75},
{0.03  ,  -0.15},
{0.40  ,  -0.69},
{-0.15 ,  -0.71},
{0.12  ,  -0.45},
{0.41  ,  -0.51},
{-0.34 ,  -0.76},
{-0.07 ,  -0.69},
{0.16  ,  -0.65},
{-0.67 ,  -1.08},
{-0.33 ,  -1.05},
{0.00  ,  -0.45},
{0.08  ,  -1.02},
{0.05  ,  -0.58},
{0.05  ,  -0.95},
{0.09  ,  -1.03},
{0.17  ,  -0.58},
{0.32  ,  -0.42},
{-0.51 ,  -1.10},
{-0.26 ,  -0.32},
{-0.13 ,  -1.05},
{0.01  ,  -0.87},
{0.00  ,  -0.67},
{-0.07 ,  -0.73},
{-0.11 ,  -0.28},
{-0.03 ,  -0.66},
{0.01  ,  -0.67},
{-0.07 ,  -0.28},
{-0.16 ,  -0.78},
{-0.07 ,  -0.95},
{0.03  ,  -1.30},
{0.05  ,  -0.29},
{-0.04 ,  -0.88},
{-0.14 ,  -0.54},
{-0.04 ,  -0.40}*/
}; 

float Target[PatternCount][OutputNodes] = {
/*{0.15},
{-104.48},
{20.23},
{-14.68},
{226.72},
{160.09},
{152.05},
{92.62},
{-14.82},
{-71.61},
{-7.30},
{255.00},
{255.00},
{255.00},
{255.00},
{255.00},
{255.00},
{255.00},
{255.00},
{255.00},
{255.00},
{255.00},
{255.00},
{255.00},
{255.00},
{255.00},
{255.00},
{255.00},
{255.00},
{255.00},
{243.65},
{108.68},
{16.38},
{-151.44},
{-82.27},
{-70.82},
{169.02},
{246.35},
{245.93},
{253.60}*/
{255.00},
{255.00},
{255.00},
{-139.84},
{13.78},
{-170.52},
{-44.57},
{36.40},
{196.18},
{162.79},
{226.52},
{255.00},
{205.93},
{-6.90},
{-91.43},
{-168.43},
{-117.70},
{40.30},
{12.36},
{-0.74},
{-48.23},
{175.45},
{250.25},
{255.00},
{255.00},
{70.06},
{-129.72},
{-146.73},
{-149.18},
{-31.03}/*
{101.09},
{159.92},
{80.98},
{-13.56},
{72.23},
{-3.91},
{104.80},
{45.74},
{57.81},
{52.26}/*
{6.44},
{-37.49},
{-2.68},
{197.71},
{104.64},
{115.49},
{96.83},
{-7.21},
{82.48},
{29.27},
{-67.64},
{76.41},
{50.26},
{-3.40},
{196.82},
{198.93},
{152.97},
{130.63},
{125.43},
{116.59},
{98.65},
{62.00},
{-3.01},
{176.23},
{177.05},
{177.80},
{156.97},
{155.55},
{172.61},
{193.92},
{186.68},
{179.35},
{198.58},
{230.13},
{227.15},
{208.73},
{198.04},
{213.84},
{244.49},
{234.68}*/
};

// lines 121 - 205
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

//reformat target values
  for( p = 0 ; p < PatternCount ; p++ ) {
    for( i = 0 ; i < OutputNodes ; i++ ) {
      if(Target[p][i] >= 0)
        Target[p][i] = 1;
      else if(Target[p][i] < 0)
        Target[p][i] = 0;
    }
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
  for( p = 0 ; p < TestPatternCount ; p++ ) {  
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
