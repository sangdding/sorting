#pragma once

#include <vector>
#include <iterator>

using namespace std;

namespace aips2o {
namespace learned_sort {

// Packs the key and its respective scaled CDF value
template <typename T>
struct training_point {
  T x;
  double y;
};

// Represents linear models
struct linear_model {
  double slope = 0;
  double intercept = 0;
};

// An implementation of a 2-layer RMI model
template <class It>
class TwoLayerRMI {

    using T = typename std::iterator_traits<It>::value_type;

 public:
  // CDF model hyperparameters
  struct Params {
    // Member fields
    long num_leaf_models;

    // Default hyperparameters
    static constexpr long DEFAULT_NUM_LEAF_MODELS = 1024;

    // Default constructor
    Params() {
      this->num_leaf_models = DEFAULT_NUM_LEAF_MODELS;
    }
  };

  // Member variables of the CDF model
  bool trained;
  linear_model root_model;
  vector<linear_model> leaf_models;
  vector<double> max_percentiles;
  Params hp;

  // CDF model constructor
  TwoLayerRMI(Params p) {
    this->trained = false;
    this->hp = p;
    this->leaf_models.resize(p.num_leaf_models);
  }

  /**
   * @brief Train a CDF function with an RMI architecture, using linear spline
   * interpolation.
   *
   * @param begin Random-access iterators to the initial position of the
   * sequence to be used for sorting. The range used is [begin,end), which
   * contains all the elements between first and last, including the element
   * pointed by first but not the element pointed by last.
   * @param end Random-access iterators to the last position of the sequence to
   * be used for sorting. The range used is [begin,end), which contains all the
   * elements between first and last, including the element pointed by first but
   * not the element pointed by last.
   * @return true if the model was trained successfully, false otherwise.
   */
  bool train(It begin, It end) {
    // Initialize the CDF model
    static const long NUM_LAYERS = 2;
    vector<vector<vector<training_point<T>>>> training_data(NUM_LAYERS);
    for (long layer_idx = 0; layer_idx < NUM_LAYERS; ++layer_idx) {
      training_data[layer_idx].resize(hp.num_leaf_models);
    }

    //----------------------------------------------------------//
    //                           SAMPLE                         //
    //----------------------------------------------------------//

    // Determine sample size
    const long SAMPLE_SZ = std::distance(begin, end);
    //----------------------------------------------------------//
    //                     TRAIN THE MODELS                     //
    //----------------------------------------------------------//

    // Initialize max_percentiles
    max_percentiles.resize(hp.num_leaf_models);

    std::fill(max_percentiles.begin(), max_percentiles.end(), 0.0);

    // Populate the training data for the root model
    for (It it = begin; it != end; it++) {
      training_data[0][0].push_back(
          {*it, 1.0 * std::distance(begin, it)  / SAMPLE_SZ});
    }

    // Train the root model using linear interpolation
    auto *current_training_data = &training_data[0][0];
    linear_model *current_model = &(this->root_model);

    // Find the min and max values in the training set
    training_point<T> min = current_training_data->front();
    training_point<T> max = current_training_data->back();

    // Calculate the slope and intercept terms, assuming min.y = 0 and max.y
    current_model->slope = 1. / (max.x - min.x);
    current_model->intercept = -current_model->slope * min.x;

    // Extrapolate for the number of models in the next layer
    current_model->slope *= this->hp.num_leaf_models - 1;
    current_model->intercept *= this->hp.num_leaf_models - 1;

    // Populate the training data for the next layer
    for (const auto &d : *current_training_data) {
      // Predict the model index in next layer
      long rank = current_model->slope * d.x + current_model->intercept;

      // Normalize the rank between 0 and the number of models in the next layer
      rank = std::max(static_cast<long>(0),
                      std::min(this->hp.num_leaf_models - 1, rank));

      // Place the data in the predicted training bucket
      training_data[1][rank].push_back(d);
      // Set the new max percentile for the rank
      max_percentiles[rank] = d.y;
    }

    for (int model_idx = 1; model_idx < this->hp.num_leaf_models; model_idx++) {
      max_percentiles[model_idx] = std::max(
        max_percentiles[model_idx], max_percentiles[model_idx-1]
      );
    }

    // Train the leaf models
    for (long model_idx = 0; model_idx < this->hp.num_leaf_models;
         ++model_idx) {
      // Update iterator variables
      current_training_data = &training_data[1][model_idx];
      current_model = &(this->leaf_models[model_idx]);

      // Interpolate the min points in the training buckets
      if (model_idx == 0) {
        // The current model is the first model in the current layer

        if (current_training_data->size() < 2) {
          // Case 1: The first model in this layer is empty
          current_model->slope = 0;
          current_model->intercept = 0;

          // Insert a fictive training point to avoid propagating more than one
          // empty initial models.
          training_point<T> tp;
          tp.x = 0;
          tp.y = 0;
          current_training_data->push_back(tp);
        } else {
          // Case 2: The first model in this layer is not empty

          min = current_training_data->front();
          max = current_training_data->back();

          // Hallucinating as if min.y = 0
          current_model->slope = (1. * max.y) / (max.x - min.x);
          current_model->intercept = min.y - current_model->slope * min.x;
        }
      } else if (model_idx == this->hp.num_leaf_models - 1) {
        if (current_training_data->empty()) {
          // Case 3: The final model in this layer is empty

          current_model->slope = 0;
          current_model->intercept = 1;
        } else {
          // Case 4: The last model in this layer is not empty

          min = training_data[1][model_idx - 1].back();
          max = current_training_data->back();

          // Hallucinating as if max.y = 1
          current_model->slope = (1. - min.y) / (max.x - min.x);
          current_model->intercept = min.y - current_model->slope * min.x;
        }
      } else {
        // The current model is not the first model in the current layer

        if (current_training_data->empty()) {
          // Case 5: The intermediate model in this layer is empty
          current_model->slope = 0;
          current_model->intercept = training_data[1][model_idx - 1]
                                         .back()
                                         .y;  // If the previous model
                                              // was empty too, it will
                                              // use the fictive
                                              // training points

          // Insert a fictive training point to avoid propagating more than one
          // empty initial models.
          // NOTE: This will _NOT_ throw to DIV/0 due to identical x's and y's
          // because it is working backwards.
          training_point<T> tp;
          tp.x = training_data[1][model_idx - 1].back().x;
          tp.y = training_data[1][model_idx - 1].back().y;
          current_training_data->push_back(tp);
        } else {
          // Case 6: The intermediate leaf model is not empty

          min = training_data[1][model_idx - 1].back();
          max = current_training_data->back();

          current_model->slope = (max.y - min.y) / (max.x - min.x);
          current_model->intercept = min.y - current_model->slope * min.x;
        }
      }
    }

    // NOTE:
    // The last stage (layer) of this model contains weights that predict the
    // CDF of the keys (i.e. Range is [0-1]) When using this model to predict
    // the position of the keys in the sorted order, you MUST scale the weights
    // of the last layer to whatever range you are predicting for. The inner
    // layers of the model have already been extrapolated to the length of the
    // stage.git
    //
    // This is a design choice to help with the portability of the model.
    //
    this->trained = true;

    return true;
  }
};
}  // namespace learned_sort
} // namespace aips2o