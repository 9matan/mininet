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
// Defines the output layer base class.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef MININET_LAYER_OUTPUT_LAYER_H
#define MININET_LAYER_OUTPUT_LAYER_H

#include <layer/layer.h>
#include <loss/loss_functor.h>
#include <util/types.h>

namespace mininet {

class OutputLayer : public Layer {
public:
  typedef std::shared_ptr<OutputLayer> Ptr;
  typedef std::shared_ptr<const OutputLayer> ConstPtr;

  explicit OutputLayer(size_t input_size, size_t output_size)
    : Layer(input_size, output_size) {}

  // 'Forward' propagation is inherited from Layer. 'Backward' computes the
  // so-called 'deltas' and 'gammas', i.e. the derivative of loss with respect
  // to the pre-nonlinearity values and layer inputs, respectively. Note that
  // 'output' holds the output of the non-linearity.
  virtual double Backward(const LossFunctor::ConstPtr& loss,
                          const VectorXd& ground_truth, const VectorXd& output,
                          VectorXd& gammas, VectorXd& deltas) const = 0;

}; // class OutputLayer

} // namespace mininet

#endif