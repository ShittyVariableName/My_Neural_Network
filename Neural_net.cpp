#include<iostream>
#include<vector>
#include<cmath>
#include<iomanip>

using namespace std;


const double e = 2.718281828459;  // defined Euler's number for the activation function



class neuron{
   public:
   double output;
   vector<double> weights;            // The weights going into the neuron size of which will also tell the number of neurons in the previous layer of the nn/w

   unsigned int layer_id , neuron_id;

   vector<neuron>* next_layer;        //references to every neuron in the next layer
   vector<neuron>* prev_layer;        //backward references to every neuron in previous layer

   double weighted_sum();
   double activate(double weighted_sum_value);
   void calculate_output();

};

vector<neuron> layer1, layer2;
double neuron :: weighted_sum(){

   double sum = 0;
   for(unsigned int i = 0; i < weights.size(); i++){
       neuron container = (*prev_layer)[i];
       sum = sum +  weights[i] * container.output;

   }
   return sum;

}


double neuron :: activate( double weighted_sum_value){

  return (1/(1 + (pow(e, -1 * weighted_sum_value)))); //Used the sigmoid as the activation function

}

void neuron :: calculate_output(){
        double wght_sum = weighted_sum();
        output = activate(wght_sum);
}

int main()
{  double input1, input2;
    neuron l00, l01;   // input layer
    neuron l10, l11;   // hidden layer
    neuron l20;        // output layer


    cout<<"Enter the inputs to the input layer"<<endl;
    cin>>input1>>input2;

    l00.output = l00.activate(input1); //Weights of input layer neurons assumed to be 1
    l01.output = l01.activate(input2);
    layer1.push_back(l00);
    layer1.push_back(l01);

    l10.prev_layer = &layer1;
    l10.weights.push_back(2);  //weight into 1st neuron of second/hidden layer
    l10.weights.push_back(4);  //weight into 1st neuron of second/hidden layer
    l10.calculate_output();
    l11.prev_layer = &layer1;
    l11.weights.push_back(6);  //weight into 2nd neuron of second/hidden layer
    l11.weights.push_back(5);  //weight into 2nd neuron of second/hidden layer
    l11.calculate_output();



    layer2.push_back(l10);
    layer2.push_back(l11);

    l20.prev_layer = &layer2;
    l20.weights.push_back(3);  //weight into 1st and only neuron of third/output layer
    l20.weights.push_back(2);  //weight into 1st and only neuron of third/output layer

    l20.calculate_output();


    cout<<"Outputs of first layer: "<<l00.output<<" "<<l01.output<<endl;
    cout<<"Output of second layer: "<<l10.output<<endl;
    cout<<"Output of the neural network is: "<<l20.output<<endl;


    cout << "Hello world!" << endl;
    return 0;
}
