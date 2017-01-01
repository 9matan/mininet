/*
 * Copyright (c) 2015, The Regents of the University of California (Regents).
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
// Defines the hidden layer base class.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef MININET_LAYER_HIDDEN_LAYER_H
#define MININET_LAYER_HIDDEN_LAYER_H

#include <layer/layer.h>
#include <util/types.h>

namespace mininet {

class HiddenLayer : public Layer {
public:
  typedef std::shared_ptr<HiddenLayer> Ptr;
  typedef std::shared_ptr<const HiddenLayer> ConstPtr;

  explicit HiddenLayer(size_t input_size, size_t output_size)
    : Layer(input_size, output_size) {}

  // 'Forward' propagation is inherited from Layer.
  // 'Backward' takes in layer output (computed by 'Forward') and the derivative
  // of loss by that output. It also computes two derivatives of loss:
  // (1) 'deltas' are with respect to the input to the non-linearity
  // (2) 'gammas' are with respect to the input to the layer
  virtual void Backward(const VectorXd& output, const VectorXd& upstream_gammas,
                        VectorXd& gammas, VectorXd& deltas) const = 0;

}; // class HiddenLayer

} // namespace mininet

#endif
