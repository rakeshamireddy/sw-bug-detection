/******************************************************************************
* Filename      : NeuralNetworkClassifier.hpp
* Source File(s): Classifier.cpp
* Description   :
* Authors(s)    :
* Date Created  :
* Date Modified :
* Modifier(s)   :
*******************************************************************************/
#ifndef NEURALNETWORKCLASSIFIER_H
#define NEURALNETWORKCLASSIFIER_H

/*******************************************************************************
*  INCLUDES
********************************************************************************/
#include <string>
#include <vector>
#include <Vec.hpp>

namespace algorithms
{
namespace neuralnetwork
{
/*******************************************************************************
*  DEFINES
********************************************************************************/

/*******************************************************************************
*  MACROS
********************************************************************************/

/*******************************************************************************
*  DATA TYPES
********************************************************************************/

/*******************************************************************************
*  EXTERNALS
********************************************************************************/

/*******************************************************************************
*  CLASS DEFINITIONS
********************************************************************************/
class Classifier
{
    public:
        /* constructors */
        Classifier ( void ); /* default */
        Classifier ( int, int, int );
        Classifier ( const Classifier& ); /* copy */
        Classifier& operator= ( const Classifier& ); /* assign */
        ~Classifier ( void );

        /* functions */
        void train ( const std::vector<Vec*>&, const std::vector<int>& );
        int classify ( Vec* );

        /* variables */
        double learningRate;                    // adjusts the step size of the weight update
        double momentum;                        // improves performance of stochastic learning (don't use for batch)

        //number of neurons
        int nInput;
        int nHidden;
        int nOutput;

        Vec* inputNeurons;
        Vec* hiddenNeurons;
        Vec* outputNeurons;

        //weights
        Vec* wInputHidden;
        Vec* wHiddenOutput;

        //epoch counter
        long epoch;
        long maxEpochs;

        //accuracy required
        double desiredAccuracy;

        Vec* deltaInputHidden;
        Vec* deltaHiddenOutput;

        //error gradients
        Vec* hiddenErrorGradients;
        Vec* outputErrorGradients;

        //accuracy stats per epoch
        double trainingSetAccuracy;
        double trainingSetMSE;

        //batch learning flag
        bool useBatch;

    private:
        /* functions */
        void feedforward( Vec* );
        void initalize ( void );
        void initializeWeights ( void );
        void backpropagate( int );
        void updateWeights ( void );
        double activationFunction( double x );
        double getOutputErrorGradient ( double, double );
        double getHiddenErrorGradient( int );
        int getRoundedOutputValue( double );
};
}
}
#endif
