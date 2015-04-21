/*******************************************************************************
 * Filename      : main.cpp
 * Header File(s):
 * Description   :
 * Authors(s)    :
 * Date Created  :
 * Date Modified :
 * Modifier(s)   :
 *******************************************************************************/
/************************************
* Included Headers
************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include "main.hpp"
#include <Vec.hpp>

#include "Fold.hpp"
#include "Instance.hpp"

#include "NaiveBayesClassifier.hpp"
#include "Domain.hpp"

#include "NeuralNetworkClassifier.hpp"

#include "Kernel.hpp"
#include "Machine.hpp"
#include "ProbCal.hpp"
#include "BaseMachine.hpp"
#include "SMO.hpp"

#include "Classifier.hpp"

#include "KNearestClassifier.hpp"

#include "Model.hpp"

/************************************
* Namespaces
************************************/
using namespace std;
using namespace algorithms;

/************************************
* Local Variables
************************************/

/************************************
* Local Functions
************************************/
std::vector< Instance > getdata ( const std::string );

/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
int main ( int argc, char* argv[] )
{

    int kfolds = 10;

    for ( unsigned int itr = 1; itr <= 5; itr++ )
    {
        string filename = "data/pc" + to_string(itr) + ".arff.txt";
        vector< Instance > instances = getdata(filename);

        vector<int> indexes(instances.size());
        std::iota(begin(indexes), end(indexes), 0);
        std::random_shuffle(begin(indexes), end(indexes));

        vector<Fold> folds(kfolds);

        int validation_count = instances.size() / kfolds;

        for ( int i = 0; i < kfolds; i++ )
        {
            for ( size_t j = 0; j < instances.size()-validation_count; j++ )
            {
                int training_fold_idx = (i*(validation_count) + j) % instances.size();

                folds[i].data_training_set.push_back( instances[ indexes[training_fold_idx] ] );
            }

            for ( int j = 0; j < validation_count; j++ )
            {
                int validation_fold_idx = ((instances.size()-validation_count) + j + i*(validation_count)) % instances.size();

                folds[i].data_testing_set.push_back( instances[ indexes[validation_fold_idx] ]);
            }
        }

        ofstream output;
        output.open ("output.csv", ios::app);
        for ( size_t i = 0; i < folds.size(); i++ )
        {
            vector< Vec* > trainingset, testingset;
            vector<int> traininglabels, testinglabels;

            for ( size_t j = 0; j < folds[i].data_training_set.size(); j++)
            {
                Vec& data = *folds[i].data_training_set[j].data;
                trainingset.push_back( new Vec( data ) );

                if ( folds[i].data_training_set[j].label == 1 )
                {
                    traininglabels.push_back(1);
                }
                else
                {
                    traininglabels.push_back(0);
                }
            }

            for ( size_t j = 0; j < folds[i].data_testing_set.size(); j++)
            {
                Vec& data = *folds[i].data_testing_set[j].data;
                testingset.push_back( new Vec( data ) );

                if ( folds[i].data_testing_set[j].label == 1 )
                {
                    testinglabels.push_back(1);
                }
                else
                {
                    testinglabels.push_back(0);
                }
            }

            //naivebayes
            if ( 0 )
            {
                int dim = trainingset[0]->width();
                vector<naivebayes::Domain> inputdomains;

                for ( int j = 0; j < dim; j++ )
                {
                    inputdomains.push_back(naivebayes::Domain(0, 50, 200));
                }
                naivebayes::Domain outputdomain(0.0, 1.0, 2);

                naivebayes::Classifier classifier(inputdomains,outputdomain);

                for ( size_t j = 0; j < trainingset.size(); j++ )
                {
                    classifier.add_example(trainingset[j],traininglabels[j]);
                }

                int tp = 0, fn = 0, tn = 0, fp = 0, err = 0, inv = 0;
                for ( size_t j = 0; j < testingset.size(); j++ )
                {
                    int _class = classifier.classify(testingset[j]);
                    int label = testinglabels[j];

                    if ( _class == -1 )
                    {
                        inv++;
                        _class = rand() % 2;
                    }

                    if ( _class == 0 && label == 0 )
                    {
                        tp++;
                    }
                    else if ( _class != 0 && label == 0 )
                    {
                        fn++;
                    }
                    else if ( _class == 1 && label == 1 )
                    {
                        tn++;
                    }
                    else if ( _class != 1 && label == 1 )
                    {
                        fp++;
                    }
                    else
                    {
                        err++;
                    }
                }

                float precision   = ((float(tp)+float(fp))==0)?0:(float(tp)/(float(tp)+float(fp)));
                float recall      = ((float(tp)+float(fn))==0)?0:(float(tp)/(float(tp)+float(fn)));
                float accuracy    = ((float(tp)+float(tn)+float(fp)+float(fn))==0)?0:((float(tp)+float(tn))/(float(tp)+float(tn)+float(fp)+float(fn)));
                float fscore      = ((precision+recall) == 0)?0:2.0*((precision*recall)/(precision+recall));
                //float specificity = ((float(fp)+float(tn))==0)?0:(float(tn)/(float(fp)+float(tn)));
                //float fallout     = ((float(fp)+float(tn))==0)?0:(float(fp)/(float(fp)+float(tn)));

                output << accuracy    << ","
                       << fscore      << endl;
            }
            //neuralnetwork
            if ( 0 )
            {
                int dim = trainingset[0]->width();

                neuralnetwork::Classifier classifier(dim,dim/2,1);
                classifier.maxEpochs = 2000;
                classifier.useBatch = true;
                classifier.learningRate = 0.01;
                classifier.momentum = false;
                classifier.desiredAccuracy = 99.0;

                classifier.train(trainingset, traininglabels);

                int tp = 0, fn = 0, tn = 0, fp = 0, err = 0, inv = 0;
                for ( size_t j = 0; j < testingset.size(); j++ )
                {
                    int _class = classifier.classify(testingset[j]);
                    int label = testinglabels[j];

                    if ( _class == -1 )
                    {
                        inv++;
                        //_class = rand() % 2;
                    }

                    if ( _class == 0 && label == 0 )
                    {
                        tp++;
                    }
                    else if ( _class != 0 && label == 0 )
                    {
                        fn++;
                    }
                    else if ( _class == 1 && label == 1 )
                    {
                        tn++;
                    }
                    else if ( _class != 1 && label == 1 )
                    {
                        fp++;
                    }
                    else
                    {
                        err++;
                    }
                }

                float precision   = ((float(tp)+float(fp))==0)?0:(float(tp)/(float(tp)+float(fp)));
                float recall      = ((float(tp)+float(fn))==0)?0:(float(tp)/(float(tp)+float(fn)));
                float accuracy    = ((float(tp)+float(tn)+float(fp)+float(fn))==0)?0:((float(tp)+float(tn))/(float(tp)+float(tn)+float(fp)+float(fn)));
                float fscore      = ((precision+recall) == 0)?0:2.0*((precision*recall)/(precision+recall));
                //float specificity = ((float(fp)+float(tn))==0)?0:(float(tn)/(float(fp)+float(tn)));
                //float fallout     = ((float(fp)+float(tn))==0)?0:(float(fp)/(float(fp)+float(tn)));

                output << accuracy    << ","
                       << fscore      << endl;
            }
            //svm
            if ( 0 )
            {
                vector<double> d_traininglabels;
                for( size_t j = 0; j < traininglabels.size(); j++ )
                {
                    if ( traininglabels[j] == 0 )
                    {
                        d_traininglabels.push_back(-1.0);
                    }
                    else
                    {
                        d_traininglabels.push_back(1.0);
                    }
                }
                vector<double> d_testinglabels;
                for( size_t j = 0; j < testinglabels.size(); j++ )
                {
                    if ( testinglabels[j] == 0 )
                    {
                        d_testinglabels.push_back(-1.0);
                    }
                    else
                    {
                        d_testinglabels.push_back(1.0);
                    }
                }

                int dim = trainingset[0]->width();
                svm::Machine machine(svm::Kernel(svm::Kernel::RBF,0.1),dim);
                svm::SMO learn(&machine,trainingset,d_traininglabels);
                learn.run();
                svm::ProbCal cal(&machine,trainingset,d_traininglabels);
                cal.run();

                int tp = 0, fn = 0, tn = 0, fp = 0, err = 0;
                for ( size_t j = 0; j < testingset.size(); j++ )
                {
                    double output;
                    int _class = machine.compute(testingset[j],output);
                    double label = d_testinglabels[j];

                    if ( _class == -1 && label == -1 )
                    {
                        tp++;
                    }
                    else if ( _class != -1 && label == -1 )
                    {
                        fn++;
                    }
                    else if ( _class == 1 && label == 1 )
                    {
                        tn++;
                    }
                    else if ( _class != 1 && label == 1 )
                    {
                        fp++;
                    }
                    else
                    {
                        err++;
                    }
                }

                float precision   = ((float(tp)+float(fp))==0)?0:(float(tp)/(float(tp)+float(fp)));
                float recall      = ((float(tp)+float(fn))==0)?0:(float(tp)/(float(tp)+float(fn)));
                float accuracy    = ((float(tp)+float(tn)+float(fp)+float(fn))==0)?0:((float(tp)+float(tn))/(float(tp)+float(tn)+float(fp)+float(fn)));
                float fscore      = ((precision+recall) == 0)?0:2.0*((precision*recall)/(precision+recall));
                //float specificity = ((float(fp)+float(tn))==0)?0:(float(tn)/(float(fp)+float(tn)));
                //float fallout     = ((float(fp)+float(tn))==0)?0:(float(fp)/(float(fp)+float(tn)));

                output << accuracy    << ","
                       << fscore      << endl;
            }
            //logistic regression
            if ( 0 )
            {
                int dim = trainingset[0]->width();

                regression::Classifier classifier(dim,2);
                classifier.regulizer      = 0.0;
                classifier.max_iterations = 100;
                classifier.min_delta      = 1.0E-3;

                vector<Vec*> blankdata;
                vector<int> blanklabels;

                classifier.run_supervised(trainingset,traininglabels,blankdata,blanklabels);

                int tp = 0, fn = 0, tn = 0, fp = 0, err = 0, inv = 0;
                for ( size_t j = 0; j < testingset.size(); j++ )
                {
                    Vec* Result = classifier.model.compute(testingset[j]);
                    Vec& result = *Result;

                    double highprob = -1.0;
                    int _class = -1;
                    for ( unsigned int i = 0; i < result.width(); i++ )
                    {
                        if ( result(0,i) > highprob )
                        {
                            highprob = result(0,i);
                            _class = i;
                        }
                    }

                    int label = testinglabels[j];

                    if ( _class == -1 )
                    {
                        inv++;
                        _class = rand() % 2;
                    }

                    if ( _class == 0 && label == 0 )
                    {
                        tp++;
                    }
                    else if ( _class != 0 && label == 0 )
                    {
                        fn++;
                    }
                    else if ( _class == 1 && label == 1 )
                    {
                        tn++;
                    }
                    else if ( _class != 1 && label == 1 )
                    {
                        fp++;
                    }
                    else
                    {
                        err++;
                    }

                    delete Result;
                }

                float precision   = ((float(tp)+float(fp))==0)?0:(float(tp)/(float(tp)+float(fp)));
                float recall      = ((float(tp)+float(fn))==0)?0:(float(tp)/(float(tp)+float(fn)));
                float accuracy    = ((float(tp)+float(tn)+float(fp)+float(fn))==0)?0:((float(tp)+float(tn))/(float(tp)+float(tn)+float(fp)+float(fn)));
                float fscore      = ((precision+recall) == 0)?0:2.0*((precision*recall)/(precision+recall));
                //float specificity = ((float(fp)+float(tn))==0)?0:(float(tn)/(float(fp)+float(tn)));
                //float fallout     = ((float(fp)+float(tn))==0)?0:(float(fp)/(float(fp)+float(tn)));

                output << accuracy    << ","
                       << fscore      << endl;
            }
            //knearest
            if ( 0 )
            {
                int dim = trainingset[0]->width();

                knearest::Classifier classifier(2,dim);

                for ( size_t i = 0; i < trainingset.size(); i++ )
                {
                    classifier.add_example(trainingset[i],traininglabels[i]);
                }

                int tp = 0, fn = 0, tn = 0, fp = 0, err = 0, inv = 0;
                for ( size_t j = 0; j < testingset.size(); j++ )
                {
                    int _class = classifier.classify(testingset[j]);
                    int label = testinglabels[j];

                    if ( _class == -1 )
                    {
                        inv++;
                        _class = rand() % 2;
                    }

                    if ( _class == 0 && label == 0 )
                    {
                        tp++;
                    }
                    else if ( _class != 0 && label == 0 )
                    {
                        fn++;
                    }
                    else if ( _class == 1 && label == 1 )
                    {
                        tn++;
                    }
                    else if ( _class != 1 && label == 1 )
                    {
                        fp++;
                    }
                    else
                    {
                        err++;
                    }
                }

                float precision   = ((float(tp)+float(fp))==0)?0:(float(tp)/(float(tp)+float(fp)));
                float recall      = ((float(tp)+float(fn))==0)?0:(float(tp)/(float(tp)+float(fn)));
                float accuracy    = ((float(tp)+float(tn)+float(fp)+float(fn))==0)?0:((float(tp)+float(tn))/(float(tp)+float(tn)+float(fp)+float(fn)));
                float fscore      = ((precision+recall) == 0)?0:2.0*((precision*recall)/(precision+recall));
                //float specificity = ((float(fp)+float(tn))==0)?0:(float(tn)/(float(fp)+float(tn)));
                //float fallout     = ((float(fp)+float(tn))==0)?0:(float(fp)/(float(fp)+float(tn)));

                output << accuracy    << ","
                       << fscore      << endl;
            }
            //mixturemodel
            if ( 1 )
            {
                em::Model model;

                model.k = 2;
                model.max_iterations = 10;
                model.max_probability = 1.0E-100;

                model.train  ( trainingset, traininglabels );

                int tp = 0, fn = 0, tn = 0, fp = 0, err = 0, inv = 0;
                for ( size_t j = 0; j < testingset.size(); j++ )
                {
                    int _class = model.predict (testingset[j]);

                    int label = testinglabels[j];

                    if ( _class == -1 )
                    {
                        inv++;
                    }

                    if ( _class == 1 && label == 1 )
                    {
                        tp++;
                    }
                    else if ( _class != 1 && label == 1 )
                    {
                        fn++;
                    }
                    else if ( _class == 0 && label == 0 )
                    {
                        tn++;
                    }
                    else if ( _class != 0 && label == 0 )
                    {
                        fp++;
                    }
                    else
                    {
                        err++;
                    }
                }

                float precision   = ((float(tp)+float(fp))==0)?0:(float(tp)/(float(tp)+float(fp)));
                float recall      = ((float(tp)+float(fn))==0)?0:(float(tp)/(float(tp)+float(fn)));
                float accuracy    = ((float(tp)+float(tn)+float(fp)+float(fn))==0)?0:((float(tp)+float(tn))/(float(tp)+float(tn)+float(fp)+float(fn)));
                float fscore      = ((precision+recall) == 0)?0:2.0*((precision*recall)/(precision+recall));
                //float specificity = ((float(fp)+float(tn))==0)?0:(float(tn)/(float(fp)+float(tn)));
                //float fallout     = ((float(fp)+float(tn))==0)?0:(float(fp)/(float(fp)+float(tn)));

                output << accuracy    << ","
                       << fscore      << endl;
            }

            for ( size_t j = 0; j < trainingset.size(); j++ )
            {
                delete trainingset[j];
            }
            for ( size_t j = 0; j < testingset.size(); j++ )
            {
                delete testingset[j];
            }
        }
        output << endl;
        output.close();
    }

    return 0;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
vector< Instance > getdata ( const string filename )
{
    fstream datafile;
    datafile.open(filename.c_str(), ios::in);

    vector< Instance > instances;

    int total_examples = 0;
    int positive_examples = 0;
    int negative_examples = 0;

    string line;
    bool in_data = false;
    while ( getline(datafile, line) )
    {
        if ( in_data == false && line.find("@data") != string::npos )
        {
            in_data = true;
            getline(datafile, line);
        }

        if ( in_data == true )
        {
            vector<string> strs;
            boost::split(strs,line,boost::is_any_of(","));

            for ( size_t i = 0; i < strs.size(); i++ )
            {
                boost::trim(strs[i]);
            }

            string strlabel = strs.back();
            strs.pop_back();

            int label = 0;

            if ( strlabel.compare("N") == 0)
            {
                label = -1;
            }
            else if ( strlabel.compare("Y") == 0)
            {
                label = 1;
            }
            else if ( strlabel.compare("FALSE") == 0 )
            {
                label = -1;
            }
            else if ( strlabel.compare("TRUE") == 0 )
            {
                label = 1;
            }
            else
            {
                label = 0;
            }

            Instance instance;
            vector<double> row;
            for( size_t i = 0; i < strs.size(); i++ )
            {
                double value;

                try
                {
                    value = boost::lexical_cast<double>(strs[i]);
                    row.push_back(value);
                }
                catch ( const boost::bad_lexical_cast & ex )
                {
                    cout << "bad_lexical_cast(data): " << strs[i] << endl;
                }
            }

            if ( label == 1 )
            {
                positive_examples++;
            }
            else if ( label == -1 )
            {
                negative_examples++;
            }

            if ( label == 0 )
            {
                continue;
            }

            total_examples++;

            instance.label = label;
            instance.data = new Vec(row);
            instances.push_back(instance);
        }
    }
    datafile.close();

//    cout << "filename: " << filename << endl;
//    cout << "total   : " << total_examples << endl;
//    cout << "positive: " << positive_examples << endl;
//    cout << "negative: " << negative_examples << endl << endl;

    return instances;
}





































