/*
 * Copyright (c) 2017, David Fridovich-Keil.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *    2. Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *
 *    3. Neither the name of the copyright holder nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS AS IS
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Please contact the author(s) of this library if you have any questions.
 * Author: David Fridovich-Keil   ( dfk@eecs.berkeley.edu )
 *         Sara Fridovich-Keil    ( saraf@princeton.edu )
 */

///////////////////////////////////////////////////////////////////////////////
//
// Defines the Layer base class.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef MININET_LAYER_LAYER_H
#define MININET_LAYER_LAYER_H

#include <util/types.h>

#include <memory>

namespace mininet {

class Layer {
public:
  virtual ~Layer();
  explicit Layer(size_t input_size, size_t output_size);

  // Get input/output sizes and weights.
  size_t InputSize() const { return weights_.cols() - 1; }
  size_t OutputSize() const { return weights_.rows(); }
  const MatrixXd& ImmutableWeights() const { return weights_; }

  // Update weights by gradient descent.
  void UpdateWeights(const MatrixXd& derivatives,
                     double step_size);

  // Perturb a single weight by a specified amount.
  void PerturbWeight(size_t ii, size_t jj, double amount);

  // Layers need to propagate forward. Specific types of layers will also
  // have a 'Backward' function to compute a derivative of loss with respect to
  // sum node value ('delta').
  virtual void Forward(const VectorXd& input, VectorXd& output) const = 0;

protected:
  // Weights from input (with bias) to output.
  MatrixXd weights_;

}; // class Layer

} // namespace mininet

#endif
